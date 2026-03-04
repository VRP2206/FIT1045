import os
import importlib.util
import inspect
from abc import ABC, abstractmethod
from typing import Dict, List, Any
import PyPDF2
from PIL import Image
try:
    import cv2
    import numpy as np
except ImportError:
    cv2 = None
    np = None

class BasePlugin(ABC):
    @abstractmethod
    def get_name(self) -> str:
        pass
    
    @abstractmethod
    def get_description(self) -> str:
        pass
    
    @abstractmethod
    def execute(self, input_data: Any, **kwargs) -> Any:
        pass

class PDFSummarizerPlugin(BasePlugin):
    def get_name(self) -> str:
        return "PDF Summarizer"
    
    def get_description(self) -> str:
        return "Extract and summarize text from PDF files"
    
    def execute(self, pdf_file, model_manager, model_name="qwen3:30b", **kwargs) -> str:
        try:
            reader = PyPDF2.PdfReader(pdf_file)
            text = ""
            for page in reader.pages:
                text += page.extract_text() + "\n"
            
            if len(text) > 4000:
                text = text[:4000] + "..."
            
            prompt = f"Summarize this PDF content in 3-4 key points:\n\n{text}"
            return model_manager.generate_response(model_name, prompt)
        except Exception as e:
            return f"Error processing PDF: {e}"

class ImageAnalyzerPlugin(BasePlugin):
    def get_name(self) -> str:
        return "Image Analyzer"
    
    def get_description(self) -> str:
        return "Analyze images and describe their contents"
    
    def execute(self, image_file, model_manager, model_name="qwen3:30b", **kwargs) -> str:
        try:
            image = Image.open(image_file)
            if np:
                img_array = np.array(image)
            else:
                img_array = image
            
            # Basic image analysis
            if np and hasattr(img_array, 'shape'):
                height, width = img_array.shape[:2]
                channels = img_array.shape[2] if len(img_array.shape) > 2 else 1
            else:
                width, height = image.size
                channels = len(image.getbands())
            
            # Color analysis
            if np and hasattr(img_array, 'shape') and len(img_array.shape) > 2:
                channels = img_array.shape[2] if len(img_array.shape) > 2 else 1
                if channels == 3:
                    avg_color = np.mean(img_array, axis=(0, 1))
                    dominant_color = "red" if avg_color[0] > avg_color[1] and avg_color[0] > avg_color[2] else \
                                   "green" if avg_color[1] > avg_color[2] else "blue"
                else:
                    dominant_color = "grayscale"
            else:
                width, height = image.size
                channels = len(image.getbands())
                dominant_color = "color" if channels > 1 else "grayscale"
            
            # Basic complexity analysis
            if cv2 and np:
                gray = cv2.cvtColor(img_array, cv2.COLOR_RGB2GRAY) if channels == 3 else img_array
                edges = cv2.Canny(gray, 50, 150)
                complexity = "high" if np.sum(edges > 0) > (height * width * 0.1) else "low"
            else:
                complexity = "medium"
            
            analysis = f"Image Analysis:\n- Dimensions: {width}x{height}\n- Channels: {channels}\n- Dominant color: {dominant_color}\n- Complexity: {complexity}"
            
            prompt = f"Based on this image analysis, provide insights about what this image might contain:\n{analysis}"
            ai_description = model_manager.generate_response(model_name, prompt)
            
            return f"{analysis}\n\nAI Description:\n{ai_description}"
            
        except Exception as e:
            return f"Error analyzing image: {e}"

class CodingAssistantPlugin(BasePlugin):
    def get_name(self) -> str:
        return "Coding Assistant"
    
    def get_description(self) -> str:
        return "Help with code review, debugging, and optimization"
    
    def execute(self, code_input, model_manager, model_name="deepseek-coder", task="review", **kwargs) -> str:
        try:
            if task == "review":
                prompt = f"Review this code and provide suggestions for improvement:\n\n```\n{code_input}\n```"
            elif task == "debug":
                prompt = f"Help debug this code and identify potential issues:\n\n```\n{code_input}\n```"
            elif task == "optimize":
                prompt = f"Optimize this code for better performance:\n\n```\n{code_input}\n```"
            elif task == "explain":
                prompt = f"Explain what this code does in simple terms:\n\n```\n{code_input}\n```"
            else:
                prompt = f"Help with this code:\n\n```\n{code_input}\n```"
            
            return model_manager.generate_response(model_name, prompt)
            
        except Exception as e:
            return f"Error in coding assistance: {e}"

class PluginManager:
    def __init__(self):
        self.plugins = {}
        self.load_builtin_plugins()
        self.load_external_plugins()
    
    def load_builtin_plugins(self):
        """Load built-in plugins"""
        self.plugins["pdf_summarizer"] = PDFSummarizerPlugin()
        self.plugins["image_analyzer"] = ImageAnalyzerPlugin()
        self.plugins["coding_assistant"] = CodingAssistantPlugin()
    
    def load_external_plugins(self):
        """Load plugins from plugins directory"""
        plugins_dir = "plugins"
        if not os.path.exists(plugins_dir):
            return
        
        for filename in os.listdir(plugins_dir):
            if filename.endswith(".py") and not filename.startswith("__"):
                try:
                    plugin_path = os.path.join(plugins_dir, filename)
                    spec = importlib.util.spec_from_file_location(filename[:-3], plugin_path)
                    module = importlib.util.module_from_spec(spec)
                    spec.loader.exec_module(module)
                    
                    # Find plugin classes
                    for name, obj in inspect.getmembers(module):
                        if (inspect.isclass(obj) and 
                            issubclass(obj, BasePlugin) and 
                            obj != BasePlugin):
                            plugin_instance = obj()
                            self.plugins[filename[:-3]] = plugin_instance
                            
                except Exception as e:
                    print(f"Error loading plugin {filename}: {e}")
    
    def get_available_plugins(self) -> Dict[str, str]:
        """Get list of available plugins with descriptions"""
        return {
            plugin_id: plugin.get_description() 
            for plugin_id, plugin in self.plugins.items()
        }
    
    def execute_plugin(self, plugin_id: str, *args, **kwargs) -> Any:
        """Execute a specific plugin"""
        if plugin_id not in self.plugins:
            return f"Plugin '{plugin_id}' not found"
        
        try:
            return self.plugins[plugin_id].execute(*args, **kwargs)
        except Exception as e:
            return f"Error executing plugin '{plugin_id}': {e}"