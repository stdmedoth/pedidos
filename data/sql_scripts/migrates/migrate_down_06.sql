-- downgrade template made with UniversalMigrate script


update versao set versao = '1.1.1.5', lancamento = '2021-07-09';
DELETE FROM migrate WHERE code = 6;
