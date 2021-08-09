create table if not exists relat_tabelas_id( code int primary key auto_increment,
nome varchar(50) not null,
sobre varchar(300),
inner_query varchar(1000),
qnt_colunas int);
