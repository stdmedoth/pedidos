create table if not exists niveis_gerenciais( code int primary key auto_increment,
  nome varchar(50) default 'NívelGerencialSemNome',
  nivel int default 0);
