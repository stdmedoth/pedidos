create table if not exists ordens_compra(
  code int primary key not null,
  fornecedor int not null,
  dtemissao datetime not null,
  dtentrega datetime not null,
  condpag int not null,
  status int not null,
  foreign key(fornecedor) references terceiros(code),
  foreign key(condpag) references pag_cond(code)
);
