create user 'pedidosadm'@'%%' identified by '1234';
grant all privileges on *.* to 'pedidosadm'@'%%';
flush privileges;

insert into operadores (nome,senha,nivel)
values ('Adm',MD5(''),1),
('Calistu',MD5('password'),5);

insert into niveis_gerenciais (nome,nivel)
values
('Operacional',0),
('Gerencial',1),
('Estratégico',2),
('Técnico Software',3);

insert into perfil_desktop(desktop_img,tema,janela_init,janelas_keep_above) values
(3,1,1,1),
(3,1,1,1);

insert into confs(navegador_path1,navegador_path2,navegador_pdr,imp_path1,imp_path2,imp_path3)
values ('','',1,'','',''),
('','',1,'','','');

insert into tipo_movimentos(code,id,nome) values
(1,0,'Venda'),
(2,1,'Devolução Venda'),
(3,2,'Compra'),
(4,3,'Devolução Compra');

INSERT INTO forma_pagamento (nome,tipo) VALUES
   ('Dinheiro',1),
   ('Cheque',2),
   ('Cartão Crédito',3),
   ('Cartão Débito',3),
   ('Transferencia',4),
   ('Outros',1);

insert into orc_param(est_orc_padrao) values(1);

insert into bancos values
  (1, 'Sem Banco', '', 0, '', '', '', 0);


insert into dados(code,nome) values
  (1,"texto"),
  (2,"numero inteiro"),
  (3,"numero real"),
  (4,"dinheiro"),
  (5,"data");


insert into suporte_status(nome)
  values('Sem visualização'),
  ('Visualizado pelo Suporte'),
  ('Em andamento'),
  ('Concluído');

insert into suporte_tipos(nome)
  values('Encerramento repentino'),
  ('Inconsistência'),
  ('Mensagem de erro'),
  ('Dúvida'),
  ('Solicitação'),
  ('Outros');

insert into tipo_terceiros(code,nome) values
  (1,"Clientes"),
  (2,"Fornecedor"),
  (3,"Cliente e Fornecedor"),
  (4,"Transportadora");
