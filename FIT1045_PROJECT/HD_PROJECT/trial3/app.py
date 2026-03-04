import streamlit as st
import plotly.graph_objects as go
import plotly.express as px
import json
import time
try:
    import pandas as pd
except ImportError:
    pd = None
from model_manager import ModelManager
from plugin_manager import PluginManager

# Page config
st.set_page_config(
    page_title="Personal AI Hub",
    page_icon="🤖",
    layout="wide",
    initial_sidebar_state="expanded"
)

# Initialize managers
@st.cache_resource
def init_managers():
    return ModelManager(), PluginManager()

model_manager, plugin_manager = init_managers()

# Custom CSS
st.markdown("""
<style>
.metric-card {
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    padding: 1rem;
    border-radius: 10px;
    color: white;
    margin: 0.5rem 0;
}
.plugin-card {
    background: #f8f9fa;
    padding: 1rem;
    border-radius: 8px;
    border-left: 4px solid #007bff;
    margin: 0.5rem 0;
}
</style>
""", unsafe_allow_html=True)

# Sidebar
with st.sidebar:
    st.title("🤖 AI Hub Control")
    
    # System Status
    st.subheader("📊 System Status")
    system_info = model_manager.get_system_info()
    
    col1, col2 = st.columns(2)
    with col1:
        st.metric("CPU", f"{system_info['cpu_percent']:.1f}%")
        st.metric("Device", system_info['device'])
    with col2:
        memory_percent = (system_info['memory']['used'] / system_info['memory']['total']) * 100
        st.metric("RAM", f"{memory_percent:.1f}%")
        st.metric("GPUs", len(system_info['gpus']))
    
    # GPU Status
    if system_info['gpus']:
        st.subheader("🎮 GPU Status")
        for i, gpu in enumerate(system_info['gpus']):
            gpu_usage = (gpu['memory_used'] / gpu['memory_total']) * 100
            st.metric(f"GPU {i}", f"{gpu_usage:.1f}%", f"{gpu['name'][:15]}...")
    
    # Model Management
    st.subheader("🧠 Model Management")
    available_models = model_manager.list_available_models()
    
    # Model selection
    all_models = available_models['ollama'] + list(available_models['huggingface'])
    selected_model = st.selectbox("Select Model", all_models)
    
    col1, col2 = st.columns(2)
    with col1:
        if st.button("Load Model"):
            model_type = "ollama" if selected_model in available_models['ollama'] else "huggingface"
            with st.spinner("Loading..."):
                success = model_manager.load_model(selected_model, model_type)
                if success:
                    st.success("Loaded!")
                else:
                    st.error("Failed!")
    
    with col2:
        if st.button("Unload Model"):
            if model_manager.unload_model(selected_model):
                st.success("Unloaded!")
            else:
                st.error("Not loaded!")
    
    # Loaded models
    if available_models['loaded']:
        st.write("**Loaded Models:**")
        for model in available_models['loaded']:
            st.write(f"• {model}")

# Main content
st.title("🤖 Personal Local AI Hub")
st.markdown("*Manage multiple LLMs locally with GPU acceleration and plugin support*")

# Tabs
tab1, tab2, tab3, tab4 = st.tabs(["💬 Chat", "🔌 Plugins", "📊 Analytics", "⚙️ Settings"])

with tab1:
    st.header("AI Chat Interface")
    
    # Chat settings
    col1, col2, col3 = st.columns(3)
    with col1:
        chat_model = st.selectbox("Chat Model", available_models['loaded'] or all_models, key="chat_model")
    with col2:
        temperature = st.slider("Temperature", 0.1, 2.0, 0.7, 0.1)
    with col3:
        max_tokens = st.slider("Max Tokens", 50, 500, 150)
    
    # Chat interface
    if "messages" not in st.session_state:
        st.session_state.messages = []
    
    # Display chat history
    for message in st.session_state.messages:
        with st.chat_message(message["role"]):
            st.write(message["content"])
    
    # Chat input
    if prompt := st.chat_input("Ask anything..."):
        st.session_state.messages.append({"role": "user", "content": prompt})
        
        with st.chat_message("user"):
            st.write(prompt)
        
        with st.chat_message("assistant"):
            with st.spinner("Thinking..."):
                response = model_manager.generate_response(
                    chat_model, prompt, 
                    temperature=temperature, 
                    max_length=max_tokens
                )
                st.write(response)
        
        st.session_state.messages.append({"role": "assistant", "content": response})

with tab2:
    st.header("🔌 Plugin System")
    
    plugins = plugin_manager.get_available_plugins()
    
    # Plugin selection
    selected_plugin = st.selectbox("Select Plugin", list(plugins.keys()))
    st.info(plugins[selected_plugin])
    
    if selected_plugin == "pdf_summarizer":
        st.subheader("📄 PDF Summarizer")
        uploaded_file = st.file_uploader("Upload PDF", type=['pdf'])
        plugin_model = st.selectbox("Model for Summary", available_models['loaded'] or all_models, key="pdf_model")
        
        if uploaded_file and st.button("Summarize PDF"):
            with st.spinner("Processing PDF..."):
                result = plugin_manager.execute_plugin(
                    "pdf_summarizer", uploaded_file, model_manager, plugin_model
                )
                st.write("**Summary:**")
                st.write(result)
    
    elif selected_plugin == "image_analyzer":
        st.subheader("🖼️ Image Analyzer")
        uploaded_image = st.file_uploader("Upload Image", type=['png', 'jpg', 'jpeg'])
        plugin_model = st.selectbox("Model for Analysis", available_models['loaded'] or all_models, key="img_model")
        
        if uploaded_image and st.button("Analyze Image"):
            col1, col2 = st.columns(2)
            with col1:
                st.image(uploaded_image, caption="Uploaded Image", use_column_width=True)
            with col2:
                with st.spinner("Analyzing..."):
                    result = plugin_manager.execute_plugin(
                        "image_analyzer", uploaded_image, model_manager, plugin_model
                    )
                    st.write("**Analysis:**")
                    st.write(result)
    
    elif selected_plugin == "coding_assistant":
        st.subheader("💻 Coding Assistant")
        code_input = st.text_area("Enter your code:", height=200)
        task = st.selectbox("Task", ["review", "debug", "optimize", "explain"])
        plugin_model = st.selectbox("Model for Coding", available_models['loaded'] or all_models, key="code_model")
        
        if code_input and st.button("Analyze Code"):
            with st.spinner("Analyzing code..."):
                result = plugin_manager.execute_plugin(
                    "coding_assistant", code_input, model_manager, plugin_model, task=task
                )
                st.write(f"**{task.title()} Result:**")
                st.write(result)

with tab3:
    st.header("📊 System Analytics")
    
    # Real-time metrics
    col1, col2, col3, col4 = st.columns(4)
    
    with col1:
        st.markdown(f"""
        <div class="metric-card">
            <h3>CPU Usage</h3>
            <h2>{system_info['cpu_percent']:.1f}%</h2>
        </div>
        """, unsafe_allow_html=True)
    
    with col2:
        memory_gb = system_info['memory']['used'] / (1024**3)
        st.markdown(f"""
        <div class="metric-card">
            <h3>Memory</h3>
            <h2>{memory_gb:.1f}GB</h2>
        </div>
        """, unsafe_allow_html=True)
    
    with col3:
        st.markdown(f"""
        <div class="metric-card">
            <h3>Loaded Models</h3>
            <h2>{len(available_models['loaded'])}</h2>
        </div>
        """, unsafe_allow_html=True)
    
    with col4:
        st.markdown(f"""
        <div class="metric-card">
            <h3>Available GPUs</h3>
            <h2>{len(system_info['gpus'])}</h2>
        </div>
        """, unsafe_allow_html=True)
    
    # GPU utilization chart
    if system_info['gpus']:
        st.subheader("GPU Utilization")
        if pd:
            gpu_data = pd.DataFrame([
                {"GPU": f"GPU {i}", "Memory Used": gpu['memory_used'], 
                 "Memory Total": gpu['memory_total'], "Load": gpu['load']}
                for i, gpu in enumerate(system_info['gpus'])
            ])
            
            fig = px.bar(gpu_data, x="GPU", y=["Memory Used", "Memory Total"], 
                         title="GPU Memory Usage (MB)")
            st.plotly_chart(fig, use_container_width=True)
        else:
            for i, gpu in enumerate(system_info['gpus']):
                st.write(f"GPU {i}: {gpu['memory_used']}/{gpu['memory_total']} MB")
    
    # Model performance metrics
    st.subheader("Model Information")
    if available_models['loaded']:
        model_data = []
        for model in available_models['loaded']:
            # Check both ollama and huggingface configs
            config = (model_manager.model_configs.get("ollama", {}).get(model, {}) or 
                     model_manager.model_configs.get("huggingface", {}).get(model, {}))
            model_data.append({
                "Model": model,
                "Type": config.get("type", "Unknown"),
                "Size": config.get("size", "Unknown"),
                "Provider": config.get("provider", "Unknown")
            })
        
        if pd:
            df = pd.DataFrame(model_data)
            st.dataframe(df, use_container_width=True)
        else:
            for model in model_data:
                st.write(f"**{model['Model']}** - {model['Type']} ({model['Size']})")

with tab4:
    st.header("⚙️ Settings & Configuration")
    
    col1, col2 = st.columns(2)
    
    with col1:
        st.subheader("Model Settings")
        
        # Default model settings
        default_temperature = st.slider("Default Temperature", 0.1, 2.0, 0.7, 0.1, key="default_temp")
        default_max_tokens = st.slider("Default Max Tokens", 50, 1000, 150, key="default_tokens")
        
        # GPU settings
        st.subheader("GPU Settings")
        use_gpu = st.checkbox("Enable GPU Acceleration", value=True)
        gpu_memory_fraction = st.slider("GPU Memory Fraction", 0.1, 1.0, 0.8, 0.1)
        
        if st.button("Save Settings"):
            settings = {
                "default_temperature": default_temperature,
                "default_max_tokens": default_max_tokens,
                "use_gpu": use_gpu,
                "gpu_memory_fraction": gpu_memory_fraction
            }
            with open("config/settings.json", "w") as f:
                json.dump(settings, f, indent=2)
            st.success("Settings saved!")
    
    with col2:
        st.subheader("Plugin Management")
        
        # Available plugins
        st.write("**Available Plugins:**")
        for plugin_id, description in plugins.items():
            st.markdown(f"""
            <div class="plugin-card">
                <h4>{plugin_id.replace('_', ' ').title()}</h4>
                <p>{description}</p>
            </div>
            """, unsafe_allow_html=True)
        
        st.subheader("System Information")
        st.json({
            "Python Version": "3.13",
            "Streamlit Version": st.__version__,
            "Device": system_info['device'],
            "Available Models": len(all_models),
            "Loaded Models": len(available_models['loaded'])
        })

# Auto-refresh system info
if st.button("🔄 Refresh System Info"):
    st.rerun()