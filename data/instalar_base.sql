create database if not exists erp;
use erp;

drop table if exists tipo_pagamento;
drop table if exists movimento_estoque;
drop table if exists estoques;
drop table if exists faturamento;
drop table if exists Produto_Orcamento;
drop table if exists orcamentos;
drop table if exists pedidos;
drop table if exists preco_cliente;
drop table if exists preco_grupo;
drop table if exists precos;
drop table if exists tipo_movimentos;
drop table if exists operadores;
drop table if exists empresa;
drop table if exists perfil_desktop;
drop table if exists pag_cond;
drop table if exists criticas;
drop table if exists produtos;
drop table if exists grupos;
drop table if exists unidades;
drop table if exists terceiros;
drop table if exists logs;

create table if not exists tipo_movimentos( code int primary key,
  nome varchar(40) default 'TipoMovimentoSemNome'
);

create table if not exists operadores( code int primary key auto_increment,
nome varchar(50) default 'OperadorSemNome',
senha varchar(50) default '',
nivel int default 1);

create table if not exists niveis_gerenciais( code int primary key auto_increment,
nome varchar(50) default 'NivelGerencialSemNome',
nivel int default 1);

create table logs( descricao varchar (2000), data datetime);

create table if not exists empresa( cnpj varchar(20) primary key default 'cnpj',
razao varchar(150) default 'Empresa Sem Nome',
endereco varchar(200) default 'Endereço Vazio');

create table if not exists perfil_desktop(code int primary key auto_increment,
desktop_img int default 0,
tema int default 0,
janela_init bool default 0,
janelas_keep_above bool default 0);

create table if not exists pag_cond(code int primary key auto_increment,
nome varchar(40) default 'Cond. Pag. sem Nome',
tipo int default 1,
dia_fixo_flag int default 1,
init_dia int default 1,
intervalos int default 1,
qnt_parcelas int default 1);

create table if not exists criticas(nome varchar(120),
opcao_nome varchar(30) default 0,
campo_nome varchar(30) default 0,
critica bool default 0);

create table if not exists terceiros ( code int primary key auto_increment,
code_nfe varchar(15) default '' not null,
razao varchar(300) default '' not null,
doc varchar(20) default '' not null,
ie varchar(20) default 'IE' not null,
tipo_doc int default 0 not null,
tipoc varchar(20) default 0 not null,
tipo int default 0 not null,
cep varchar(15) default '' not null,
endereco varchar(400) default '' not null,
bairro  varchar(100) default '' not null,
cidade varchar(50) default '' not null,
uf varchar(20) default 'UF' not null,
numrua int default 0 not null,
tiporua int default 0 not null,
telefone varchar(15) default '' not null,
contatot varchar(15) default '' not null,
celular varchar(15) default '' not null,
contatoc varchar(15) default '' not null,
email varchar(100) default '' not null,
contatoe varchar(20) default '' not null,

transp_nome varchar(300) default '' not null,
transp_cnpj varchar(20) default '' not null,
transp_ie varchar(20) default '' not null,
transp_logradouro varchar(400) default '' not null,
transp_num int default 0 not null,
transp_bairro varchar(100) default '' not null,
transp_cidade varchar(100) default '' not null,
transp_estado varchar(20) default 'UF' not null,
transp_cep varchar(15) default '' not null,
transp_telefone varchar(20) default '' not null,
transp_obs varchar(500) default '' not null,

frete_pago bool default 0 not null,
vlr_frete_pago float default 0 not null,
prazo varchar(20) default '' not null,
obs varchar(500) default '' not null);

create table if not exists grupos( code int primary key auto_increment,
pai int default 0,
nome varchar(50) default 'Grupo Sem Nome',
nivel int default 1 );

create table if not exists unidades( code int primary key auto_increment,
nome varchar(50) default '',
sigla varchar(10) default '',
multiplo int default 1,
medida int default 0);

create table if not exists produtos( code int primary key auto_increment,
nome varchar(150) default 'Produto Sem Nome',
peso float default 0.0,
unidades int default 1,
unidades_atacado int default 1,
fornecedor int default 1,
grupo int default 1,
grupo_nivel int default 2,
observacoes varchar(500) default '',
foreign key(unidades) references unidades(code),
foreign key(fornecedor) references terceiros(code),
foreign key(grupo) references grupos(code) );

create table if not exists precos( code int primary key auto_increment,
produto int default 1,
terceiro int default 1,
valor_fat float default 0.0,
valor_vist float default 0.0,
foreign key(produto) references produtos(code),
foreign key(terceiro) references terceiros(code));

create table preco_grupo( code int primary key auto_increment,
produto int default 1,
grupo int default 1,
valor_fat float default 0.0,
valor_vist float default 0.0,
foreign key(grupo) references grupos(code));

create table if not exists preco_cliente( code int primary key auto_increment,
produto int default 1,
grupo int default 1,
cliente int default 1,
valor_fat float default 0.0,
valor_vist float default 0.0,
foreign key(cliente) references terceiros(code));

create table if not exists pedidos( code int primary key auto_increment,
vendedor int default 1,
cliente int default 1,
data_mov date default '2001-01-01',
total float default 0.0,
status int default 0,
foreign key(cliente) references terceiros(code));

create table if not exists orcamentos( code int primary key auto_increment,
vendedor int default 0,
cliente int default 0,
dia date default '2001-01-01',
pag_cond int default 1,
total float default 0,
observacoes varchar(500) default '',
foreign key(cliente) references terceiros(code));

create table if not exists Produto_Orcamento( code int,
item int default 1,
produto int default 0,
subgrupo int default 0,
unidades float default 0.0,
valor_unit float default 0.0,
valor_orig int default 0,
tipodesc int default 0,
desconto float default 0.0,
total float default 0.0,
observacoes varchar(500) default '',
foreign key(code) references orcamentos(code));

create table if not exists faturamento ( code int primary key auto_increment,
pedido int default 0,
cliente int default 0,
entrada float default 0.0,
saida float default 0.0,
data_mov date default '2001-01-01',
tipo_mov int default 0 );

create table if not exists estoques( code int primary key auto_increment,
nome varchar(20) default 'Estoque Sem Nome');

create table if not exists movimento_estoque( code int primary key auto_increment,
estoque int default 1,
pedido int default 0,
cliente int default 0,
produto int default 0,
subgrupo int default 0,
entradas float default 0,
saidas float default 0,
data_mov date default '2001-01-01',
tipo_mov int default 0,
foreign key(estoque) references estoques(code),
foreign key(produto) references produtos(code),
foreign key(subgrupo) references grupos(code));

create table if not exists tipo_pagamento( code int, nome varchar(50));

create table if not exists cidade (id_cidade int(11) NOT NULL AUTO_INCREMENT,
descricao varchar(100) DEFAULT NULL,
uf varchar(2) DEFAULT NULL,
codigo_ibge int(11) DEFAULT NULL,
ddd varchar(2) DEFAULT NULL,
PRIMARY KEY (id_cidade),
KEY id (id_cidade) USING BTREE,
KEY cidade (id_cidade,
uf) USING BTREE,
KEY cidade_estado (uf) USING BTREE);


create table if not exists logradouro (  CEP varchar(11) NOT NULL,
id_logradouro int(10) unsigned NOT NULL AUTO_INCREMENT,
tipo varchar(50) DEFAULT NULL,
descricao varchar(100) NOT NULL,
id_cidade int(11) NOT NULL,
UF varchar(2) NOT NULL,
complemento varchar(100) DEFAULT NULL,
descricao_sem_numero varchar(100) DEFAULT NULL,
descricao_cidade varchar(100) DEFAULT NULL,
codigo_cidade_ibge int(11) DEFAULT NULL,
descricao_bairro varchar(100) DEFAULT NULL,
PRIMARY KEY (id_logradouro),
KEY cep (CEP) USING BTREE,
KEY cidade (id_cidade,
UF) USING BTREE,
CONSTRAINT FK_cidade_2 FOREIGN KEY (id_cidade) REFERENCES cidade (id_cidade));
