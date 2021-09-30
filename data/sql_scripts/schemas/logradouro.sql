create table if not exists logradouro (
  code int(10) unsigned NOT NULL AUTO_INCREMENT,
  CEP varchar(11) NOT NULL,
  tipo varchar(50) DEFAULT '',
  descricao varchar(100)  DEFAULT '',
  id_cidade int(11)  DEFAULT 0,
  UF varchar(2)  DEFAULT '',
  complemento varchar(100) DEFAULT '',
  descricao_sem_numero varchar(100) DEFAULT '',
  descricao_cidade varchar(100) DEFAULT '',
  codigo_cidade_ibge int(11) DEFAULT 0,
  descricao_bairro varchar(100) DEFAULT '',
  PRIMARY KEY (code),
  KEY cep (CEP) USING BTREE,
  KEY cidade (code,
  UF) USING BTREE,
  CONSTRAINT FK_cidade_2 FOREIGN KEY (id_cidade) REFERENCES cidade (code));