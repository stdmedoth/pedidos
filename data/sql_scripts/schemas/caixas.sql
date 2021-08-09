create table if not exists caixas(
    code int primary key auto_increment,
    nome varchar(60) not null,
    status int not null
  );
