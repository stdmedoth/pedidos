drop database if exists erp;
#criar banco
create database erp;
use erp;
#tabela da empresa

create table 
empresa(razao varchar(100) not null,
endereco varchar(100) not null,
cnpj varchar(100) not null,
primary key(cnpj));
insert into 
empresa(razao,endereco,cnpj) 
values('empresa','endereco','cnpj');
#tabela de produtos cadastrados

create table 
produtos(code int(100) not null,
name varchar(100) not null, 
price float not null, 
tabela1 float,
tabela2 float,
tabela3 float,
supplier varchar(100) not null,
primary key(code));
#tabela dos terceiros cadastrados

create table 
terceiros(code int(100) not null,
name varchar(100) not null,
address varchar(100)not null,
preco real,
type varchar(100)not null,
primary key(code));

create table 
unidades(code int(100) not null,
name varchar(100) not null,
sigla varchar(100)not null,
multiplo int(100)not null,
primary key(code));

create user if not exists 'petitto'@'localhost' 
identified with mysql_native_password by '1234';
grant all privileges on *.* to 'petitto'@'localhost';

create user if not exists 'petitto'@'%' 
identified with mysql_native_password by '1234';
grant all privileges on *.* to 'petitto'@'%';

flush privileges;
