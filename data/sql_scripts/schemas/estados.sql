create table if not exists estados( code int primary key auto_increment,
sigla varchar(5) not null default 'UF',
nome varchar(100) not null default 'Estado');
