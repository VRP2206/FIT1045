@echo off
echo 🤖 Starting Simple AI Hub...

REM Use the existing venv from parent directory
call ..\venv\Scripts\activate.bat

REM Run the simple version
streamlit run simple_app.py

pause