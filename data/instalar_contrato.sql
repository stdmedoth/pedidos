create table if not exists contratos(
code int primary key auto_increment,
cadastro int default 0,
compras int default 0,
faturamento int default 0,
estoque int default 0,
financeiro int default 0,
relatorios int default 0,
data_vencimento datetime default '2049-12-31');

insert into contratos values(1,1,0,1,1,0,1,'2049-12-31');
