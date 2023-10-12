@echo off
del /Q *.o > nul
cls

date < cr.txt
time < cr.txt
date < cr.txt > results_debug.txt
time < cr.txt >> results_debug.txt

echo about 4 minutes, please wait ...
Sorts < input.txt >> results_debug.txt
time < cr.txt
time < cr.txt >> results_debug.txt

rem echo.
rem echo another 4 minutes, please wait again ...
rem Sorts < input.txt >> results_debug.txt
rem time < cr.txt
rem time < cr.txt >> results_debug.txt
pause
