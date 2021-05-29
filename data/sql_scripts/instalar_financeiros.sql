create table titulos(
  code int primary key,
  cliente int not null,
  pedido int not null,
  status int not null,
  qnt_parcelas int not null,
  tipo_titulo int not null,
  foreign key (cliente) references terceiros(code));

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
  conta varchar(50) not null
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


create table bancos(
  code int primary key auto_increment,
  nome varchar(100) not null,
  conta varchar(30) not null,
  tipoconta int not null,
  agencia varchar(10) not null,
  nome_usuario  varchar(200) not null,
  documento  varchar(30) not null,
  saldo_inicial float not null);

create table orcs_cheques(
  code int primary key auto_increment,
  orcamento int not null,
  cheque int not null
  foreign key(orcamento) references orcamentos(code),
  foreign key(cheque) references cheque(code));
