-- versao base sem migrate

create table if not exists versao( code int primary key auto_increment, versao varchar(30) not null, lancamento datetime not null );

create table if not exists migrate( code int primary key auto_increment, descricao varchar(300) not null, arquivo varchar(150) not null, versao varchar(30) not null,lancamento datetime not null); 

insert ignore into versao values(1, '1.1', '2021-05-28');
insert ignore into migrate values(1, 'Versao 1.1', 'migrate_01.sql', '1.1', '2021-05-28');
