create table tipo_terceiros(
  code int primary key,
  nome varchar(100) not null);

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
  nome varchar(50) default 'NívelGerencialSemNome',
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

create table if not exists grupos( code int primary key auto_increment,
  pai int default 0,
  nome varchar(50) default 'Grupo Sem Nome',
  nivel int default 1 );

create table if not exists unidades( code int primary key auto_increment,
  nome varchar(50) default '',
  sigla varchar(10) default '',
  multiplo int default 1,
  medida int default 0);

create table pis_cofins(
   code int not null primary key,
   cst varchar(2) not null,
   descricao varchar(126) not null
);

CREATE TABLE IF NOT EXISTS `IcmsInterestadual` (
  `code` int(11) NOT NULL AUTO_INCREMENT,
  `origem` varchar(2) NOT NULL,
  `destino` varchar(2) NOT NULL,
  `icms` decimal(10,2) NOT NULL,
  PRIMARY KEY (`code`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=730 ;

CREATE TABLE IF NOT EXISTS `ncm` (
  `code` INT(16) NOT NULL AUTO_INCREMENT ,
  `cod_ncm` VARCHAR(8) NOT NULL ,
  `nome_ncm` VARCHAR(128) NOT NULL ,
  PRIMARY KEY (`code`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;

CREATE INDEX `descricao` ON `ncm` (`nome_ncm` ASC) ;

create table prod_origem(
  code int not null primary key,
  idOrigem int not null,
  nome varchar(200),
  aliquota float
);

create table cst_cson(
  code int not null primary key,
  charIdTrib varchar(3) not null,
  nome varchar(200),
  regime int not null
);

CREATE TABLE  produtos(
  code int(11) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  nome varchar(150) DEFAULT 'Produto Sem Nome',
  peso float DEFAULT '0',
  preco float DEFAULT '0',
  unidades int(11) DEFAULT '1',
  unidades_atacado int(11) DEFAULT '1',
  fornecedor int(11) DEFAULT '1',
  grupo int(11) DEFAULT '1',
  grupo_nivel int(11) DEFAULT '2',
  ncm int NOT NULL ,
  code_barra varchar(20),
  icmscst int NOT NULL ,
  piscst int NOT NULL ,
  pisaliq float not null,
  cofinscst int NOT NULL,
  cofinsaliq float not null,
  origem int NOT NULL,
  observacoes varchar(500) DEFAULT '',
  dt_criacao datetime,
  dt_modificacao datetime,
  FOREIGN KEY (unidades) REFERENCES unidades(code),
  FOREIGN KEY (fornecedor) REFERENCES terceiros(code),
  FOREIGN KEY (grupo) REFERENCES grupos(code),
  FOREIGN KEY (ncm) REFERENCES ncm(code),
  FOREIGN KEY (icmscst) REFERENCES cst_cson(code),
  FOREIGN KEY (piscst) REFERENCES pis_cofins(code),
  FOREIGN KEY (cofinscst) REFERENCES pis_cofins(code),
  FOREIGN KEY (origem) REFERENCES prod_origem(code)
);

create table if not exists precos(
  code int primary key auto_increment,
  nome varchar(50) not null,
  produto int default 1,
  valor_fat float default 0.0,
  valor_vist float default 0.0,
  foreign key(produto) references produtos(code));

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

create table if not exists produto_orcamento(
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


CREATE TABLE cfops(
_GRUPO_CFOP_ VARCHAR(2000),
CFOP DOUBLE,
DESCRIO_CFOP VARCHAR(2000),
Incio_Vigncia datetime default '2021-01-01'
);

create table titulos(
  code int primary key,
  cliente int not null,
  pedido int not null,
  status int not null,
  qnt_parcelas int not null,
  tipo_titulo int not null,
  foreign key (cliente) references terceiros(code));

create table bancos(
  code int primary key auto_increment,
  nome varchar(100) not null,
  conta varchar(30) not null,
  tipoconta int not null,
  agencia varchar(10) not null,
  nome_usuario  varchar(200) not null,
  documento  varchar(30) not null,
  saldo_inicial float not null);

create table parcelas_tab(
  parcelas_id int not null,
  posicao int not null,
  banco int default NULL,
  data_criacao datetime,
  data_vencimento datetime,
  valor float default 0 not null,
  foreign key(parcelas_id) references titulos(code),
  foreign key (banco) references bancos(code));

create table baixas_titulos(
  code int primary key auto_increment,
  parcelas_id int not null,
  posicao int not null,
  id_baixa int not null,
  data_criacao datetime,
  valor float default 0 not null,
  foreign key(parcelas_id) references parcelas_tab(parcelas_id));

create table orc_datas_livres(
  code int primary key auto_increment,
  orcamento int not null,
  pag_cond int not null,
  posicao int not null,
  data_vencimento datetime not null,
  valor float not null);

create table agencia(
  code int primary key auto_increment,
  nome varchar(50) not null,
  endereco varchar(50));

create table cheque(
  code int primary key auto_increment,
  banco varchar(50) not null,
  conta varchar(50) not null,
  serie varchar(20) not null,
  numero varchar(20) not null,
  pagante int not null,
  status int not null,
  tipo int not null,
  data_emissao datetime not null,
  valor float not null);

create table cheque_finan(
  code int primary key auto_increment,
  cheque int not null,
  titulo int not null,
  foreign key(cheque) references cheque(code),
  foreign key(titulo) references titulos(code));

create table orcs_cheques(
  code int primary key auto_increment,
  orcamento int not null,
  cheque int not null,
  foreign key(orcamento) references orcamentos(code),
  foreign key(cheque) references cheque(code));

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

create table if not exists estoques( code int primary key auto_increment,
  nome varchar(20) default 'Estoque Sem Nome');

create table if not exists movimento_estoque( code int primary key auto_increment,
  estoque int default 1,
  pedido int default 0,
  cliente int default 0,
  produto int default 0,
  entradas float default 0,
  saidas float default 0,
  data_mov date default '2001-01-01',
  tipo_mov int default 0,
  obs varchar(100) default '',
  foreign key(estoque) references estoques(code),
  foreign key(produto) references produtos(code));

create table saldo_min( code int primary key auto_increment,
  produto int  not null default 1,
  saldo_min float  not null default 0.0,
  estoque int  not null default 1,
  foreign key(produto) references produtos(code),
  foreign key(estoque) references estoques(code));

create table saldo_max( code int primary key auto_increment,
  produto int  not null default 1,
  saldo_max float  not null default 0.0,
  estoque int  not null default 1,
  foreign key(produto) references produtos(code),
  foreign key(estoque) references estoques(code));

create table cartao(
  code int primary key not null,
  capa longblob,
  titulo varchar(100) not null,
  descricao varchar(500) not null,
  oper_respn int not null,
  data_criacao datetime not null,
  data_entrega datetime not null,
  status int not null,
  prioridade int not null,
  foreign key (oper_respn) references operadores(code)
);

create table cartoes_checklists(
  code int primary key not null,
  cartao int not null,
  nome varchar(30)not null,
  status int not null,
  foreign key (cartao) references cartao(code)
);

create table historico(
  code int primary key not null,
  descricao varchar(200) not null,
  data datetime not null
);

create table prod_requisicoes(
  code int primary key not null,
  produto int not null,
  quantidade float not null,
  descricao varchar(200),
  data datetime not null,
  prioridade int not null,
  data_evento datetime,
  status int not null,
  foreign key(produto) references produtos(code)
);

create table cotacoes(
  code int primary key not null,
  descricao varchar(500) not null,
  status int not null,
  publica int not null,
  data datetime not null,
  validade datetime not null
);

create table cotacoes_participantes(
  code int primary key auto_increment not null,
  cotacoes_id int not null,
  participante int not null,
  foreign key(cotacoes_id) references cotacoes(code),
  foreign key(participante) references terceiros(code)
);

create table itens_cotacoes(
  code int primary key auto_increment not null,
  item_index int not null,
  cotacoes_id int not null,
  participante_id int not null,
  requisicao int not null,
  qnt float not null,
  preco float not null,
  foreign key(requisicao) references prod_requisicoes(code),
  foreign key(cotacoes_id) references cotacoes(code),
  foreign key(participante_id) references terceiros(code)
);

create table ordens_compra(
  code int primary key not null,
  fornecedor int not null,
  dtemissao datetime not null,
  dtentrega datetime not null,
  condpag int not null,
  status int not null,
  foreign key(fornecedor) references terceiros(code),
  foreign key(condpag) references pag_cond(code)
);

create table itens_ordens_compra(
  code int primary key auto_increment not null,
  ordem_id int not null,
  itens_cotacao int not null,
  foreign key(ordem_id) references ordens_compra(code),
  foreign key(itens_cotacao) references itens_cotacoes(code)
);

create table compras(
  code int primary key not null,
  fornecedor int not null,
  ordem_id int not null,
  data datetime not null,
  vlr_total float not null,
  foreign key(fornecedor) references terceiros(code)
);

create table itens_compras(
  code int primary key not null,
  compra_id int not null,
  produto int not null,
  foreign key(produto) references produtos(code),
  foreign key(compra_id) references compras(code)
);

CREATE TABLE `grupos` (
  `code` int NOT NULL,
  `pai` int DEFAULT '0',
  `nome` varchar(50) DEFAULT 'Grupo Sem Nome',
  `nivel` int DEFAULT '1',
  PRIMARY KEY (`code`)
);

create table orc_param(
  est_orc_padrao int not null
);

create table dados (code int primary key,
nome varchar(50) not null default 'TipoIndefinido');

create table relat_tabelas_id( code int primary key auto_increment,
nome varchar(50) not null,
sobre varchar(300),
inner_query varchar(1000),
qnt_colunas int);

create table relat_tab_campos( code int primary key auto_increment,
tabela int default 1,
nome varchar(50),
sobre varchar(300),
query varchar(100),
tipo_dado int default 1,
foreign key(tabela) references relat_tabelas_id(code),
foreign key(tipo_dado) references dados(code));

create table criador_relat( code int,
nome varchar(30) default "Relatorio_SemNome",
tabela int default 1,
campos int default 1,
foreign key(tabela) references relat_tabelas_id(code),
foreign key(campos) references relat_tab_campos(code));


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

create table servico_transporte(
  code int primary key auto_increment,
  transportador int not null default 1,
  cliente int not null default 1,
  cep_inicio varchar(20) not null default '',
  cep_entrega varchar(20) not null default '',
  num_entrega int not null default 0,
  orcamento int not null default 1,
  vlr_frete float not null default '0.0',
  valor_desconto_frete float not null default '0.0',
  frete_pago tinyint not null default 0,
  observacoes_entrega varchar(500) not null default '');

create table frete_vlrs(
  code int primary key auto_increment,
  transportador int not null default 1,
  cliente int not null default 1,
  cep_inicio varchar(20) not null default '',
  cep_entrega varchar(20) not null default '',
  taxa_km float not null default '0.0',
  regiao int not null default 1,
  vlr_frete float not null default '0.0');

create table emails_model(
  code int primary key not null,
  nome varchar(50) not null,
  assunto varchar(50),
  tipo int not null,
  setor int not null
);

create table emails_header(
  code int primary key not null auto_increment,
  conteudo BLOB,
  email_id int not null,
  foreign key(email_id) references emails_model(code)
);

create table emails_body(
  code int primary key not null auto_increment,
  conteudo BLOB,
  email_id int not null,
  foreign key(email_id) references emails_model(code)
);

create table emails_footer(
  code int primary key not null auto_increment,
  conteudo BLOB,
  email_id int not null,
  foreign key(email_id) references emails_model(code)
);

create table distribuicoes(
  code int primary key not null auto_increment,
  nome varchar(200)
);

create table PessoasDistribuicao(
  code int primary key not null auto_increment,
  distribuicao int not null,
  pessoa int not null,
  foreign key(distribuicao) references distribuicoes(code),
  foreign key(pessoa) references terceiros(code)
);
