@echo off
del /Q *.o > nul
cls

date < cr.txt
time < cr.txt
date < cr.txt > results_release.txt
time < cr.txt >> results_release.txt

echo. start
echo -----------------------------------

Sorts < input.txt >> results_release.txt
time < cr.txt
time < cr.txt >> results_release.txt
echo -----------------------------------
echo. over



rem echo.
rem echo another 2 minutes, please wait again ...
rem Sorts >> results_release.txt
rem time < cr.txt
rem time < cr.txt >> results_release.txt
pause
