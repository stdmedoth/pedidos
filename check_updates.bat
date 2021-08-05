ECHO OFF
SET APP_DIR=C:
SET FILE_NEW=%APP_DIR%\pedidos\bin\PedidosSemConsole.exeNew
ECHO Verificando
ECHO %FILE_NEW%

IF EXIST %FILE_NEW% (
  echo Existe atualização
  echo Atualizando...
  MOVE %FILE_NEW% %APP_DIR%\pedidos\bin\PedidosSemConsole.exe
  echo Atualizado
) ELSE (
  echo Nenhuma atualização
)
start %APP_DIR%\pedidos\bin\PedidosSemConsole.exe
