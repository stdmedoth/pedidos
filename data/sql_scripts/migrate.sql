alter table titulos add foreign key (cliente) references terceiros(code); 

alter table parcelas_tab add foreign key (banco) references bancos(code); 

create table cheque(
  code int primary key auto_increment,
  banco varchar(50) not null,
  conta varchar(50) not null,
  serie varchar(20) not null,
  numero varchar(20) not null,
  pagante int not null, 
  data_emissao datetime not null,
  valor float not null);

create table agencia(
  code int primary key auto_increment,
  nome varchar(50) not null,
  endereco varchar(50));

alter table pedidos change banco banco int default NULL;
alter table parcelas_tab change banco banco int default NULL;
alter table forma_pagamento add tipo int default 1;

create table orcs_cheques(
  code int primary key auto_increment,
  orcamento int not null,
  cheque int not null,
  foreign key(orcamento) references orcamentos(code),
  foreign key(cheque) references cheque(code));

alter table contatos change code code int primary key auto_increment;