create table if not exists eventos_caixa(
  code int primary key auto_increment,
  caixa int not null,
  operador int not null,
  maquina int not null,
  data datetime not null,
  tipo int not null,
  foreign key(caixa) references caixas(code),
  foreign key(operador) references operadores(code),
  foreign key(maquina) references maquinas(code)
);
