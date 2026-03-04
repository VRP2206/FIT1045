@echo off
echo 🤖 Installing and running Full AI Hub...

REM Use parent venv
call ..\venv\Scripts\activate.bat

REM Install core requirements
pip install streamlit ollama psutil plotly requests PyPDF2 Pillow --break-system-packages

REM Try optional dependencies
echo Installing optional dependencies...
pip install opencv-python pandas numpy --break-system-packages 2>nul
pip install GPUtil --break-system-packages 2>nul

REM Run the full app
echo.
echo 🚀 Starting Full AI Hub...
streamlit run app.py

pause