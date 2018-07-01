@echo off

::set strCmd=gcc -finput-charset=UTF-8 -fexec-charset=GBK -mwindows -O2 frame.cpp -o frame.exe
set strCmd=gcc -mwindows -O2 frame.cpp -o frame.exe


echo #%strCmd%
%strCmd%

pause
