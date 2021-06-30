-- down criado com script migrate pedidos

ALTER TABLE contatos CHANGE terceiro terceiro INT NOT NULL;
ALTER TABLE contatos DROP CONSTRAINT IF EXISTS  contatos_ibfk_1;
ALTER TABLE maquinas DROP COLUMN IF EXISTS versao;

update versao set versao = '1.1.3', lancamento = '2021-06-29';
DELETE FROM migrate WHERE code = 4;