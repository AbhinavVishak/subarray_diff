@echo on
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64     
set compilerflags=/O1 /EHsc
set linkerflags=/OUT:program.exe
cl.exe %compilerflags% main.cpp /link %linkerflags%