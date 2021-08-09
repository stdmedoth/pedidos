create table if not exists cotacoes_participantes(
  code int primary key auto_increment not null,
  cotacoes_id int not null,
  participante int not null,
  foreign key(cotacoes_id) references cotacoes(code),
  foreign key(participante) references terceiros(code)
);
