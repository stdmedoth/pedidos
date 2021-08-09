create table if not exists pis_cofins(
   code int not null primary key,
   cst varchar(2) not null,
   descricao varchar(126) not null
);
