create table if not exists credenciadoras(
    code int primary key not null,
    cod_cred varchar(4),
    nome varchar(300),
    cnpj varchar(20)
);
