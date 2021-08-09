create table if not exists compras(
  code int primary key not null,
  fornecedor int not null,
  ordem_id int not null,
  data datetime not null,
  vlr_total float not null,
  foreign key(fornecedor) references terceiros(code)
);
