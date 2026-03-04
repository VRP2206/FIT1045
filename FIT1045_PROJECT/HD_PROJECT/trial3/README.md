# 🤖 Personal Local AI Hub

A comprehensive desktop application for managing and running multiple Large Language Models (LLMs) locally with GPU acceleration, plugin system, and advanced monitoring.

## ✨ Features

### 🧠 Multi-LLM Support
- **Ollama Integration**: Qwen3:30B, LLaMA 3, DeepSeek Coder, Gemma3
- **HuggingFace Models**: DialoGPT and custom models
- **Dynamic Loading**: Load/unload models on demand
- **GPU Acceleration**: Automatic CUDA detection and utilization

### 🔌 Plugin Architecture
- **PDF Summarizer**: Extract and summarize PDF documents
- **Image Analyzer**: Analyze images with AI descriptions
- **Coding Assistant**: Code review, debugging, optimization
- **Custom Plugins**: Easy plugin development framework

### 📊 System Monitoring
- **Real-time Metrics**: CPU, RAM, GPU utilization
- **Model Management**: Track loaded models and memory usage
- **Performance Analytics**: Interactive charts and graphs
- **Resource Optimization**: Intelligent resource allocation

### 🎨 Modern UI
- **Streamlit Interface**: Clean, responsive web UI
- **Multi-tab Layout**: Chat, Plugins, Analytics, Settings
- **Real-time Updates**: Live system monitoring
- **Custom Styling**: Professional gradient themes

## 🚀 Quick Start

### 1. Setup
```bash
python setup.py
```

### 2. Start the Hub
```bash
streamlit run app.py
```

### 3. Access Interface
Open http://localhost:8501 in your browser

## 📁 Project Structure

```
trial3/
├── app.py                 # Main Streamlit application
├── model_manager.py       # Multi-LLM management system
├── plugin_manager.py      # Plugin architecture & built-ins
├── setup.py              # Automated setup script
├── requirements.txt      # Python dependencies
├── config/
│   └── settings.json     # Configuration file
├── plugins/
│   └── sample_plugin.py  # Example custom plugin
├── models/               # Local model storage
└── static/              # Static assets
```

## 🔧 Configuration

### Model Settings
- **Temperature**: Response creativity (0.1-2.0)
- **Max Tokens**: Response length limit
- **GPU Memory**: Allocation percentage
- **Default Models**: Per-task model preferences

### Plugin Development
```python
from plugin_manager import BasePlugin

class MyPlugin(BasePlugin):
    def get_name(self) -> str:
        return "My Custom Plugin"
    
    def get_description(self) -> str:
        return "Description of what the plugin does"
    
    def execute(self, input_data, model_manager, **kwargs):
        # Plugin logic here
        return result
```

## 🎯 Use Cases

### 💬 AI Chat
- Multi-model conversations
- Temperature and token control
- Persistent chat history
- Model switching mid-conversation

### 📄 Document Processing
- PDF text extraction and summarization
- Batch document processing
- Custom summarization prompts
- Export results

### 🖼️ Image Analysis
- Computer vision analysis
- AI-powered descriptions
- Color and complexity detection
- Batch image processing

### 💻 Code Assistance
- Code review and suggestions
- Bug detection and fixes
- Performance optimization
- Code explanation

## 🔍 System Requirements

### Minimum
- Python 3.8+
- 8GB RAM
- 10GB storage

### Recommended
- Python 3.10+
- 16GB+ RAM
- NVIDIA GPU with 8GB+ VRAM
- 50GB+ storage for models

## 🛠️ Advanced Features

### GPU Optimization
- Automatic device detection
- Memory-efficient model loading
- Batch processing support
- Multi-GPU support (future)

### Plugin System
- Hot-reload plugins
- Dependency management
- Error handling
- Plugin marketplace (future)

### Monitoring & Analytics
- Resource usage tracking
- Model performance metrics
- Usage statistics
- Export capabilities

## 🤝 Contributing

1. Fork the repository
2. Create feature branch
3. Add your plugin/feature
4. Test thoroughly
5. Submit pull request

## 📝 License

MIT License - Feel free to use and modify

## 🆘 Support

- Check system requirements
- Verify GPU drivers
- Review error logs
- Update dependencies

---

**Built with ❤️ for the AI community**