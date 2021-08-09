create table if not exists cheque_finan(
  code int primary key auto_increment,
  cheque int not null,
  titulo int not null,
  foreign key(cheque) references cheque(code),
  foreign key(titulo) references titulos(code));
