create table servico_transporte(
  code int primary key auto_increment,
  transportador int not null default 1,
  cliente int not null default 1,
  cep_inicio varchar(20) not null default '',
  cep_entrega varchar(20) not null default '',
  num_entrega int not null default 0,
  orcamento int not null default 1,
  vlr_frete float not null default '0.0',
  observacoes_entrega varchar(500) not null default '');

create table frete_vlrs(
  code int primary key auto_increment,
  transportador int not null default 1,
  cliente int not null default 1,
  cep_inicio varchar(20) not null default '',
  cep_entrega varchar(20) not null default '',
  taxa_km float not null default '0.0',
  região int not null default 1,
  vlr_frete float not null default '0.0');
