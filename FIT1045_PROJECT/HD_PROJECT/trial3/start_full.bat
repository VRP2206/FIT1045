@echo off
echo 🤖 Starting Full AI Hub...

REM Use existing venv
call ..\venv\Scripts\activate.bat

REM Install missing dependencies if needed
pip install PyPDF2 Pillow plotly --quiet 2>nul

REM Start the full app
echo.
echo 🚀 Launching Full AI Hub...
echo Open http://localhost:8501 in your browser
echo.
streamlit run app.py

pause