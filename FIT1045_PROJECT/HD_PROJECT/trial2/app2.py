# app.py
"""
Personal Local AI Hub (Streamlit prototype)
Supports:
 - Ollama local API (recommended for easy local deployments)
 - llama_cpp (GGUF files) via llama-cpp-python
 - Hugging Face transformers (CPU/GPU, smaller models)
Includes:
 - Prompt UI, chat history
 - Simple file (PDF) summarizer plugin
 - GPU / RAM status panel

Install (suggested):
pip install streamlit requests pypdfium2 pypdf python-multipart
# optionally for llama_cpp:
pip install llama-cpp-python
# optionally for transformers:
pip install transformers accelerate torch

Run:
streamlit run app.py
"""

import streamlit as st
from typing import Optional, List, Dict
import time
import requests
import os
import tempfile
import json
from io import BytesIO

# Optional imports that may not be installed in all environments:
try:
    from llama_cpp import Llama
    HAS_LLAMA_CPP = True
except Exception:
    HAS_LLAMA_CPP = False

try:
    import torch
    HAS_TORCH = True
except Exception:
    HAS_TORCH = False

# PDF summarizer
try:
    from PyPDF2 import PdfReader
    HAS_PYPDF = True
except Exception:
    HAS_PYPDF = False

# ---------- Utility functions ----------
def get_gpu_info() -> Dict[str, Optional[str]]:
    info = {"torch_available": False, "cuda_available": False, "gpu_name": None, "gpu_total_mem": None, "gpu_free_mem": None}
    if HAS_TORCH:
        info["torch_available"] = True
        info["cuda_available"] = torch.cuda.is_available()
        if info["cuda_available"]:
            try:
                idx = torch.cuda.current_device()
                info["gpu_name"] = torch.cuda.get_device_name(idx)
                props = torch.cuda.get_device_properties(idx)
                info["gpu_total_mem"] = f"{props.total_memory//1024**2} MB"
                # torch doesn't give free mem easily; skip exact free mem
                info["gpu_free_mem"] = "See system monitor"
            except Exception as e:
                info["gpu_name"] = f"error: {e}"
    return info

def call_ollama_generate(model: str, prompt: str, max_tokens: int = 512) -> str:
    """
    Send a text generation request to a local Ollama instance.
    Requires Ollama to be running locally (default port 11434).
    """
    url = f"http://localhost:11434/compose"
    payload = {
        "model": model,
        "prompt": prompt,
        "maxTokens": max_tokens,
        "temperature": 0.2
    }
    try:
        r = requests.post(url, json=payload, timeout=120)
        r.raise_for_status()
        data = r.json()
        # Ollama responses place text in 'content' or so; adjust if different
        # The structure might be {"id":..., "model":..., "response": {"text": "..."}}
        # We'll try common fields:
        if isinstance(data, dict):
            if "text" in data:
                return data["text"]
            # sometimes 'response' -> 'content' or 'response' -> 'output'
            if "response" in data:
                if isinstance(data["response"], dict):
                    for key in ("output", "text", "content"):
                        if key in data["response"]:
                            return data["response"][key]
            # fallback - stringify
        return json.dumps(data, indent=2)
    except Exception as e:
        return f"[Ollama call error] {e}"

def llama_cpp_generate(model_path: str, prompt: str, max_tokens: int = 512) -> str:
    """Generate using llama-cpp-python wrapper. Model_path should be a GGUF or GGML file."""
    if not HAS_LLAMA_CPP:
        return "[llama_cpp not installed]"
    try:
        llm = Llama(model_path=model_path)
        resp = llm(prompt=prompt, max_tokens=max_tokens, temperature=0.2)
        return resp.get("choices", [{}])[0].get("text", "")
    except Exception as e:
        return f"[llama_cpp error] {e}"

def transformers_generate(model_name: str, prompt: str, max_tokens: int = 256) -> str:
    """Simple transformers-based generation (for small models only)."""
    try:
        from transformers import AutoModelForCausalLM, AutoTokenizer
        model = AutoModelForCausalLM.from_pretrained(model_name, device_map="auto" if HAS_TORCH and torch.cuda.is_available() else None)
        tokenizer = AutoTokenizer.from_pretrained(model_name)
        input_ids = tokenizer(prompt, return_tensors="pt").input_ids
        if HAS_TORCH and torch.cuda.is_available():
            input_ids = input_ids.to("cuda")
        gen = model.generate(input_ids, max_new_tokens=max_tokens, do_sample=True, temperature=0.2)
        out = tokenizer.decode(gen[0], skip_special_tokens=True)
        return out
    except Exception as e:
        return f"[transformers error] {e}"

def summarize_pdf_bytes(pdf_bytes: bytes, model_backend: str, model_tag: str) -> str:
    """Extract text from PDF and produce a simple summary using the selected backend."""
    if not HAS_PYPDF:
        return "[pypdf not installed]"
    try:
        reader = PdfReader(BytesIO(pdf_bytes))
        text = []
        for p in reader.pages:
            try:
                t = p.extract_text()
                if t:
                    text.append(t)
            except Exception:
                continue
        big_text = "\n\n".join(text)[:20000]  # limit to 20k chars
        prompt = f"Summarize the following PDF content in 5 concise bullet points:\n\n{big_text}"
        if model_backend == "Ollama":
            return call_ollama_generate(model_tag, prompt, max_tokens=400)
        elif model_backend == "llama_cpp":
            return llama_cpp_generate(model_tag, prompt, max_tokens=400)
        else:
            return transformers_generate(model_tag, prompt, max_tokens=400)
    except Exception as e:
        return f"[pdf summarizer error] {e}"

# ---------- Streamlit UI ----------
st.set_page_config(page_title="Local AI Hub", layout="wide")
st.title("🔌 Personal Local AI Hub — Prototype")
st.write("A Streamlit prototype to manage and interact with local LLMs (Ollama, llama.cpp, transformers).")

# Sidebar: backend selection and settings
st.sidebar.header("Backend & Model")
backend = st.sidebar.selectbox("Backend", ["Ollama", "llama_cpp", "transformers"])
if backend == "Ollama":
    st.sidebar.markdown("**Ollama local endpoint** (default: http://localhost:11434)")
    model_tag = st.sidebar.text_input("Ollama model tag (e.g. qwen:3.30b)", value="qwen:3.30b")
    ollama_url = st.sidebar.text_input("Ollama URL", value="http://localhost:11434")
elif backend == "llama_cpp":
    st.sidebar.markdown("**llama-cpp (GGUF/GGML)**")
    model_tag = st.sidebar.text_input("Path to GGUF/GGML model file", value="models/qwen-3-30b.Q4_K_M.gguf")
    st.sidebar.write("Note: llama-cpp-python must be installed and the model path valid.")
else:
    st.sidebar.markdown("**Transformers (HF)**")
    model_tag = st.sidebar.text_input("Hugging Face model name", value="gpt2")

st.sidebar.header("Generation settings")
max_tokens = st.sidebar.slider("Max tokens", min_value=32, max_value=2048, value=256, step=32)
temperature = st.sidebar.slider("Temperature", 0.0, 1.2, 0.2, step=0.05)
# (temp is wired into backends per-call where supported)

# GPU info panel
st.sidebar.header("System / GPU info")
gpu_info = get_gpu_info()
st.sidebar.json(gpu_info)

# Main area: chat + plugin
col1, col2 = st.columns([3, 1])

with col1:
    st.subheader("Prompt / Chat")
    if "history" not in st.session_state:
        st.session_state.history = []  # list of tuples (role, text)
    prompt_input = st.text_area("Enter prompt", height=180, key="prompt_input")
    submit = st.button("Generate")
    if submit and prompt_input.strip():
        st.session_state.history.append(("user", prompt_input))
        st.experimental_rerun()

    # When a new user prompt appears in history without a model response, process the last one
    if st.session_state.history and (len(st.session_state.history) % 2 == 1 and st.session_state.history[-1][0] == "user"):
        user_prompt = st.session_state.history[-1][1]
        with st.spinner("Generating..."):
            if backend == "Ollama":
                # call ollama via requests
                # NOTE: using local variable ollama_url earlier; fallback to default if not changed
                try:
                    url = ollama_url.rstrip("/") + "/compose"
                    payload = {"model": model_tag, "prompt": user_prompt, "maxTokens": max_tokens, "temperature": temperature}
                    resp = requests.post(url, json=payload, timeout=120)
                    resp.raise_for_status()
                    data = resp.json()
                    # Ollama may provide different response structure; try to parse common fields
                    model_text = None
                    if isinstance(data, dict):
                        for key in ("text", "content", "response"):
                            if key in data and isinstance(data[key], str):
                                model_text = data[key]
                                break
                        if model_text is None and "response" in data and isinstance(data["response"], dict):
                            for k2 in ("text", "content", "output"):
                                if k2 in data["response"]:
                                    model_text = data["response"][k2]
                                    break
                    if model_text is None:
                        model_text = json.dumps(data, indent=2)
                except Exception as e:
                    model_text = f"[Ollama request failed] {e}"
            elif backend == "llama_cpp":
                model_text = llama_cpp_generate(model_tag, user_prompt, max_tokens=max_tokens)
            else:
                model_text = transformers_generate(model_tag, user_prompt, max_tokens=max_tokens)

        st.session_state.history.append(("assistant", model_text))
        st.experimental_rerun()

    # Display chat
    st.markdown("### Conversation")
    for role, text in st.session_state.history[-20:]:
        if role == "user":
            st.markdown(f"**You:** {text}")
        else:
            st.markdown(f"**Model:** {text}")

with col2:
    st.subheader("Plugins")
    st.write("Plugins are lightweight tools that use the selected model to process files or do tasks.")

    st.markdown("#### PDF Summarizer")
    uploaded_pdf = st.file_uploader("Upload a PDF to summarize", type=["pdf"])
    if uploaded_pdf:
        if st.button("Summarize PDF"):
            pdf_bytes = uploaded_pdf.read()
            with st.spinner("Extracting and summarizing..."):
                summ = summarize_pdf_bytes(pdf_bytes, backend, model_tag)
                st.text_area("Summary", value=summ, height=240)

    st.markdown("---")
    st.markdown("#### Quick prompts")
    if st.button("Explain code snippet"):
        snippet = """def fib(n):
    if n <= 1:
        return n
    else:
        return fib(n-1) + fib(n-2)
"""
        task_prompt = f"Explain the following Python function and suggest an optimization:\n\n{snippet}"
        # generate
        if backend == "Ollama":
            gen = call_ollama_generate(model_tag, task_prompt, max_tokens=200)
        elif backend == "llama_cpp":
            gen = llama_cpp_generate(model_tag, task_prompt, max_tokens=200)
        else:
            gen = transformers_generate(model_tag, task_prompt, max_tokens=200)
        st.text_area("Model Output", value=gen, height=220)

    st.markdown("---")
    st.markdown("#### Model Info")
    if backend == "llama_cpp" and HAS_LLAMA_CPP:
        st.write("llama-cpp is available.")
        st.write("Model path:", model_tag)
        if st.button("Try load model (quick)"):
            try:
                # quick probe load (small)
                m = Llama(model_path=model_tag, n_ctx=512)
                st.success("Loaded (probe) — model seems accessible.")
            except Exception as e:
                st.error(f"Load failed: {e}")
    elif backend == "Ollama":
        st.write("Assumes Ollama daemon is running locally (port 11434).")
        try:
            r = requests.get(ollama_url.rstrip("/") + "/models", timeout=3)
            if r.ok:
                st.success("Ollama reachable.")
                st.json(r.json())
            else:
                st.warning("Ollama reachable but model list request failed.")
        except Exception as e:
            st.warning(f"Ollama not reachable: {e}")
    else:
        st.write("Transformers backend (HF). Model:", model_tag)

st.sidebar.markdown("---")
st.sidebar.write("⚠️ This is a prototype. Running large models (30B+) requires appropriate quantized files and sufficient GPU memory.")
st.sidebar.write("If using Ollama, install and run Ollama: https://ollama.com/")

# ---------- Footer ----------
st.markdown("---")
st.caption("Prototype created for FIT1045 'Something Awesome' project pitch. Ask me to expand this into a packaged app (Electron + backend), or add persistent memory, multi-model orchestration, or a plugin system.")
