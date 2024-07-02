@echo off
reg add "HKEY_CURRENT_USER\Console" /v VirtualTerminalLevel /t REG_DWORD /d 1 /f > nul

:: Ejecución del script principal en una nueva consola
start cmd /k "noabrir.bat"
exit
