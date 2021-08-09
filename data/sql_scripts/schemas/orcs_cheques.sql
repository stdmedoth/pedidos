create table if not exists orcs_cheques(
  code int primary key auto_increment,
  orcamento int not null,
  cheque int not null,
  foreign key(orcamento) references orcamentos(code),
  foreign key(cheque) references cheque(code));
