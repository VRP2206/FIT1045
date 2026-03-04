@echo off
echo 🤖 Starting Personal AI Hub...
echo.

REM Check if virtual environment exists
if not exist "venv" (
    echo Creating virtual environment...
    python -m venv venv
)

REM Activate virtual environment
call venv\Scripts\activate.bat

REM Install requirements if needed
if not exist "venv\Lib\site-packages\streamlit" (
    echo Installing requirements...
    pip install -r requirements.txt
)

REM Create directories and config if needed
if not exist "config" (
    echo Running setup...
    python setup.py
)

REM Start the application
echo.
echo 🚀 Launching AI Hub...
echo Open http://localhost:8501 in your browser
echo.
streamlit run app.py

pause