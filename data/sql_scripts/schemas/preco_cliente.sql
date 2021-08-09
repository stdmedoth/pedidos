create table if not exists preco_cliente(
  code int primary key auto_increment,
  produto int default 1,
  cliente int default 1,
  valor_fat float default 0.0,
  valor_vist float default 0.0,
  foreign key(cliente) references terceiros(code));
