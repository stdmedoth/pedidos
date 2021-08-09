create table if not exists suporte_posts(
code int primary key,
operador int default 1 not null,
titulo varchar(100) default '' not null,
descricao varchar(1000) default '' not null,
data datetime default '2000-01-01 ' not null,
status int default 1 not null,
prioridade int default 1 not null,
tipo int default 1 not null,
foreign key(operador) references operadores(code),
foreign key(status) references suporte_status(code),
foreign key(tipo) references suporte_tipos(code));
