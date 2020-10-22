drop table if exists suporte_posts;
drop table if exists suporte_status;

create table  if not exists suporte_status(
code int primary key auto_increment,
nome varchar(50));

create table  if not exists suporte_tipos(
code int primary key auto_increment,
nome varchar(50));

create table  if not exists suporte_posts(
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

insert into suporte_status(nome)
values('Sem visualização'),
('Visualizado pelo Suporte'),
('Em andamento'),
('Concluído');

insert into suporte_tipos(nome)
values('Encerramento repentino'),
('Inconsistência'),
('Mensagem de erro'),
('Dúvida'),
('Solicitação'),
('Outros');
