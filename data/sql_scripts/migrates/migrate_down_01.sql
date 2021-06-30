-- down criado com script migrate pedidos

-- criado como exemplo, mas não deve ser rodado
-- DROP TABLE versao;
-- DROP TABLE migrate;

update versao set versao = 'x.x', lancamento = '2021-06-29';
DELETE FROM migrate WHERE code = 1;