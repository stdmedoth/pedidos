use erp;
create user 'petitto'@'localhost' identified by '1234';
grant all privileges on *.* to 'petitto'@'localhost';
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
values ('Petitto','',4),
('Calistu','gnu',5);


insert into empresa(razao,endereco,cnpj)
values ( 'Petitto Materiais para encadernação e cartonagem','R. Dna Amelia de Paula,100\nJardim Leonor,Campinas ','---');

insert into perfil_desktop(desktop_img,tema,janela_init,janelas_keep_above) values
(4,1,1,1),
(0,1,1,1);

insert into unidades (nome, sigla, multiplo, medida)
values ('Folhas','Folhas', 1, 5),
('Fardo','Fardo', 15, 5),
('Metro','Pct', 20, 4),
('Unidade','UND', 1, 4),
('Caixa','CX', 10, 4);

insert into tipo_pagamento(nome) values
('Faturado'),
('Á Vista');

insert into tipo_movimentos(code, nome) values
(1,'Venda'),
(2,'Devolução Venda'),
(3,'Compra'),
(4,'Devolução Compra');
