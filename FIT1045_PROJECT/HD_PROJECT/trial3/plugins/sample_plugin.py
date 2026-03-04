from plugin_manager import BasePlugin

class SamplePlugin(BasePlugin):
    def get_name(self) -> str:
        return "Sample Plugin"
    
    def get_description(self) -> str:
        return "A sample plugin demonstrating the plugin architecture"
    
    def execute(self, input_data, model_manager, model_name="qwen3:30b", **kwargs):
        prompt = f"Process this input creatively: {input_data}"
        return model_manager.generate_response(model_name, prompt)

class TextAnalyzerPlugin(BasePlugin):
    def get_name(self) -> str:
        return "Text Analyzer"
    
    def get_description(self) -> str:
        return "Analyze text for sentiment, keywords, and structure"
    
    def execute(self, text_input, model_manager, model_name="qwen3:30b", **kwargs):
        prompt = f"""Analyze this text and provide:
1. Sentiment (positive/negative/neutral)
2. Key topics/themes
3. Writing style
4. Readability level

Text: {text_input}"""
        return model_manager.generate_response(model_name, prompt)