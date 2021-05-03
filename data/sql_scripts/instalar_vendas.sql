create table if not exists pedidos( 
  code int primary key auto_increment,
  tipo_mov int default 1,
  vendedor int default 1,
  cliente int default 1,
  data_mov date default '2001-01-01',
  pag_cond int default 1,
  banco int default NULL,
  total float default 0.0,
  status int default 0,
  foreign key(cliente) references terceiros(code));

create table if not exists orcamentos(
  code int primary key auto_increment,
  tipo_mov int default 1,
  vendedor int default 0,
  cliente int default 0,
  dia date default '2001-01-01',
  pag_cond int default 1,
  banco int default NULL,
  cheque int default NULL,
  total float default 0,
  observacoes varchar(500) default '',
  foreign key(cliente) references terceiros(code));

create table if not exists Produto_Orcamento(
  code int,
  item int default 1,
  produto int default 0,
  unidades float default 0.0,
  valor_unit float default 0.0,
  valor_orig int default 0,
  tipodesc int default 0,
  desconto float default 0.0,
  total float default 0.0,
  observacoes varchar(500) default '',
  foreign key(code) references orcamentos(code),
  foreign key(produto) references produtos(code)
);


create table if not exists faturamento ( code int primary key auto_increment,
  pedido int default 0,
  cliente int default 0,
  entrada float default 0.0,
  saida float default 0.0,
  data_mov date default '2001-01-01',
  tipo_mov int default 0 );

create table if not exists caixas(
    code int primary key auto_increment,
    nome varchar(60) not null,
    status int not null
  );

create table if not exists movimentos_caixa(
  code int primary key auto_increment,
  caixa int not null,
  data datetime not null,
  operacao int not null,
  dinheiro float not null default 0,
  cheque float not null default 0,
  cartao float not null default 0,
  total float not null default 0,
  descricao varchar(50) not null,
  foreign key(caixa) references caixas(code)
);

create table if not exists eventos_caixa(
  code int primary key auto_increment,
  caixa int not null,
  operador int not null,
  maquina int not null,
  data datetime not null,
  tipo int not null,
  foreign key(caixa) references caixas(code),
  foreign key(operador) references operadores(code),
  foreign key(maquina) references maquinas(code)
);

create table if not exists meios_pagamento(
  code int primary key not null,
  nome varchar(50)
);

create table credenciadoras(
    code int primary key not null,
    cod_cred varchar(4),
    nome varchar(300),
    cnpj varchar(20)
);


/* CREATE TABLE */
CREATE TABLE cfops(
_GRUPO_CFOP_ VARCHAR(2000),
CFOP DOUBLE,
DESCRIO_CFOP VARCHAR(2000),
Incio_Vigncia datetime default now()
);
