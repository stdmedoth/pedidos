create table prod_requisicoes(
  code int primary key not null,
  produto int not null,
  quantidade int not null,
  descricao varchar(200),
  data datetime not null,
  prioridade int not null,
  data_evento datetime,
  status int not null,
  foreign key(produto) references produtos(code)
);

create table cotacoes(
  code int primary key not null,
  descricao varchar(500) not null,
  status int not null,
  publica int not null,
  data datetime not null,
  validade datetime not null
);

create table cotacoes_participantes(
  code int primary key auto_increment not null,
  cotacoes_id int not null,
  participante int not null,
  foreign key(cotacoes_id) references cotacoes(code),
  foreign key(participante) references terceiros(code)
);

create table itens_cotacoes(
  code int primary key auto_increment not null,
  item_index int not null,
  cotacoes_id int not null,
  participante_id int not null,
  requisicao int not null,
  qnt float not null,
  preco float not null,
  foreign key(produto) references produtos(code),
  foreign key(cotacoes_id) references cotacoes(code),
  foreign key(participante_id) references terceiros(code)
);

create table ordens_compra(
  code int primary key not null,
  produto int not null,
  fornecedor int not null,
  data datetime not null,
  status int not null
);

create table itens_ordens_compra(
  code int primary key not null,
  ordem_id int not null,
  produto int not null,
  qnt float not null,
  preco float not null,
  foreign key(produto) references produtos(code),
  foreign key(ordem_id) references ordens_compra(code)
);

create table compras(
  code int primary key not null,
  fornecedor int not null,
  ordem_id int not null,
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
