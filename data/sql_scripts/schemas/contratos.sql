create table if not exists contratos(
  code int primary key auto_increment,
  cadastro int default 0,
  compras int default 0,
  faturamento int default 0,
  estoque int default 0,
  financeiro int default 0,
  marketing int default 0,
  relatorios int default 0,
  ativo int default 1,
  data_vencimento datetime default '2049-12-31');
