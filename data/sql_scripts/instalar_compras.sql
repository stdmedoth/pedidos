create table prod_requisicoes(
  code int primary key not null,
  descricao varchar(200),
  data datetime not null,
  prioridade int not null,
  data_evento datetime,
  status int not null
);

create table compras(
  code int primary key not null,
  fornecedor int not null,
  data datetime not null,
  vlr_total float not null,
  foreign key(fornecedor) references terceiros(code)
);

create table itens_compras(
  code int primary key not null,
  compra_id int not null,
  produto int not null,
  foreign key(produto) references produtos(code),
  foreign key(compra_id) references compras(code)
);
