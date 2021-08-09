-- down criado com script migrate pedidos

ALTER TABLE titulos MODIFY code INT ;
ALTER TABLE titulos DROP CONSTRAINT IF EXISTS titulos_ibfk_2;
ALTER TABLE titulos DROP KEY IF EXISTS titulos_ibfk_2;
ALTER TABLE titulos MODIFY pedido INT DEFAULT 0 ;

update versao set versao = '1.1.1.4', lancamento = '2021-06-29';
DELETE FROM migrate WHERE code = 5;
