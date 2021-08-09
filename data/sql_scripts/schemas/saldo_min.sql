create table if not exists saldo_min( code int primary key auto_increment,
  produto int  not null default 1,
  saldo_min float  not null default 0.0,
  estoque int  not null default 1,
  foreign key(produto) references produtos(code),
  foreign key(estoque) references estoques(code));
