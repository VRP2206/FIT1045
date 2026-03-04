@echo off
echo 🎯 Starting 3D Pathfinding Visualizer...

REM Use existing venv or create new one
if exist "..\venv\Scripts\activate.bat" (
    call ..\venv\Scripts\activate.bat
) else (
    echo Creating virtual environment...
    python -m venv ..\venv
    call ..\venv\Scripts\activate.bat
)

REM Install dependencies
echo Installing dependencies...
pip install -r requirements.txt --quiet

REM Start the app
echo.
echo 🚀 Launching 3D Pathfinding Visualizer...
echo Open http://localhost:8501 in your browser
echo.
streamlit run app.py

pause