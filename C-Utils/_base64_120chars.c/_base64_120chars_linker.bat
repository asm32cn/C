@echo off

set strCmd=gcc _base64_120chars.c -o _base64_120chars.exe

echo #%strCmd%
%strCmd%

pause
