create table if not exists cotacoes(
  code int primary key not null,
  descricao varchar(500) not null,
  status int not null,
  publica int not null,
  data datetime not null,
  validade datetime not null
);
