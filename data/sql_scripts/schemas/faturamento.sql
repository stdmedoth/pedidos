create table if not exists faturamento ( code int primary key auto_increment,
  pedido int default 0,
  cliente int default 0,
  entrada float default 0.0,
  saida float default 0.0,
  data_mov date default '2001-01-01',
  tipo_mov int default 0 );
