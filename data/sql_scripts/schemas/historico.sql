create table if not exists historico(
  code int primary key not null,
  descricao varchar(200) not null,
  data datetime not null
);
