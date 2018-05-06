@echo off

set strCmd=cl.exe /O2 _path.c

echo #%strCmd%
%strCmd%

pause
