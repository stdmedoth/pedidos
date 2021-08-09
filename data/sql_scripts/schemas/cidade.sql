create table if not exists cidade (
  code int(11) NOT NULL AUTO_INCREMENT,
  descricao varchar(100) DEFAULT '',
  uf varchar(2)  DEFAULT '',
  codigo_ibge int(11)  DEFAULT 0,
  ddd varchar(2)  DEFAULT '',
  PRIMARY KEY (code),
  KEY code (code) USING BTREE,
  KEY cidade (code,
  uf) USING BTREE,
  KEY cidade_estado (uf) USING BTREE);
