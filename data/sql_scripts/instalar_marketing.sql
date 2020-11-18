create table emails_model(
  code int primary key not null,
  nome varchar(50) not null,
  tipo int not null,
  setor int not null
);

create table emails_title(
  code int primary key not null,
  tipo_widget int not null,
  conteudo varchar(1000),
  email_id int not null,
  foreign key references emails_model(code);
);

create table emails_body(
  code int primary key not null,
  tipo_widget int not null,
  conteudo varchar(2000),
  email_id int not null,
  foreign key references emails_model(code);
);

create table emails_footer(
  code int primary key not null,
  tipo_widget int not null,
  conteudo varchar(1000),
  email_id int not null,
  foreign key references emails_model(code);
);
