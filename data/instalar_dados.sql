create user 'petitto'@'localhost' identified by '1234';
grant all privileges on *.* to 'petitto'@'localhost';
flush privileges;

insert into criticas(opcao_nome,campo_nome,critica) 
values('terceiros','ter_doc',1),
('terceiros','ter_tipo_doc',1),
('terceiros','ter_endereco',1),
('terceiros','ter_cep',1),
('terceiros','ter_tipo',1),
('terceiros','ter_celular',1),
('terceiros','ter_contatoc',1),
('terceiros','ter_telefone',1),
('terceiros','ter_contatot',1),
('terceiros','ter_email',1),
('terceiros','ter_contatoe',1);

insert into operadores 
values(1,'Petitto','',5);

insert into empresa(razao,endereco,cnpj) 
values ( 'Petitto Mat. p/ encadern. e carton.','R. Dna Amelia de Paula,100\nJardim Leonor,Campinas ','---');

insert into perfil_desktop(code,
desktop_img,
tema,
janela_init,
janelas_keep_above) values(1,3,3,0,1);

insert into unidades (nome, sigla, multiplo, medida)
values ('Folhas','Folhas', 1, 5),  
('Fardo','Fardo', 15, 5),
('Pacote','Pct', 20, 4),
('Unidade','UND', 1, 4),
('Caixa','CX', 10, 4);

insert into grupos(nome,pai,nivel) values 
('RAIZ',1, 0), 
('PERCALUX',1, 1), 
('CABECEADO',1, 1), 
('COLA',1, 1), 
('FITILHO ACETINADO',1, 1), 
('LINHA',1, 1), 
('PELICULA',1, 1), 
('RESISTÊNCIA',1, 1),
('ESPIRAIS', 1, 1),
('PLASTIFICAÇÕES', 1, 1),
('WERE-O', 1, 1),
('CAPAS DE PP', 1, 1),
 
('LISO', 2, 2), 
('BICOLOR', 2, 2), 
('METALIZADO', 2, 2), 
('OURO/BRONZE', 2, 2),

('ROLO 50M',3,2),
('ROLO 100M',3,2),

('1,30 LARG./25M',13,3),
('1,30 LARG./50M',13,3),
('1,30 LARG./25M',14,3),
('1,30 LARG./25M',15,3),
('1,30 LARG./25M',16,3);



insert into terceiros (razao,doc,tipo_doc,ie,tipoc,tipo,cep,endereco,cidade,uf,numrua,tiporua, 
telefone,contatot ,celular , contatoc ,email,contatoe, transp_nome, transp_num,transp_logradouro ,
transp_cidade , transp_estado ,  transp_cep,  transp_telefone, transp_cnpj, transp_ie, transp_obs, obs,
frete_pago, vlr_frete_pago, prazo) 
values ('CLIENTE PARA TESTE', '512.146.788-58',  2, '123456789' , 'Cliente',  1,  '13067450', 'Rua Doutor Marcos Antonio Samartine', 
'Campinas', 'SP', 18, 1, '(19) 32818753', 'cliente', '(19) 987817853','calisto', 'email@email.com', 'contato', 'TRANSPORTADORA', 
18 ,'Praça da Sé, 108','São Paulo' ,'SP' , '01001900' ,'(null)' , '1234567890', '1234567890',  '(null)', '', 1, 200.00 ,'20'), 

('FORNECEDOR PARA TESTE', '123.146.744-58',  2, '123456789' , 'Fornecedor',  2,  '13067450', 'Rua Doutor Marcos Antonio Samartine', 
'Campinas', 'SP', 18, 1, '(19) 32818753', 'fornecedor', '(19) 987817853','calisto', 'email@email.com', 'contato', 'TRANSPORTADORA', 
18 ,'Praça da Sé, 108','São Paulo' ,'SP' , '01001900' ,'(null)' , '1234567890', '1234567890',  '(null)', '', 1, 200.00 ,'20');

insert into produtos(nome, peso , unidades, unidades_atacado, grupo, grupo_nivel, observacoes) 
values ('PERCALUX PAPEL PLASTIFICADO', 0.0, 4, 5, 2, 3, ''),
('CABECEADO FITA ALGODÃO', 0.0, 4, 5, 3, 3, '');
