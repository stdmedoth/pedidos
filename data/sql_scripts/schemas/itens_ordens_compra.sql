create table if not exists itens_ordens_compra(
  code int primary key auto_increment not null,
  ordem_id int not null,
  itens_cotacao int not null,
  foreign key(ordem_id) references ordens_compra(code),
  foreign key(itens_cotacao) references itens_cotacoes(code)
);
