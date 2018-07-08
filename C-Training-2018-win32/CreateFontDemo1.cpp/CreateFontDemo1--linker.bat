@echo off

::set strCmd=gcc -finput-charset=UTF-8 -mwindows -O2 CreateFontDemo1.cpp -o CreateFontDemo1.exe
set strCmd=gcc -finput-charset=UTF-8 -fexec-charset=GBK -mwindows -O2 CreateFontDemo1.cpp -o CreateFontDemo1.exe

echo #%strCmd%
%strCmd%

pause
