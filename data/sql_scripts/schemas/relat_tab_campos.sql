create table if not exists relat_tab_campos( code int primary key auto_increment,
tabela int default 1,
nome varchar(50),
sobre varchar(300),
query varchar(100),
tipo_dado int default 1,
foreign key(tabela) references relat_tabelas_id(code),
foreign key(tipo_dado) references dados(code));
