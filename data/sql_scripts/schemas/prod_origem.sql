create table if not exists prod_origem(
  code int not null primary key,
  idOrigem int not null,
  nome varchar(200),
  aliquota float
);
