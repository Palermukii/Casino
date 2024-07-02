@echo off
:: Comprobar si las secuencias de escape ANSI están habilitadas
reg query "HKEY_CURRENT_USER\Console" /v VirtualTerminalLevel | find "0x1" > nul
if %errorlevel% neq 0 (
    echo Las secuencias de escape ANSI no están habilitadas.
    echo Ejecute setup.bat para configurar la consola correctamente.
    pause
    exit /b
)

:: Definir secuencias de escape ANSI para colores
set "ESC="
for /F %%e in ('echo prompt $E ^| cmd') do set "ESC=%%e"
set "RED=%ESC%[31m"
set "GREEN=%ESC%[32m"
set "YELLOW=%ESC%[33m"
set "BLUE=%ESC%[34m"
set "MAGENTA=%ESC%[35m"
set "CYAN=%ESC%[36m"
set "RESET=%ESC%[0m"



:: Ejecutar el programa 'game'
chcp 65001

:: Limpiar la pantalla
cls

Casino

:: Mensaje de salida después de ejecutar el programa
echo %YELLOW%El juego ha terminado. Presiona cualquier tecla para salir.%RESET%
pause > nul
