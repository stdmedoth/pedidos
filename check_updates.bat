ECHO OFF
SET APP_DIR=C:
SET FILE_NEW=%APP_DIR%\pedidos\bin\PedidosSemConsoleNew.exe
ECHO Verificando
ECHO %FILE_NEW%

IF EXIST %FILE_NEW% (
  echo Existe atualização
  echo Atualizando...
  MOVE %APP_DIR%\pedidos\bin\PedidosSemConsoleNew.exe %APP_DIR%\pedidos\bin\PedidosSemConsole
  MOVE %APP_DIR%\pedidos\bin\PedidosComConsoleNew.exe %APP_DIR%\pedidos\bin\PedidosComConsole
  echo Atualizado
) ELSE (
  echo Nenhuma atualização
)
