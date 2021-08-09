create table if not exists unidades( code int primary key auto_increment,
  nome varchar(50) default '',
  sigla varchar(10) default '',
  multiplo int default 1,
  medida int default 0);
