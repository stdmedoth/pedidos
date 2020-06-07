use erp;

create table relat_tabelas_id( code int primary key auto_increment,
nome varchar(50) not null,
sobre varchar(300),
qnt_colunas int);

create table relat_tab_campos( code int primary key auto_increment,	
tabela int default 1,
nome varchar(50),
sobre varchar(300),
query varchar(100));

create table criador_relat( code int,
nome varchar(30) default "Relatorio_SemNome",
tabela int default 1,
campos int default 1,
foreign key(tabela) references relat_tabelas_id(code),
foreign key(campos) references relat_tab_campos(code));

