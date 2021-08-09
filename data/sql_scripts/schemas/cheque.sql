create table if not exists cheque(
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
