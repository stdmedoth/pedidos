-- down criado com script migrate pedidos

ALTER TABLE terceiros DROP COLUMN relacionamento_desde;
update versao set versao = '1.1', lancamento = '2021-05-28';
DELETE FROM migrate WHERE code = 2;