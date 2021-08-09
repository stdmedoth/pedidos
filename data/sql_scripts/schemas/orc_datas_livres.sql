create table if not exists orc_datas_livres(
  code int primary key auto_increment,
  orcamento int not null,
  pag_cond int not null,
  posicao int not null,
  data_vencimento datetime not null,
  valor float not null);
