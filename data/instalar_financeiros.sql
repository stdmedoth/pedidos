create table titulos(
  code int primary key,
  cliente int not null,
  pedido int not null,
  status int not null,
  qnt_parcelas int not null,
  tipo_titulo int not null);

create table parcelas_tab(
  parcelas_id int not null,
  posicao int not null,
  banco int default 0,
  data_criacao datetime,
  data_vencimento datetime,
  valor float default 0 not null,
  foreign key(parcelas_id) references titulos(code));

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

create table bancos(
  code int primary key auto_increment,
  nome varchar(100) not null,
  conta varchar(30) not null,
  tipoconta int not null,
  agencia varchar(10) not null,
  nome_usuario  varchar(200) not null,
  documento  varchar(30) not null,
  saldo_inicial float not null);
