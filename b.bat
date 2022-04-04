@echo off
pushd _build\
      cl /nologo /Od /EHsc /Fe"main.exe" /Zi /W4 ../src/main.cpp /I ../src/ /link user32.lib Gdi32.lib
popd
exit /b
