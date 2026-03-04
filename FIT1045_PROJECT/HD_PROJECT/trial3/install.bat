@echo off
echo Installing AI Hub dependencies...

REM Install minimal requirements first
pip install -r requirements_minimal.txt

REM Try to install GPU support (optional)
echo.
echo Installing GPU support (optional)...
pip install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu118 2>nul
pip install transformers accelerate bitsandbytes 2>nul
pip install GPUtil 2>nul

echo.
echo Installation complete!
echo Run: streamlit run app.py