rem C:\petitto\files\atualizacao\bin\curl.exe https://codeload.github.com/sistemapetitto/atualizacao/zip/master --output \petitto\files\atualizacao\tmp\atualizacao.zip
rem C:\petitto\files\atualizacao\bin\unzip.exe -o C:\petitto\files\atualizacao\tmp\atualizacao.zip -d C:\petitto\files\atualizacao\tmp\
xcopy /S /E /Y C:\petitto\files\atualizacao\tmp\atualizacao-master\Petitto.exe C:\petitto\gtk\bin
xcopy /S /E /Y C:\petitto\files\atualizacao\tmp\atualizacao-master\files\* C:\petitto\files\