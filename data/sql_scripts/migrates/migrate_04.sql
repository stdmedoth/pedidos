-- migrate criado com script migrate pedidos

DELETE FROM contatos WHERE terceiro NOT IN(SELECT code FROM terceiros);
ALTER TABLE contatos change terceiro terceiro int default NULL;
ALTER TABLE contatos add foreign key(terceiro) references terceiros(code);
ALTER TABLE maquinas add column versao varchar(200) default NULL;

update versao set versao = '1.1.4', lancamento = '2021-06-29';
insert into migrate values(4, 'Versao 1.1.4', 'migrate_04.sql', '1.1.4', '2021-06-29');
