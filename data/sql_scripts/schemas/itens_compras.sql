create table if not exists itens_compras(
  code int primary key not null,
  compra_id int not null,
  produto int not null,
  foreign key(produto) references produtos(code),
  foreign key(compra_id) references compras(code)
);
