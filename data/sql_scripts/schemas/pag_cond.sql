create table if not exists pag_cond(
  code int primary key auto_increment,
  nome varchar(40) default 'Cond. Pag. sem Nome',
  tipo int default 1,
  forma_pag int,
  dia_fixo_flag int default 1,
  init_dia int default 1,
  intervalos int default 1,
  qnt_parcelas int default 1,
  foreign key(forma_pag) references forma_pagamento(code)
);
