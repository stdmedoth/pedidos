create table if not exists movimentos_caixa(
  code int primary key auto_increment,
  caixa int not null,
  data datetime not null,
  operacao int not null,
  dinheiro float not null default 0,
  cheque float not null default 0,
  cartao float not null default 0,
  total float not null default 0,
  descricao varchar(50) not null,
  foreign key(caixa) references caixas(code)
);
