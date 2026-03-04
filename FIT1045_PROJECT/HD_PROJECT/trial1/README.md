# Local AI Personal Assistant

A fully local AI system with voice input, file summarization, and command execution.

## Features

- 🤖 **Local Qwen3 Integration** - Runs entirely offline
- 🎤 **Voice Input/Output** - Speech recognition and text-to-speech
- 📄 **File Summarization** - Analyze and summarize documents
- 💻 **Safe Command Execution** - Execute whitelisted system commands
- 🧠 **Persistent Memory** - Remembers conversations via JSON storage
- 🌐 **Streamlit UI** - Clean, adaptive web interface

## Quick Start

1. **Setup:**
   ```bash
   python setup.py
   ```

2. **Install Ollama** (Windows):
   - Download from https://ollama.ai/download
   - Run: `ollama pull qwen3:30b`

3. **Start Assistant:**
   ```bash
   streamlit run app.py
   ```

## Usage

- **Chat**: Type messages in the chat input
- **Voice**: Click 🎤 to speak your request
- **Files**: Upload files for AI summarization
- **Commands**: Execute safe system commands

## Architecture

- `assistant.py` - Core AI logic with Qwen3 integration
- `voice_handler.py` - Speech recognition and TTS
- `app.py` - Streamlit web interface
- `memory.json` - Persistent conversation storage

## Security

Commands are restricted to safe operations: `ls`, `dir`, `pwd`, `date`, `whoami`, `echo`