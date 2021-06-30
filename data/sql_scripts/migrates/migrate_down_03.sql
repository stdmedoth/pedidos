-- down criado com script migrate pedidos

ALTER TABLE terceiros DROP COLUMN nome_fantasia;
update versao set versao = '1.1.2', lancamento = '2021-06-17';
DELETE FROM migrate WHERE code = 3;