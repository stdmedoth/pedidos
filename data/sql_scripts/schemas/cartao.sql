create table if not exists cartao(
  code int primary key not null,
  capa longblob,
  titulo varchar(100) not null,
  descricao varchar(500) not null,
  oper_respn int not null,
  data_criacao datetime not null,
  data_entrega datetime not null,
  status int not null,
  prioridade int not null,
  foreign key (oper_respn) references operadores(code)
);
