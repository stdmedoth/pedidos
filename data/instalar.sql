drop database if exists erp;
create database erp;
use erp;
create table empresa(
cnpj varchar(20) primary key not null,
razao varchar(150) not null,
endereco varchar(200) not null);

create table unidades( 
code int primary key auto_increment not null,
nome varchar(20) not null,
sigla varchar(10) not null,
multiplo int not null);

create table 
terceiros (
code int primary key auto_increment not null,
razao varchar(100) not null,
cnpj varchar(20),
tipoc varchar(100) not null,
tipo int not null,
endereco varchar(100),
cep varchar(10),
telefone1 varchar(15),
telefone2 varchar(15),
celular1 varchar(15),
celular2 varchar(15),
email varchar(100),
contato varchar(20),
obs varchar(500));

create table produtos(
code int primary key auto_increment not null, 
nome varchar(150) not null, 
tabela1 float, 
tabela2 float,
tabela3 float,
unidade int not null,
fornecedor int not null,
foreign key(unidade) references unidades(code),
foreign key(fornecedor) references terceiro(code));

create table precos(
code int primary key auto_increment not null,
produto int not null, 
terceiro int, 
valor float not null, 
foreign key(terceiro) references terceiros(code),
foreign key(produto) references produtos(code));

create user if not exists 'petitto'@'%' identified with mysql_native_password by '1234';
grant all privileges on *.* to 'petitto'@'%';

flush privileges;

insert into 
empresa(razao,endereco,cnpj) 
values('empresa','endereco','cnpj');
