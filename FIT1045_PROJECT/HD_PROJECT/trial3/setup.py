#!/usr/bin/env python3
import subprocess
import sys
import os
import json

def create_directories():
    """Create necessary directories"""
    dirs = ["plugins", "models", "static", "config"]
    for dir_name in dirs:
        os.makedirs(dir_name, exist_ok=True)
    print("✅ Directories created")

def install_requirements():
    """Install Python requirements"""
    print("Installing requirements...")
    try:
        subprocess.run([sys.executable, "-m", "pip", "install", "-r", "requirements.txt"], check=True)
        print("✅ Requirements installed")
    except subprocess.CalledProcessError:
        print("❌ Failed to install requirements")

def setup_ollama_models():
    """Setup recommended Ollama models"""
    models = ["qwen3:30b", "llama3:latest", "deepseek-coder", "gemma3:4b"]
    
    print("Setting up Ollama models...")
    for model in models:
        try:
            print(f"Pulling {model}...")
            subprocess.run(["ollama", "pull", model], check=True, capture_output=True)
            print(f"✅ {model} installed")
        except (subprocess.CalledProcessError, FileNotFoundError):
            print(f"❌ Failed to install {model}")

def create_default_config():
    """Create default configuration"""
    config = {
        "default_temperature": 0.7,
        "default_max_tokens": 150,
        "use_gpu": True,
        "gpu_memory_fraction": 0.8,
        "preferred_models": {
            "chat": "qwen3:30b",
            "coding": "deepseek-coder",
            "small_tasks": "gemma3:4b"
        }
    }
    
    with open("config/settings.json", "w") as f:
        json.dump(config, f, indent=2)
    print("✅ Default configuration created")

def create_sample_plugin():
    """Create a sample custom plugin"""
    sample_plugin = '''from plugin_manager import BasePlugin

class SamplePlugin(BasePlugin):
    def get_name(self) -> str:
        return "Sample Plugin"
    
    def get_description(self) -> str:
        return "A sample plugin demonstrating the plugin architecture"
    
    def execute(self, input_data, model_manager, model_name="qwen3:30b", **kwargs):
        prompt = f"Process this input creatively: {input_data}"
        return model_manager.generate_response(model_name, prompt)
'''
    
    with open("plugins/sample_plugin.py", "w") as f:
        f.write(sample_plugin)
    print("✅ Sample plugin created")

def main():
    print("🤖 Setting up Personal AI Hub...")
    print("=" * 50)
    
    create_directories()
    install_requirements()
    create_default_config()
    create_sample_plugin()
    setup_ollama_models()
    
    print("\n" + "=" * 50)
    print("🎉 Setup complete!")
    print("\nTo start the AI Hub:")
    print("  streamlit run app.py")
    print("\nFeatures available:")
    print("  • Multi-LLM support (Ollama + HuggingFace)")
    print("  • GPU acceleration")
    print("  • Plugin system")
    print("  • Real-time system monitoring")
    print("  • PDF summarization")
    print("  • Image analysis")
    print("  • Coding assistance")

if __name__ == "__main__":
    main()