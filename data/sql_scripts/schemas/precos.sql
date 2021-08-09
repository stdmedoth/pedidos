create table if not exists precos(
  code int primary key auto_increment,
  nome varchar(50) not null,
  produto int default 1,
  valor_fat float default 0.0,
  valor_vist float default 0.0,
  foreign key(produto) references produtos(code));
