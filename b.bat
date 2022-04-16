@echo off
if "%~1" == "r" (goto run)

pushd _build\
      cl /nologo /Od /EHsc /Fe"main.exe" /Zi /W4 ../src/main.cpp /I ../src/ /link user32.lib Gdi32.lib
popd
exit /b

:run
.\_build\main.exe
exit /b
