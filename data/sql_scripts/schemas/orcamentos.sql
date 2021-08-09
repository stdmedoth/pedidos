create table if not exists orcamentos(
  code int primary key auto_increment,
  tipo_mov int default 1,
  vendedor int default 0,
  cliente int default 0,
  dia date default '2001-01-01',
  pag_cond int default 1,
  banco int default NULL,
  cheque int default NULL,
  total float default 0,
  observacoes varchar(500) default '',
  foreign key(cliente) references terceiros(code));
