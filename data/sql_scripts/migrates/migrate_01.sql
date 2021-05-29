-- versao base sem migrate

create table versao(
  versao varchar(30) not null,
  lancamento datetime not null 
);

create table migrate(
  code int primary key auto_increment,
  descricao varchar(300) not null,
  arquivo varchar(150) not null,
  versao varchar(30) not null,
  lancamento datetime not null 
);


update versao set versao = '1.1', lancamento = '2021-05-28';
insert into migrate values(1, 'Versao 1.1', 'migrate_01.sql', '1.1', '2021-05-28');