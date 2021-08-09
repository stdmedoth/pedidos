create table if not exists maquinas(
  code int primary key auto_increment,
  nome varchar(50) not null,
  ip varchar(15),
  hostname varchar(20),
  ativa tinyint not null
);
