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
janelas_keep_above) values(1,3,1,0,1);

insert into unidades (nome, sigla, multiplo, medida)
values ('Folhas','Folhas', 1, 5),  
('Fardo','Fardo', 15, 5),
('Pacote','Pct', 20, 4),
('Unidade','UND', 1, 4),
('Caixa','CX', 10, 4);

insert into grupos(code,nome,pai,nivel) values 
(1,'RAIZ',1, 0), 
(2,'PERCALUX',1, 1), 
(3,'CABECEADO',1, 1), 
(4,'COLA',1, 1), 
(5,'FITILHO ACETINADO',1, 1), 
(6,'LINHA',1, 1), 
(7,'PELICULA',1, 1), 
(8,'RESISTÊNCIA',1, 1),
(9,'ESPIRAIS', 1, 1),
(10,'PLASTIFICAÇÕES', 1, 1),
(11,'WERE-O', 1, 1),
(12,'CAPAS DE PP', 1, 1),
(13,'PAPELÃO', 1, 1),
 
(14,'LISO', 2, 2), 
(15,'BICOLOR', 2, 2), 
(16,'METALIZADO', 2, 2), 
(17,'OURO/BRONZE', 2, 2),
(18,'FOSCO',2, 2),

(19,'ROLO 50M',3,2),
(20,'ROLO 100M',3,2),

(21,'Nº12', 13, 2),
(22,'Nº15', 13, 2),
(23,'Nº18', 13, 2),
(24,'Nº20', 13, 2),
(25,'Nº 20 (FACE BRANCA)', 13, 2),

(26,'1,30 LARG./25M',14,3),
(27,'1,30 LARG./50M',14,3),
(28,'1,30 LARG./25M',15,3),
(29,'1,30 LARG./25M',16,3),
(30,'1,30 LARG./25M',17,3),

(31,'AZUL', 18, 3),
(32,'VERMELHO', 18, 3),
(33,'AMARELO', 18, 3),
(34,'VERDE', 18, 3),
(35,'PRETO', 18, 3),

(36,'15 FOLHAS 1,7MM', 21,3),
(37,'18 FOLHAS 1,7MM', 22,3),
(38,'21 FOLHAS 1,7MM', 23,3),
(39,'24 FOLHAS 1,7MM', 24,3),
(40,'24 FOLHAS 1,7MM', 25,3);

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
values ('PERCALUX', 0.0, 4, 5, 2, 3, ''),
('CABECEADO', 0.0, 4, 5, 3, 3, ''),
('PAPELÃO', 0.0, 4, 5, 3, 3, '');
