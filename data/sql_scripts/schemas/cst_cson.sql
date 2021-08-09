create table if not exists cst_cson(
  code int not null primary key,
  charIdTrib varchar(3) not null,
  nome varchar(200),
  regime int not null
);
