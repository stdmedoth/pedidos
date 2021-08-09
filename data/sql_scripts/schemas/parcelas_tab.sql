create table if not exists parcelas_tab(
  parcelas_id int not null,
  posicao int not null,
  banco int default NULL,
  data_criacao datetime,
  data_vencimento datetime,
  valor float default 0 not null,
  foreign key(parcelas_id) references titulos(code),
  foreign key (banco) references bancos(code));
