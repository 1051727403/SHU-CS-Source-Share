@echo off
excel results_release.txt
if %errorlevel% == 0 goto quit
cls
echo.
echo �޷���excel�Զ���results_release.txt�ļ�����������·�ʽ��
echo 1) ������excel�����һ���Ѿ����ڵ�excel�ļ�����
echo 2) Ȼ��results_release.txt�ļ���ҷ��excel���档
echo.
pause
:quit
