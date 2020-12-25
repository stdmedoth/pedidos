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
