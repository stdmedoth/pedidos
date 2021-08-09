create table if not exists operadores( code int primary key auto_increment,
  nome varchar(50) default 'OperadorSemNome',
  senha varchar(50) default '',
  nivel int default 1);
