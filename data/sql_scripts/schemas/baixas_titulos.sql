create table if not exists baixas_titulos(
  code int primary key auto_increment,
  parcelas_id int not null,
  posicao int not null,
  id_baixa int not null,
  data_criacao datetime,
  valor float default 0 not null,
  foreign key(parcelas_id) references parcelas_tab(parcelas_id));
