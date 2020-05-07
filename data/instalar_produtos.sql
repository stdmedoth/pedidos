insert into unidades (nome, sigla, multiplo)
values ('Folhas','Folhas',1),  
('Fardo','Fardo',1),
('Pacote','Pct',1),
('Unidade','UND',1),
('Caixa','CX',1);

insert into grupos(nome) 
values('PERCALUX'), 
('CABECEADO'), 
('COLA'), 
('FITILHO ACETINADO'), 
('LINHA'), 
('PELÍCULA'), 
('RESISTÊNCIA'),
('ESPIRAIS'),
('PLASTIFICAÇÕES'),
('WERE-O'),
('CAPAS DE PP');

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
('CABECEADO - FITA ALGODÃO - ROLO 50M - DIVERSAS CORES', 225.00, 371.50, 0.0, 4, 1, '');
