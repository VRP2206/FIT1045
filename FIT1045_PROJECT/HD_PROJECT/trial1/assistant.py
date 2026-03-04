import ollama
import json
import subprocess
import os

class LocalAssistant:
    def __init__(self, model="qwen3:30b"):
        self.model = model
        self.memory_file = "memory.json"
        self.memory = self.load_memory()
    
    def load_memory(self):
        if os.path.exists(self.memory_file):
            with open(self.memory_file, 'r') as f:
                return json.load(f)
        return {"conversations": [], "preferences": {}}
    
    def save_memory(self):
        with open(self.memory_file, 'w') as f:
            json.dump(self.memory, f, indent=2)
    
    def chat(self, message):
        try:
            response = ollama.chat(model=self.model, messages=[
                {"role": "system", "content": "You are a helpful local AI assistant. Be concise and practical."},
                {"role": "user", "content": message}
            ])
            
            # Store conversation
            self.memory["conversations"].append({
                "user": message,
                "assistant": response['message']['content']
            })
            self.save_memory()
            
            return response['message']['content']
        except Exception as e:
            return f"Error: {str(e)}"
    
    def summarize_file(self, file_path):
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
            
            prompt = f"Summarize this file content in 2-3 sentences:\n\n{content[:2000]}"
            return self.chat(prompt)
        except Exception as e:
            return f"Error reading file: {str(e)}"
    
    def execute_command(self, command):
        safe_commands = ['ls', 'dir', 'pwd', 'date', 'whoami', 'echo']
        cmd_parts = command.split()
        
        if not cmd_parts or cmd_parts[0] not in safe_commands:
            return "Command not allowed for security reasons"
        
        try:
            result = subprocess.run(command, shell=True, capture_output=True, text=True, timeout=10)
            return result.stdout if result.stdout else result.stderr
        except Exception as e:
            return f"Command error: {str(e)}"