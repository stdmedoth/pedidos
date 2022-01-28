create table if not exists produto_orcamento(
  code int,
  item int default 1,
  produto int default 0,
  unidades float default 0.0,
  valor_unit float default 0.0,
  valor_orig int default 0,
  tipodesc int default 0,
  desconto float default 0.0,
  total float default 0.0,
  observacoes varchar(500) default '',
  foreign key(code) references orcamentos(code),
  foreign key(produto) references produtos(code)
);
