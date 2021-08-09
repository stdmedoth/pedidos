create table if not exists tipo_movimentos( code int primary key,
    id int not null default 0,
    nome varchar(40) default 'TipoMovimentoSemNome'
  );
