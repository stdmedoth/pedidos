create table if not exists pedidos(
  code int primary key auto_increment,
  tipo_mov int default 1,
  vendedor int default 1,
  cliente int default 1,
  data_mov date default '2001-01-01',
  pag_cond int default 1,
  banco int default NULL,
  total float default 0.0,
  status int default 0,
  foreign key(cliente) references terceiros(code));
