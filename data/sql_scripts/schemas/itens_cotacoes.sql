create table if not exists itens_cotacoes(
  code int primary key auto_increment not null,
  item_index int not null,
  cotacoes_id int not null,
  participante_id int not null,
  requisicao int not null,
  qnt float not null,
  preco float not null,
  foreign key(requisicao) references prod_requisicoes(code),
  foreign key(cotacoes_id) references cotacoes(code),
  foreign key(participante_id) references terceiros(code)
);
