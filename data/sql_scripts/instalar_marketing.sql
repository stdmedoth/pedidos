create table emails_model(
  code int primary key not null,
  nome varchar(50) not null,
  assunto varchar(20),
  tipo int not null,
  setor int not null
);

create table emails_header(
  code int primary key not null auto_increment,
  conteudo BLOB,
  email_id int not null,
  foreign key(email_id) references emails_model(code)
);

create table emails_body(
  code int primary key not null auto_increment,
  conteudo BLOB,
  email_id int not null,
  foreign key(email_id) references emails_model(code)
);

create table emails_footer(
  code int primary key not null auto_increment,
  conteudo BLOB,
  email_id int not null,
  foreign key(email_id) references emails_model(code)
);

create table distribuicoes(
  code int primary key not null auto_increment,
  nome varchar(200)
);

create table PessoasDistribuicao(
  code int primary key not null auto_increment,
  distribuicao int not null,
  pessoa int not null,
  foreign key(distribuicao) references distribuicoes(code),
  foreign key(pessoa) references terceiros(code)
);
