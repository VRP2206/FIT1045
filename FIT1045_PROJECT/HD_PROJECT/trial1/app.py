import streamlit as st
import os
from assistant import LocalAssistant
from voice_handler import VoiceHandler

# Initialize session state
if 'assistant' not in st.session_state:
    st.session_state.assistant = LocalAssistant()
if 'voice_handler' not in st.session_state:
    st.session_state.voice_handler = VoiceHandler()
if 'messages' not in st.session_state:
    st.session_state.messages = []

st.title("🤖 Local AI Assistant")

# Sidebar
with st.sidebar:
    st.header("Features")
    
    # Voice input
    if st.button("🎤 Voice Input"):
        with st.spinner("Listening..."):
            voice_text = st.session_state.voice_handler.listen()
            if voice_text and "Error" not in voice_text and "timeout" not in voice_text:
                st.session_state.messages.append({"role": "user", "content": voice_text})
                st.rerun()
    
    # File upload
    uploaded_file = st.file_uploader("📄 Upload file to summarize", type=['txt', 'py', 'md'])
    if uploaded_file:
        if st.button("Summarize File"):
            with open(f"temp_{uploaded_file.name}", "wb") as f:
                f.write(uploaded_file.getbuffer())
            
            summary = st.session_state.assistant.summarize_file(f"temp_{uploaded_file.name}")
            st.session_state.messages.append({"role": "assistant", "content": f"File Summary: {summary}"})
            os.remove(f"temp_{uploaded_file.name}")
            st.rerun()
    
    # Command execution
    command = st.text_input("💻 Execute command:")
    if command and st.button("Execute"):
        result = st.session_state.assistant.execute_command(command)
        st.session_state.messages.append({"role": "assistant", "content": f"Command result: {result}"})
        st.rerun()

# Chat interface
for message in st.session_state.messages:
    with st.chat_message(message["role"]):
        st.write(message["content"])

# Chat input
if prompt := st.chat_input("Ask me anything..."):
    st.session_state.messages.append({"role": "user", "content": prompt})
    
    with st.chat_message("user"):
        st.write(prompt)
    
    with st.chat_message("assistant"):
        with st.spinner("Thinking..."):
            response = st.session_state.assistant.chat(prompt)
            st.write(response)
            
            # Speak response
            st.session_state.voice_handler.speak(response)
    
    st.session_state.messages.append({"role": "assistant", "content": response})