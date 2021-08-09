create table if not exists contatos (
  code int primary key auto_increment,
  terceiro int not null,
  nome varchar(30) default '' not null,
  telefone varchar(15) default '' not null,
  celular varchar(15) default '' not null,
  email varchar(100) default '' not null);
