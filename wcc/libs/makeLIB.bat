@echo off
REM this programm compile for windows(dll)
REM %1 -- gcc or g++
REM %2 -- lib name



if %1.==. goto ERR
if %2.==. goto ERR

if %1==c++ goto CPP
if %1==c goto C
goto END

:C
REM -fPIC
	gcc -c src\Win\%2.c -o obj\Win\c%2.o
	gcc -shared -o out\Win\c%2.dll obj\Win\c%2.o 
	goto END
:CPP
REM -fPIC
	g++ -c src\Win\%2.c -o obj\Win\cpp%2.o
    g++ -shared -o out\Win\cpp%2.dll obj\Win\cpp%2.o
REM	g++ -shared -o src\Win\cpp%2.o out\Win\cpp%2.dll
REM	g++ -shared src\Win\cpp%2.o -o out\Linux\cpp%2.so
REM	g++ -shared out\Linux\cpp%2.so -ldl out\Win\cpp%2
	goto END

:ERR
	echo ERROR: not valid cmd args
	goto END
:END
