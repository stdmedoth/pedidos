create user 'petitto'@'%%' identified by '1234';
grant all privileges on *.* to 'petitto'@'%%';
flush privileges;

insert into criticas(nome, opcao_nome, campo_nome, critica)
values('Documento','terceiros','ter_doc',1),
('Tipo Documento (CNPJ/CPF)','terceiros','ter_tipo_doc',1),
('Endereço','terceiros','ter_endereco',1),
('CEP','terceiros','ter_cep',1),
('Tipo Terceiro','terceiros','ter_tipo',1),
('Celular','terceiros','ter_celular',0),
('Contato Celular','terceiros','ter_contatoc',0),
('Telefone','terceiros','ter_telefone',0),
('Contato Telefone','terceiros','ter_contatot',0),
('Email','terceiros','ter_email',0),
('Contato Email','terceiros','ter_contatoe',0),
('Dados de Entrega','terceiros','ter_entrega',0),
('Prazo','terceiros','ter_prazo',0),
('Valor mínimo para frete pago','terceiros','ter_vlr_frete_pago',0),

('Bloqueia Produtos sem movimentos de estoque','orcamentos','orc_prod_movimento',0),
('Produto deve ter saldo para criar orcamento','orcamentos','orc_prod_saldo',0),
('Avisar saldo próximo ao limite','orcamentos','orc_prod_saldo_limite',0),
('Pedidos cancelados são reaproveitados','orcamentos','orc_ped_cancelado',0);

insert into operadores (nome,senha,nivel)
values ('Petitto',MD5(''),3),
('Calistu',MD5('password'),5);

insert into niveis_gerenciais (nome,nivel)
values
('Operacional',1),
('Gerencial',2),
('Estratégico',3),
('Técnico Software',4);

insert into perfil_desktop(desktop_img,tema,janela_init,janelas_keep_above) values
(3,1,1,1),
(3,1,1,1);

insert into confs(navegador_path1,navegador_path2,navegador_pdr,imp_path1,imp_path2,imp_path3)
values ('','',1,'','',''),
('','',1,'','','');


insert into tipo_pagamento(nome) values
('Faturado'),
('Á Vista');

insert into bancos

insert into tipo_movimentos(code,id,nome) values
(1,0,'Venda'),
(2,1,'Devolução Venda'),
(3,2,'Compra'),
(4,3,'Devolução Compra');

insert into estados(sigla,nome)
  values ('AC','Acre'),
  ('AL','Alagoas'),
  ('AM','Amapá'),
  ('AP','Amazonas'),
  ('BA','Bahia'),
  ('CE','Ceará'),
  ('DF','Distrito Federal'),
  ('ES','Espirito Santo'),
  ('GO','Goiás'),
  ('MA','Maranhão'),
  ('MG','Minas Gerais'),
  ('MS','Mato Grosso do Sul'),
  ('MT','Mato Grosso'),
  ('PA','Pará'),
  ('PB','Paraíba'),
  ('PE','Pernambuco'),
  ('PI','Piaí'),
  ('PR','Paraná'),
  ('RJ','Rio de Janeiro'),
  ('RN','Rio Grande do Norte'),
  ('RO','Rondonia'),
  ('RR','Roraima'),
  ('RS','Rio Grande do Sul'),
  ('SC','Santa Catarina'),
  ('SE','Sergipe'),
  ('TO','Tocantins'),
  ('SP','São Paulo');
