@echo off

set strCmd=g++ _pgmptr.cpp -o _pgmptr.exe

echo #%strCmd%
%strCmd%

pause
