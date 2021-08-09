create table if not exists emails_body(
  code int primary key not null auto_increment,
  conteudo BLOB,
  email_id int not null,
  foreign key(email_id) references emails_model(code)
);
