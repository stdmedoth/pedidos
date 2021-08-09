create table if not exists titulos(
  code int primary key,
  cliente int not null,
  pedido int not null,
  status int not null,
  qnt_parcelas int not null,
  tipo_titulo int not null,
  foreign key (cliente) references terceiros(code));
