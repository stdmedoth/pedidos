create table if not exists cartoes_checklists(
  code int primary key not null,
  cartao int not null,
  nome varchar(30)not null,
  status int not null,
  foreign key (cartao) references cartao(code)
);
