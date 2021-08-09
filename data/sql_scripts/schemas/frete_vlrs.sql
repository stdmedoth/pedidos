create table if not exists frete_vlrs(
  code int primary key auto_increment,
  transportador int not null default 1,
  cliente int not null default 1,
  cep_inicio varchar(20) not null default '',
  cep_entrega varchar(20) not null default '',
  taxa_km float not null default '0.0',
  regiao int not null default 1,
  vlr_frete float not null default '0.0');
