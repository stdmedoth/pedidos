create table if not exists forma_pagamento(
  code int primary key auto_increment,
  nome varchar(50),
  tipo int default 1);
