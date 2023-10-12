@echo off
excel results_release.txt
if %errorlevel% == 0 goto quit
cls
echo.
echo 无法用excel自动打开results_debug.txt文件。请改用如下方式：
echo 1) 先启动excel（如打开一个已经存在的excel文件）；
echo 2) 然后将results_debug.txt文件拖曳至excel界面。
echo.
pause
:quit
