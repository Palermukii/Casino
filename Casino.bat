@echo off
rem Establecer el valor de VirtualTerminalLevel en el registro
reg add "HKEY_CURRENT_USER\Console" /v VirtualTerminalLevel /t REG_DWORD /d 1 /f > nul
reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Console" /v VirtualTerminalLevel /t REG_DWORD /d 1 /f > nul
chcp 65001
cls
casino