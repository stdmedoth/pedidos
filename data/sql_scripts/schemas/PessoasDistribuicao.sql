create table if not exists PessoasDistribuicao(
  code int primary key not null auto_increment,
  distribuicao int not null,
  pessoa int not null,
  foreign key(distribuicao) references distribuicoes(code),
  foreign key(pessoa) references terceiros(code)
);
