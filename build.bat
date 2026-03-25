@echo off
setlocal

cd /d "%~dp0"

set "GCC=C:\Programacao\MinGW\bin\gcc.exe"
if not exist "%GCC%" (
  echo.
  echo GCC nao encontrado em: %GCC%
  exit /b 1
)

taskkill /F /T /IM Academia.exe >nul 2>&1
"%GCC%" -Wall -Wextra -g Academia.c menu.c aluno.c treino.c utils.c persistencia.c ui.c -o Academia.exe
if %errorlevel% neq 0 (
  echo.
  echo Build falhou.
  echo Dica: se aparecer "cannot open output file Academia.exe", feche o programa em execucao e tente de novo.
  exit /b %errorlevel%
)

echo.
echo Build concluido: Academia.exe
exit /b 0
