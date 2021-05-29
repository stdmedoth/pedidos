create table tipo_terceiros(
  code int primary key,
  nome varchar(100) not null);

create table versao(
  versao varchar(30) not null,
  lancamento datetime not null 
);

create table migrate(
  code int primary key auto_increment,
  descricao varchar(300) not null,
  arquivo varchar(150) not null,
  versao varchar(30) not null,
  lancamento datetime not null 
);

create table if not exists confs(  code int primary key auto_increment,
  navegador_path1 varchar(1000) default '' not null,
  navegador_path2 varchar(1000) default '' not null,
  navegador_pdr int default 1 not null,
  imp_path1 varchar(1000) default '' not null,
  imp_path2 varchar(1000) default '' not null,
  imp_path3 varchar(1000) default '' not null,
  print_logs int not null default 0,
  bd_logs int not null default 0);

create table tecn_pers_elem(
    code int not null,
    path_img_init varchar(1000) not null,
    script_bin_path varchar(1000) not null);

create table if not exists tipo_movimentos( code int primary key,
    id int not null default 0,
    nome varchar(40) default 'TipoMovimentoSemNome'
  );

create table if not exists operadores( code int primary key auto_increment,
  nome varchar(50) default 'OperadorSemNome',
  senha varchar(50) default '',
  nivel int default 1);

create table if not exists setores(
  code int primary key auto_increment,
  nome varchar(30)
);

create table if not exists niveis_gerenciais( code int primary key auto_increment,
  nome varchar(50) default 'NivelGerencialSemNome',
  nivel int default 0);

create table logs( descricao varchar (2000), data datetime);

create table if not exists empresa(
  code int primary key auto_increment,
  cnpj varchar(20) default '',
  razao varchar(150) default 'Empresa Sem Nome',
  ie varchar(20) default '',
  im varchar(20) default '',
  regime_tributario int default 1,
  regime_issqn int default 1,
  digcert_path varchar(255) default '',
  digcert_pass varchar(25) default '',
  cep varchar(15) default '' not null,
  endereco varchar(400) default '' not null,
  bairro  varchar(100) default '' not null,
  cidade varchar(50) default '' not null,
  uf varchar(20) default 'UF' not null,
  numrua int default 0 not null,
  tiporua int default 0 not null,
  telefone varchar(15) default '' not null,
  celular varchar(15) default '' not null,
  smtp varchar(100) default '' not null,
  porta int default 587 not null,
  email varchar(100) default '' not null,
  senhaemail varchar(100) default '' not null,
  sobre varchar(500));

create table if not exists perfil_desktop(
  code int primary key auto_increment,
  desktop_img int default 0,
  tema int default 0,
  janela_init bool default 0,
  janelas_keep_above bool default 0);

create table datas_livres_tab( orcamento int not null,
  posicao int not null,
  data datetime not null,
  valor float not null);

create table if not exists criticas(
  nome varchar(120),
  opcao_nome varchar(30) default 0,
  campo_nome varchar(30) default 0,
  critica bool default 0);


create table if not exists forma_pagamento(
  code int primary key auto_increment, 
  nome varchar(50),
  tipo int default 1);

create table if not exists pag_cond(
  code int primary key auto_increment,
  nome varchar(40) default 'Cond. Pag. sem Nome',
  tipo int default 1,
  forma_pag int, 
  dia_fixo_flag int default 1,
  init_dia int default 1,
  intervalos int default 1,
  qnt_parcelas int default 1,
  foreign key(forma_pag) references forma_pagamento(code)
);

create table if not exists terceiros (
  code int primary key auto_increment,
  code_nfe varchar(15) default '' not null,
  razao varchar(300) default '' not null,
  doc varchar(20) default '' not null,
  ie varchar(20) default 'IE' not null,
  tipo_doc int default 0 not null,
  tipoc varchar(20) default 0 not null,
  tipo int default 0 not null,
  cep varchar(15) default '' not null,
  endereco varchar(400) default '' not null,
  complmt varchar(20) default '' not null,
  bairro  varchar(100) default '' not null,
  cidade varchar(50) default '' not null,
  uf varchar(20) default 'UF' not null,
  numrua int default 0 not null,
  tiporua int default 0 not null,

  transp_code int default 0 not null,
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
  prazo int,
  obs varchar(500) default '' not null,
  foreign key(prazo) references pag_cond(code));

create table if not exists contatos (
  code int primary key auto_increment,
  terceiro int not null,
  nome varchar(30) default '' not null,
  telefone varchar(15) default '' not null,
  celular varchar(15) default '' not null,
  email varchar(100) default '' not null);

create table if not exists preco_cliente(
  code int primary key auto_increment,
  produto int default 1,
  cliente int default 1,
  valor_fat float default 0.0,
  valor_vist float default 0.0,
  foreign key(cliente) references terceiros(code));


create table if not exists wnd_logger(id_janela int,
  nome_janela varchar(100),
  estado int,
  qnt_aberta int,
  operador int,
  tempo datetime);

create table if not exists cidade (
  code int(11) NOT NULL AUTO_INCREMENT,
  descricao varchar(100) DEFAULT '',
  uf varchar(2)  DEFAULT '',
  codigo_ibge int(11)  DEFAULT 0,
  ddd varchar(2)  DEFAULT '',
  PRIMARY KEY (code),
  KEY code (code) USING BTREE,
  KEY cidade (code,
  uf) USING BTREE,
  KEY cidade_estado (uf) USING BTREE);

create table if not exists logradouro (
  code int(10) unsigned NOT NULL AUTO_INCREMENT,
  CEP varchar(11) NOT NULL,
  tipo varchar(50) DEFAULT '',
  descricao varchar(100)  DEFAULT '',
  id_cidade int(11)  DEFAULT 0,
  UF varchar(2)  DEFAULT '',
  complemento varchar(100) DEFAULT '',
  descricao_sem_numero varchar(100) DEFAULT '',
  descricao_cidade varchar(100) DEFAULT '',
  codigo_cidade_ibge int(11) DEFAULT 0,
  descricao_bairro varchar(100) DEFAULT '',
  PRIMARY KEY (code),
  KEY cep (CEP) USING BTREE,
  KEY cidade (code,
  UF) USING BTREE,
  CONSTRAINT FK_cidade_2 FOREIGN KEY (id_cidade) REFERENCES cidade (code));

create table if not exists estados( code int primary key auto_increment,
sigla varchar(5) not null default 'UF',
nome varchar(100) not null default 'Estado');

create table if not exists maquinas(
  code int primary key auto_increment,
  nome varchar(50) not null,
  ip varchar(15),
  hostname varchar(20),
  ativa tinyint not null
);

create table if not exists contratos(
  code int primary key auto_increment,
  cadastro int default 0,
  compras int default 0,
  faturamento int default 0,
  estoque int default 0,
  financeiro int default 0,
  marketing int default 0,
  relatorios int default 0,
  ativo int default 1,
  data_vencimento datetime default '2049-12-31');
