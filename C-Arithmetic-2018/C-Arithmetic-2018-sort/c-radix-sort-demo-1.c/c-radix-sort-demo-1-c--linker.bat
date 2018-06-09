@echo off

set strCmd=g++ c-radix-sort-demo-1.c -o c-radix-sort-demo-1-c.exe

echo $%strCmd%
%strCmd%

pause
