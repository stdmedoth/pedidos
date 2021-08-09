create table if not exists emails_model(
  code int primary key not null,
  nome varchar(50) not null,
  assunto varchar(50),
  tipo int not null,
  setor int not null
);
