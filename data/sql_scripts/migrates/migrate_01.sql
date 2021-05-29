-- versao base sem migrate

update versao set versao = '1.1', lancamento = '2021-05-28';
insert into migrate values(1, 'Versao 1.1', 'migrate_01.sql', '1.2', '2021-05-28');