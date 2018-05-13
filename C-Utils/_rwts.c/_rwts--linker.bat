@echo off

set strCmd=gcc _rwts.c -o _rwts.exe

echo #%strCmd%
%strCmd%

pause
