-- downgrade template made with UniversalMigrate script


ALTER TABLE orcamentos DROP CONSTRAINT IF EXISTS orcamentos_ibfk_2;
ALTER TABLE orcamentos DROP COLUMN IF EXISTS forma_pagamento;

ALTER TABLE pedidos DROP CONSTRAINT IF EXISTS pedidos_ibfk_2;
ALTER TABLE pedidos DROP COLUMN IF EXISTS forma_pagamento;

ALTER TABLE terceiros DROP COLUMN IF EXISTS dt_criacao;
ALTER TABLE terceiros DROP COLUMN IF EXISTS dt_modificacao;
ALTER TABLE orcamentos MODIFY COLUMN pag_cond int(11) DEFAULT 1 NULL;
ALTER TABLE orcamentos DROP COLUMN IF EXISTS dt_criacao;
ALTER TABLE orcamentos DROP COLUMN IF EXISTS dt_modificacao;
ALTER TABLE produtos CHANGE COLUMN fornecedor fornecedor INT DEFAULT 1;
ALTER TABLE produtos CHANGE COLUMN ncm ncm INT NOT NULL;
ALTER TABLE produtos CHANGE COLUMN icmscst icmscst INT NOT NULL;
ALTER TABLE produtos CHANGE COLUMN piscst piscst INT NOT NULL;
ALTER TABLE produtos CHANGE COLUMN cofinscst cofinscst INT NOT NULL;

update versao set versao = '1.1.1.5', lancamento = '2021-07-09';
DELETE FROM migrate WHERE code = 6;
