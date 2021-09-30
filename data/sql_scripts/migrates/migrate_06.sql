-- migrate made with UniversalMigrate script

ALTER TABLE orcamentos ADD COLUMN forma_pagamento INT AFTER pag_cond;
ALTER TABLE orcamentos ADD FOREIGN KEY(forma_pagamento) REFERENCES forma_pagamento(code);
ALTER TABLE terceiros ADD COLUMN IF NOT EXISTS dt_criacao DATETIME DEFAULT NOW() NOT NULL;
ALTER TABLE terceiros ADD COLUMN IF NOT EXISTS dt_modificacao DATETIME DEFAULT NOW();
ALTER TABLE orcamentos MODIFY COLUMN pag_cond int(11) NOT NULL;
ALTER TABLE orcamentos ADD COLUMN IF NOT EXISTS dt_criacao DATETIME DEFAULT NOW() NOT NULL;
ALTER TABLE orcamentos ADD COLUMN IF NOT EXISTS dt_modificacao DATETIME DEFAULT NOW();

update versao set versao = '1.1.1.6', lancamento = '2021-08-08';
insert into migrate values(6, 'Versao 1.1.1.6', 'migrate_06.sql', '1.1.1.6', '2021-08-08');
