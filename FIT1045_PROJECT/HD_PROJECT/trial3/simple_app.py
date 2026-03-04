import streamlit as st
import ollama
import json
import os

# Simple AI Hub without heavy dependencies
st.set_page_config(page_title="AI Hub", page_icon="🤖", layout="wide")

# Initialize session state
if "messages" not in st.session_state:
    st.session_state.messages = []

def get_available_models():
    try:
        models = ollama.list()
        return [model['name'] for model in models['models']]
    except:
        return ["qwen3:30b", "llama3:latest", "gemma3:4b"]

def chat_with_model(model, message):
    try:
        response = ollama.chat(
            model=model,
            messages=[{"role": "user", "content": message}]
        )
        return response['message']['content']
    except Exception as e:
        return f"Error: {str(e)}"

# Main UI
st.title("🤖 Personal AI Hub")
st.markdown("*Simple local AI interface*")

# Sidebar
with st.sidebar:
    st.header("🎛️ Controls")
    
    # Model selection
    models = get_available_models()
    selected_model = st.selectbox("Select Model", models)
    
    # Settings
    temperature = st.slider("Temperature", 0.1, 2.0, 0.7, 0.1)
    
    # Clear chat
    if st.button("Clear Chat"):
        st.session_state.messages = []
        st.rerun()

# Chat interface
st.header("💬 Chat")

# Display messages
for message in st.session_state.messages:
    with st.chat_message(message["role"]):
        st.write(message["content"])

# Chat input
if prompt := st.chat_input("Ask anything..."):
    # Add user message
    st.session_state.messages.append({"role": "user", "content": prompt})
    
    with st.chat_message("user"):
        st.write(prompt)
    
    # Get AI response
    with st.chat_message("assistant"):
        with st.spinner("Thinking..."):
            response = chat_with_model(selected_model, prompt)
            st.write(response)
    
    # Add assistant message
    st.session_state.messages.append({"role": "assistant", "content": response})

# Simple plugins section
st.header("🔌 Quick Tools")

col1, col2 = st.columns(2)

with col1:
    st.subheader("📝 Text Processor")
    text_input = st.text_area("Enter text to analyze:")
    if st.button("Analyze Text") and text_input:
        prompt = f"Analyze this text for sentiment and key points: {text_input}"
        result = chat_with_model(selected_model, prompt)
        st.write("**Analysis:**")
        st.write(result)

with col2:
    st.subheader("💻 Code Helper")
    code_input = st.text_area("Enter code to review:")
    if st.button("Review Code") and code_input:
        prompt = f"Review this code and suggest improvements:\n```\n{code_input}\n```"
        result = chat_with_model(selected_model, prompt)
        st.write("**Code Review:**")
        st.write(result)