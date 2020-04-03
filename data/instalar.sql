drop database if exists erp;
create database erp;
use erp;
create table empresa( cnpj varchar(20) primary key not null, razao varchar(150) not null, endereco varchar(200) not null);
create table ceps(codigo varchar(15), estado varchar(200), cidade varchar (20), bairro varchar(30), logradouro varchar(100), Nome_Edificio varchar(30));
create table terceiros ( code int primary key auto_increment not null, razao varchar(100) not null, doc varchar(20), tipo_doc int not null, tipoc varchar(20) not null, tipo int not null, endereco varchar(100), cep varchar(10), telefone varchar(15), contatot varchar(15), celular varchar(15), contatoc varchar(15), email varchar(100), contatoe varchar(20), obs varchar(500));
create table grupos( code int primary key auto_increment not null, nome varchar(20) not null);
create table unidades( code int primary key auto_increment not null, nome varchar(20) not null, sigla varchar(10) not null, multiplo int not null);
create table produtos( code int primary key auto_increment not null, nome varchar(150) not null, preco float not null, peso float not null, unidade int not null, fornecedor int not null, grupo int not null, marca varchar(30), observacoes varchar(500) not null, foreign key(unidade) references unidades(code), foreign key(fornecedor) references terceiros(code), foreign key(grupo) references grupos(code));
create table estoques( code int primary key auto_increment not null, produto int not null, saldo float not null, entradas int not null, saidas int not null, resultado float not null, foreign key(produto) references produtos(code));
create table precos( code int primary key auto_increment not null, produto int not null, terceiro int, valor float not null, foreign key(produto) references produtos(code), foreign key(terceiro) references terceiros(code));
create table Produto_Venda( code int primary key auto_increment not null, produto int not null, unidades float not null, valor_unit int not null, foreign key(valor_unit) references precos(code));
create table pedidos( cod_venda int not null, vendedor int not null, cliente int not null, dia date not null, total float not null, foreign key(cod_venda) references Produto_Venda(code), foreign key(cliente) references terceiros(code));
create table fatores( code int primary key auto_increment not null, nome varchar(50) not null,observacoes varchar(500) not null);
create table Fatores_Preco( code int primary key auto_increment not null, produto int not null,fator1 int not null,fator2 int, fator3 int,  fator4 int,foreign key(produto) references produtos(code),foreign key(fator1) references fatores(code),foreign key(fator2) references fatores(code),foreign key(fator3) references fatores(code),foreign key(fator4) references fatores(code));

create user if not exists 'petitto'@'%' identified with mysql_native_password by '1234';
grant all privileges on *.* to 'petitto'@'%';
flush privileges;
insert into empresa(razao, endereco, cnpj) values ( 'Petitto Materiais para encadernacaoo e cartonagem', 'R. Dna Amelia de Paula, 100 - Jardim Leonor, Campinas ', 'cnpj');

