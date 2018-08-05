@echo off

::set strCmd=gcc -finput-charset=UTF-8 -fexec-charset=GBK -mwindows -O2 frame.cpp -o frame.exe

set strCmd=windres gcc-sqlite3-db-demo-1.rc -O coff -o gcc-sqlite3-db-demo-1.res

echo #%strCmd%
%strCmd%


set strCmd=gcc -finput-charset=UTF-8 -fexec-charset=GBK -mwindows -O2 gcc-sqlite3-db-demo-1.c sqlite3.lib gcc-sqlite3-db-demo-1.res -o gcc-sqlite3-db-demo-1.exe

echo #%strCmd%
%strCmd%

::del gcc-sqlite3-db-demo-1.res

pause