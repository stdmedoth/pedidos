create table if not exists prod_requisicoes(
  code int primary key not null,
  produto int not null,
  quantidade float not null,
  descricao varchar(200),
  data datetime not null,
  prioridade int not null,
  data_evento datetime,
  status int not null,
  foreign key(produto) references produtos(code)
);
