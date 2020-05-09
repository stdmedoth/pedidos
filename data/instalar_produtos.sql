insert into unidades (nome, sigla, multiplo)
values ('Folhas','Folhas',1),  
('Fardo','Fardo',1),
('Pacote','Pct',1),
('Unidade','UND',1),
('Caixa','CX',1);

insert into grupos(nome,pai) values 
('RAIZ',1), 
('PERCALUX',1), 
('CABECEADO',1), 
('COLA',1), 
('FITILHO ACETINADO',1), 
('LINHA',1), 
('PELICULA',1), 
('RESISTÊNCIA',1),
('ESPIRAIS', 1),
('PLASTIFICAÇÕES', 1),
('WERE-O', 1),
('CAPAS DE PP', 1),

('LISO', 2), 
('BICOLOR', 2), 
('METALIZADO', 2), 
('OURO/BRONZE', 2);

insert into terceiros(razao) 
values('CLIENTE PARA TESTE'),
('FORNECEDOR PARA TESTE');

insert into produtos(nome, preco_faturado, preco_vista, peso , unidade, grupo, observacoes) 
values('PERCALUX PAPEL PLASTIFICADO LISO - 1,30 LARG./25M - DIV. CORES', 225.00, 371.50, 0.0, 4, 1, ''),
('PERCALUX PAPEL PLASTIFICADO LISO - 1,30 LARG./25M - DIV. CORES', 225.00, 371.50, 0.0, 4, 1, ''),
('PERCALUX PAPEL PLASTIFICADO LISO - 1,30 LARG./50M - DIV. CORES', 371.50, 351.50, 0.0, 4, 1, ''),
('PERCALUX PAPEL PLASTIFICADO BICOLOR - 1,30 LARG./25M - CORES', 289.00, 289.00, 0.0, 4, 1, ''),
('PERCALUX PAPEL PLASTIFICADO METALIZADO - 1,30 LARG./25M - CORES', 251.00, 241.00, 0.0, 4, 1, ''),
('PERCALUX PAPEL PLASTIFICADO OURO/BRONZE - 1,30 LARG./25M', 225.00, 371.50, 0.0, 4, 1, ''),
('CABECEADO - FITA ALGODAO - ROLO 50M - DIVERSAS CORES', 225.00, 371.50, 0.0, 4, 1, '');
