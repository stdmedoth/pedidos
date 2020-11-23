create table emails_model(
  code int primary key not null,
  nome varchar(50) not null,
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
