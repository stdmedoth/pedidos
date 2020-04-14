drop database if exists erp;
create database erp;
use erp;

create table operadores( code int primary key not null, nome varchar(20) not null, senha varchar(20) not null,nivel int not null);
create table empresa( cnpj varchar(20) primary key not null, razao varchar(150) not null, endereco varchar(200) not null);
create table perfil_desktop(code int primary key,desktop_img int,cor_barra varchar(30),janela_init bool,janelas_keep_above bool);
create table criticas(opcao_nome varchar(20) not null, campo_nome varchar(20) not null, critica bool);
create table terceiros ( code int primary key auto_increment not null, razao varchar(100) not null, doc varchar(20), tipo_doc int not null, tipoc varchar(20), tipo int, cep varchar(10) , endereco varchar(400), tiporua int, telefone varchar(15), contatot varchar(15), celular varchar(15), contatoc varchar(15), email varchar(100), contatoe varchar(20), obs varchar(500));
create table grupos( code int primary key auto_increment not null, nome varchar(20) not null);
create table unidades( code int primary key auto_increment not null, nome varchar(20) not null, sigla varchar(10) not null, multiplo int not null);
create table produtos( code int primary key auto_increment not null, nome varchar(150) not null, preco float not null, peso float not null, unidade int not null, fornecedor int not null, grupo int not null, marca varchar(30), observacoes varchar(500) not null, foreign key(unidade) references unidades(code), foreign key(fornecedor) references terceiros(code), foreign key(grupo) references grupos(code));
create table estoques( code int primary key auto_increment not null, produto int not null, saldo float not null, entradas int not null, saidas int not null, resultado float not null, foreign key(produto) references produtos(code));
create table precos( code int primary key auto_increment not null, produto int not null, terceiro int, valor float not null, foreign key(produto) references produtos(code), foreign key(terceiro) references terceiros(code));
create table pedidos( code int primary key auto_increment not null, vendedor int not null, cliente int not null, dia date not null, total float not null,  foreign key(cliente) references terceiros(code));
create table orcamentos( code int primary key auto_increment not null, vendedor int not null, cliente int not null, dia date not null, total float not null, observacoes varchar (500),foreign key(cliente) references terceiros(code));
create table Produto_Orcamento( code int not null,item int not null, produto int not null, unidades float not null, valor_unit float not null, desconto float, total float not null,foreign key(code) references orcamentos(code));
create table Produto_Venda( code int auto_increment not null,item int not null, produto int not null, unidades float not null, valor_unit int not null,desconto float, total float not null,foreign key(code) references pedidos(code),foreign key(valor_unit) references precos(code));
create table fatores( code int primary key auto_increment not null, nome varchar(50) not null,observacoes varchar(500) not null);
create table Fatores_Preco( code int primary key auto_increment not null, produto int not null,fator1 int not null,fator2 int, fator3 int,  fator4 int,foreign key(produto) references produtos(code),foreign key(fator1) references fatores(code),foreign key(fator2) references fatores(code),foreign key(fator3) references fatores(code),foreign key(fator4) references fatores(code));
create table cidade (id_cidade int(11) NOT NULL AUTO_INCREMENT,descricao varchar(100) DEFAULT NULL,uf varchar(2) DEFAULT NULL,codigo_ibge int(11) DEFAULT NULL,ddd varchar(2) DEFAULT NULL,PRIMARY KEY (id_cidade),KEY id (id_cidade) USING BTREE,KEY cidade (id_cidade,uf) USING BTREE,KEY cidade_estado (uf) USING BTREE);
create table logradouro (  CEP varchar(11) NOT NULL,id_logradouro int(10) unsigned NOT NULL AUTO_INCREMENT,tipo varchar(50) DEFAULT NULL,descricao varchar(100) NOT NULL,id_cidade int(11) NOT NULL,UF varchar(2) NOT NULL,complemento varchar(100) DEFAULT NULL,descricao_sem_numero varchar(100) DEFAULT NULL,descricao_cidade varchar(100) DEFAULT NULL,codigo_cidade_ibge int(11) DEFAULT NULL,descricao_bairro varchar(100) DEFAULT NULL,PRIMARY KEY (id_logradouro),KEY cep (CEP) USING BTREE,KEY cidade (id_cidade,UF) USING BTREE,CONSTRAINT FK_cidade_2 FOREIGN KEY (id_cidade) REFERENCES cidade (id_cidade));
create user if not exists 'petitto'@'%' identified with mysql_native_password by '1234';
grant all privileges on *.* to 'petitto'@'%';
flush privileges;
insert into criticas(opcao_nome,campo_nome,critica) 
values('terceiros','ter_doc',1),('terceiros','ter_tipo_doc',1),('terceiros','ter_endereco',1),('terceiros','ter_cep',1),
('terceiros','ter_tipo',1),('terceiros','ter_celular',1),('terceiros','ter_contatoc',1),('terceiros','ter_telefone',1),('terceiros','ter_contatot',1),
('terceiros','ter_email',1),('terceiros','ter_contatoe',1);
insert into operadores values(1,'Petitto','1234',5),(999,'Padrao',' ',5);
insert into empresa(razao, endereco, cnpj) values ( 'Petitto Mat. p/ encadern. e carton.', 'R. Dna Amelia de Paula, 100\nJardim Leonor, Campinas ', '---');
insert into grupos(nome) values('Ferramentas'),('Cilindros'),('Papelao');
insert into unidades(nome,sigla,multiplo) values('Caixas','CX',30),('Unidade','UND',1);
insert into perfil_desktop(code, desktop_img,cor_barra,janela_init,janelas_keep_above) values(1,3,1,1,1),(999,3,1,1,1);
