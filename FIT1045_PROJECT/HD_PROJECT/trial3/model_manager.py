import ollama
import psutil
import json
import threading
from typing import Dict, List, Optional

try:
    import GPUtil
except ImportError:
    GPUtil = None

try:
    import torch
    from transformers import AutoTokenizer, AutoModelForCausalLM
except ImportError:
    torch = None

class ModelManager:
    def __init__(self):
        self.loaded_models = {}
        self.model_configs = self.load_model_configs()
        self.device = self.get_best_device()
        self.lock = threading.Lock()
    
    def get_best_device(self):
        if torch and torch.cuda.is_available():
            return f"cuda:{torch.cuda.current_device()}"
        return "cpu"
    
    def load_model_configs(self):
        return {
            "ollama": {
                "qwen3:30b": {"type": "ollama", "size": "30B", "provider": "ollama"},
                "llama3:latest": {"type": "ollama", "size": "8B", "provider": "ollama"},
                "gpt-oss:120b": {"type": "ollama", "size": "120B", "provider": "ollama"},
                "gemma3:4b": {"type": "ollama", "size": "4B", "provider": "ollama"}
            },
            "huggingface": {
                "microsoft/DialoGPT-medium": {"type": "hf", "size": "345M", "provider": "huggingface"},
                "microsoft/DialoGPT-small": {"type": "hf", "size": "117M", "provider": "huggingface"}
            }
        }
    
    def get_system_info(self):
        gpus = GPUtil.getGPUs() if GPUtil else []
        return {
            "cpu_percent": psutil.cpu_percent(),
            "memory": psutil.virtual_memory()._asdict(),
            "gpus": [{"name": gpu.name, "memory_used": gpu.memoryUsed, 
                     "memory_total": gpu.memoryTotal, "load": gpu.load} for gpu in gpus],
            "device": self.device
        }
    
    def list_available_models(self):
        try:
            ollama_models = [model['name'] for model in ollama.list()['models']]
        except:
            ollama_models = []
        
        return {
            "ollama": ollama_models,
            "huggingface": list(self.model_configs["huggingface"].keys()),
            "loaded": list(self.loaded_models.keys())
        }
    
    def load_model(self, model_name: str, model_type: str = "ollama"):
        with self.lock:
            if model_name in self.loaded_models:
                return True
            
            try:
                if model_type == "ollama":
                    # Ollama models are loaded on-demand
                    self.loaded_models[model_name] = {"type": "ollama", "model": None}
                    return True
                
                elif model_type == "huggingface" and torch:
                    tokenizer = AutoTokenizer.from_pretrained(model_name)
                    model = AutoModelForCausalLM.from_pretrained(
                        model_name,
                        torch_dtype=torch.float16 if self.device.startswith("cuda") else torch.float32,
                        device_map="auto" if self.device.startswith("cuda") else None
                    )
                    self.loaded_models[model_name] = {
                        "type": "huggingface",
                        "model": model,
                        "tokenizer": tokenizer
                    }
                    return True
                    
            except Exception as e:
                print(f"Error loading {model_name}: {e}")
                return False
    
    def unload_model(self, model_name: str):
        with self.lock:
            if model_name in self.loaded_models:
                model_info = self.loaded_models[model_name]
                if model_info["type"] == "huggingface" and model_info["model"]:
                    del model_info["model"]
                    del model_info["tokenizer"]
                    if torch and torch.cuda.is_available():
                        torch.cuda.empty_cache()
                del self.loaded_models[model_name]
                return True
            return False
    
    def generate_response(self, model_name: str, prompt: str, **kwargs):
        if model_name not in self.loaded_models:
            if not self.load_model(model_name):
                return "Error: Failed to load model"
        
        model_info = self.loaded_models[model_name]
        
        try:
            if model_info["type"] == "ollama":
                response = ollama.chat(
                    model=model_name,
                    messages=[{"role": "user", "content": prompt}],
                    options=kwargs
                )
                return response['message']['content']
            
            elif model_info["type"] == "huggingface" and torch:
                model = model_info["model"]
                tokenizer = model_info["tokenizer"]
                
                inputs = tokenizer.encode(prompt, return_tensors="pt").to(model.device)
                with torch.no_grad():
                    outputs = model.generate(
                        inputs,
                        max_length=kwargs.get("max_length", 150),
                        temperature=kwargs.get("temperature", 0.7),
                        do_sample=True,
                        pad_token_id=tokenizer.eos_token_id
                    )
                
                response = tokenizer.decode(outputs[0], skip_special_tokens=True)
                return response[len(prompt):].strip()
                
        except Exception as e:
            return f"Error generating response: {e}"