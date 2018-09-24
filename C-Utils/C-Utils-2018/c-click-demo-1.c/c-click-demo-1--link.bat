@echo off

::set strCmd=gcc -finput-charset=UTF-8 -fexec-charset=GBK -mwindows -O2 frame.cpp -o frame.exe

::set strCmd=windres c-click-demo-1.rc -O coff -o c-click-demo-1.res
::echo #%strCmd%
::%strCmd%



set strCmd=gcc -finput-charset=UTF-8 -fexec-charset=GBK -mwindows -O2 c-click-demo-1.c c-click-demo-1.res -o c-click-demo-1.exe

echo #%strCmd%
%strCmd%

::del c-click-demo-1.res

pause