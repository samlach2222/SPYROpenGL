@ECHO OFF
cd "%~dp0"
"C:\Program Files\doxygen\bin\doxygen" doxyfile
echo.
echo.
TIMEOUT 5
