-- migrate criado com script migrate pedidos


update versao set versao = '1.1.3', lancamento = '2021-06-18';
insert into migrate values(3, 'Versao 1.1.3', 'migrate_03.sql', '1.1.3', '2021-06-18');

ALTER TABLE terceiros add column nome_fantasia varchar(255) after razao;
