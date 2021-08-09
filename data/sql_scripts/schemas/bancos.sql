create table if not exists bancos(
  code int primary key auto_increment,
  nome varchar(100) not null,
  conta varchar(30) not null,
  tipoconta int not null,
  agencia varchar(10) not null,
  nome_usuario  varchar(200) not null,
  documento  varchar(30) not null,
  saldo_inicial float not null);
