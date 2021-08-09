create table if not exists `grupos` (
  `code` int NOT NULL,
  `pai` int DEFAULT '0',
  `nome` varchar(50) DEFAULT 'Grupo Sem Nome',
  `nivel` int DEFAULT '1',
  PRIMARY KEY (`code`)
);
