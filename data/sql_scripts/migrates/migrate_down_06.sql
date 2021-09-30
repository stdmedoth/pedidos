-- downgrade template made with UniversalMigrate script


ALTER TABLE orcamentos DROP CONSTRAINT IF EXISTS orcamentos_ibfk_3;
ALTER TABLE orcamentos DROP COLUMN IF EXISTS forma_pagamento;
ALTER TABLE terceiros DROP COLUMN IF EXISTS dt_criacao;
ALTER TABLE terceiros DROP COLUMN IF EXISTS dt_modificacao;
ALTER TABLE orcamentos MODIFY COLUMN pag_cond int(11) DEFAULT 1 NULL;
ALTER TABLE orcamentos DROP COLUMN IF EXISTS dt_criacao;
ALTER TABLE orcamentos DROP COLUMN IF EXISTS dt_modificacao;

update versao set versao = '1.1.1.5', lancamento = '2021-07-09';
DELETE FROM migrate WHERE code = 6;
