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


insert into estados(sigla,nome)
  values ('AC','Acre'),
  ('AL','Alagoas'),
  ('AM','Amapá'),
  ('AP','Amazonas'),
  ('BA','Bahia');

insert into estados(sigla,nome)
  values ('CE','Ceará'),
  ('DF','Distrito Federal'),
  ('ES','Espirito Santo'),
  ('GO','Goiás'),
  ('MA','Maranhão'),
  ('MG','Minas Gerais'),
  ('MS','Mato Grosso do Sul'),
  ('MT','Mato Grosso');

insert into estados(sigla,nome)
  values ('PA','Pará'),
  ('PB','Paraíba'),
  ('PE','Pernambuco'),
  ('PI','Piaí'),
  ('PR','Paraná'),
  ('RJ','Rio de Janeiro'),
  ('RN','Rio Grande do Norte');

  insert into estados(sigla,nome)
    values
  ('RO','Rondonia'),
  ('RR','Roraima'),
  ('RS','Rio Grande do Sul'),
  ('SC','Santa Catarina');

  insert into estados(sigla,nome)
    values
  ('SE','Sergipe'),
  ('TO','Tocantins'),
  ('SP','São Paulo');


  INSERT INTO unidades (nome,sigla,multiplo,medida) VALUES
  	 ('AMPOLA','AMPOLA',1,0),
  	 ('BALDE','BALDE',1,0),
  	 ('BANDEJA','BANDEJ',1,0),
  	 ('BARRA','BARRA',1,0),
  	 ('BISNAGA','BISNAG',1,0),
  	 ('BLOCO','BLOCO',1,0),
  	 ('BOBINA','BOBINA',1,0),
  	 ('BOMBONA','BOMB',1,0),
  	 ('CAPSULA','CAPS',1,0),
  	 ('CARTELA','CART',1,0);

  INSERT INTO unidades (nome,sigla,multiplo,medida) VALUES
  	 ('CENTO','CENTO',1,0),
  	 ('CONJUNTO','CJ',1,0),
  	 ('CENTIMETRO','CM',1,0),
  	 ('CENTIMETRO QUADRADO','CM2',1,0),
  	 ('CAIXA','CX',1,0),
  	 ('CAIXA COM 2 UNIDADES','CX2',1,0),
  	 ('CAIXA COM 3 UNIDADES','CX3',1,0),
  	 ('CAIXA COM 5 UNIDADES','CX5',1,0),
  	 ('CAIXA COM 10 UNIDADES','CX10',1,0),
  	 ('CAIXA COM 15 UNIDADES','CX15',1,0);
  INSERT INTO unidades (nome,sigla,multiplo,medida) VALUES
  	 ('CAIXA COM 20 UNIDADES','CX20',1,0),
  	 ('CAIXA COM 25 UNIDADES','CX25',1,0),
  	 ('CAIXA COM 50 UNIDADES','CX50',1,0),
  	 ('CAIXA COM 100 UNIDADES','CX100',1,0),
  	 ('DISPLAY','DISP',1,0),
  	 ('DUZIA','DUZIA',1,0),
  	 ('EMBALAGEM','EMBAL',1,0),
  	 ('FARDO','FARDO',1,0),
  	 ('FOLHA','FOLHA',1,0),
  	 ('FRASCO','FRASCO',1,0);
  INSERT INTO unidades (nome,sigla,multiplo,medida) VALUES
  	 ('GALÃO','GALAO',1,0),
  	 ('GARRAFA','GF',1,0),
  	 ('GRAMAS','GRAMAS',1,0),
  	 ('JOGO','JOGO',1,0),
  	 ('QUILOGRAMA','KG',1,0),
  	 ('KIT','KIT',1,0),
  	 ('LATA','LATA',1,0),
  	 ('LITRO','LITRO',1,0),
  	 ('METRO','M',1,0),
  	 ('METRO QUADRADO','M2',1,0);
  INSERT INTO unidades (nome,sigla,multiplo,medida) VALUES
  	 ('METRO CÚBICO','M3',1,0),
  	 ('MILHEIRO','MILHEI',1,0),
  	 ('MILILITRO','ML',1,0),
  	 ('MEGAWATT HORA','MWH',1,0),
  	 ('PACOTE','PACOTE',1,0),
  	 ('PALETE','PALETE',1,0),
  	 ('PARES','PARES',1,0),
  	 ('PEÇA','PC',1,0),
  	 ('POTE','POTE',1,0),
  	 ('QUILATE','K',1,0);
  INSERT INTO unidades (nome,sigla,multiplo,medida) VALUES
  	 ('RESMA','RESMA',1,0),
  	 ('ROLO','ROLO',1,0),
  	 ('SACO','SACO',1,0),
  	 ('SACOLA','SACOLA',1,0),
  	 ('TAMBOR','TAMBOR',1,0),
  	 ('TANQUE','TANQUE',1,0),
  	 ('TONELADA','TON',1,0),
  	 ('TUBO','TUBO',1,0),
  	 ('UNIDADE','UNID',1,0),
  	 ('VASILHAME','VASIL',1,0);
  INSERT INTO unidades (nome,sigla,multiplo,medida) VALUES
  	 ('VIDRO','VIDRO',1,0);


insert into criticas(nome, opcao_nome, campo_nome, critica)
values
('Documento','terceiros','ter_doc',1),
('Tipo Documento (CNPJ/CPF)','terceiros','ter_tipo_doc',1),
('Endereço','terceiros','ter_endereco',1),
('CEP','terceiros','ter_cep',1),
('Tipo Terceiro','terceiros','ter_tipo',1);

insert into criticas(nome, opcao_nome, campo_nome, critica)
values
('Celular','terceiros','ter_celular',0),
('Contato Celular','terceiros','ter_contatoc',0),
('Telefone','terceiros','ter_telefone',0),
('Contato Telefone','terceiros','ter_contatot',0),
('Email','terceiros','ter_email',0);

insert into criticas(nome, opcao_nome, campo_nome, critica)
values
('Contato Email','terceiros','ter_contatoe',0),
('Dados de Entrega','terceiros','ter_entrega',0),
('Prazo','terceiros','ter_prazo',0),
('Valor mínimo para frete pago','terceiros','ter_vlr_frete_pago',0),

insert into criticas(nome, opcao_nome, campo_nome, critica)
values
('Bloqueia Produtos sem movimentos de estoque','orcamentos','orc_prod_movimento',0),
('Produto deve ter saldo para criar orcamento','orcamentos','orc_prod_saldo',0),
('Avisar saldo próximo ao limite','orcamentos','orc_prod_saldo_limite',0),
('Pedidos cancelados são reaproveitados','orcamentos','orc_ped_cancelado',0);


insert into relat_tabelas_id(nome, sobre, inner_query, qnt_colunas) values
('produtos','Tabela responsável por armazenar os dados dos produtos',
'  from produtos as p inner join unidades as u inner join terceiros as t on p.fornecedor = t.code and p.unidades = u.code',8);


insert into relat_tabelas_id(nome, sobre, inner_query, qnt_colunas) values
('terceiros','Tabela responsável por armazenar os dados dos clientes e fornecedores',
' from terceiros as t inner join terceiros as trp left join tipo_terceiros as tp on t.transp_code = trp.code and t.tipo = tp.code left join contatos as tc on tc.terceiro = t.code' ,25);


insert into relat_tabelas_id(nome, sobre, inner_query, qnt_colunas) values
('orçamentos','Tabela responsável por armazenar os orcamentos criados e seus status',
' from orcamentos as o inner join terceiros as t inner join tipo_pagamento as tp on o.cliente = t.code and o.tipopag = tp.code',6);

insert into relat_tabelas_id(nome, sobre, inner_query, qnt_colunas) values
('pedidos','Tabela responsável por armazenar os pedidos criados e seus status',
' from pedidos as p',5);

insert into relat_tabelas_id(nome, sobre, inner_query, qnt_colunas) values
('Movimentos estoque','Tabela responsável por mostrar movimentações de produtos no estoque',
' from movimento_estoque as m_e inner join estoques as e inner join terceiros as t inner join produtos as p inner join tipo_movimentos as t_m on m_e.estoque = e.code and m_e.cliente = t.code and m_e.produto = p.code and m_e.tipo_mov = t_m.id',10);

insert into relat_tabelas_id(nome, sobre, inner_query, qnt_colunas) values
('Faturamento','Tabela responsável pela visualização de valor das vendas',
' from faturamento as f inner join pedidos as p inner join terceiros as t inner join tipo_movimentos as t_m on p.code = f.pedido and f.cliente = t.code and f.tipo_mov = t_m.code',7);

insert into relat_tabelas_id(nome, sobre, inner_query, qnt_colunas) values
('Produtos por Orçamentos/Pedidos','Tabela responsável por armazenar os produtos contidos em orçamentos',
' from produtos as p inner join unidades as u inner join terceiros as t inner join tipo_terceiros as tp inner join produto_orcamento as p_o inner join orcamentos as o on p.fornecedor = t.code and p.unidades = u.code and t.tipo = tp.code and p_o.produto = p.code and p_o.code = o.code',15);


insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(1, 'Código' , 'Visualizar código do produto', 'p.code',2),
(1, 'Nome',  'Visualizar nome do produto', 'p.nome ',1),
(1, 'Peso',  'Visualizar peso do produto', 'p.peso',3),
(1, 'UND. Varejo', 'Unidades para venda varejo', 'u.nome',1);

insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(1, 'UND. Atacado', 'Unidades para venda Atacado', 'u.nome',1),
(1, 'Fornecedor', 'Terceiro fornecedor do produto', 't.razao',1),
(1, 'Nivel Grupo', 'Nivel do grupo vinculado (Não utilizado)', 'p.grupo_nivel',2),
(1, 'Observações', 'Observações do produto', 'observacoes',1);


insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(2, 'Código' , 'Visualizar código do terceiro', 't.code',2),
(2, 'Código NF-e',  'Visualizar código do terceiro para tirar nfe', 't.code_nfe',1),
(2, 'Razão Social/Nome',  'Visualizar Nome ou Razão da empresa/pessoa', 't.razao',1),
(2, 'Documento', 'CNPJ ou RG do Terceiro', 't.doc',1),
(2, 'IE/RG', 'Inscrição/RG do Terceiro', 't.ie',1),
(2, 'CEP', 'CEP do Terceiro', 't.cep',1),
(2, 'Tipo', 'Tipo de Terceiro (Cliente/Fornecedor/Transportadora)', 'tp.nome',1),
(2, 'Logradouro', 'Logradouro do Terceiro', 't.endereco',1),
(2, 'Cidade', 'Cidade do Terceiro', 't.cidade',1),
(2, 'Número ', 'Numero endereço do Terceiro', 't.numrua',1);

insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(2, 'Tipo Logr', 'Tipo de logradouro: Rua,Avenida,Rodovia', 't.tiporua',1),
(2, 'Contato', 'Contato para o telefone', 'tc.nome',1),
(2, 'Telefone', 'Número de telefone do terceiro', 'tc.telefone',1),
(2, 'Celular', 'Número de celular do terceiro', 'tc.celular',1),
(2, 'Email', 'Email do terceiro', 'tc.email',1),
(2, 'Transp. Nome', 'Nome da transp. vinc. ao Terceiro', 'trp.transp_nome',1),
(2, 'Transp. Documento', 'CNPJ da transp. vinc. ao Terceiro', 'trp.transp_cnpj',1),
(2, 'Transp. IE', 'Inscrição Estadual da transp. vinc. ao Terceiro', 'trp.ie',1);

insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(2, 'Transp .Logradouro', 'Logradouro da transp. vinc. ao Terceiro', 't.endereco',1),
(2, 'Numero Endereço Transp.', 'Número endereço da transp. vinc. ao Terceiro', 't.transp_num',2),
(2, 'Cidade  Transp.', 'Cidade da transp. vinc. ao Terceiro', 't.transp_cidade',1),
(2, 'UF Transp.', 'Estado da transp. vinc. ao Terceiro', 't.transp_estado',1),
(2, 'CEP Transp.', 'CEP da transp. vinc. ao Terceiro', 't.transp_cep',1),
(2, 'Prazo', 'Prazo padrão de pagamento', 't.prazo',1),
(2, 'Observações de entrega', 'Observações da entrega vinc. ao Terceiro', 't.transp_obs',1);

insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(3, 'Código','Código dos orcamentos gerados', 'o.code',2),
(3, 'Cliente','Cliente vinculado ao orcamento', 't.razao',1),
(3, 'Data de Criação', 'Data dos dos orcamentos gerados', 'o.dia',5),
(3, 'tipopag','Tipo de pagamento (faturado, a vista)', 'tp.nome',1),
(3, 'Total','Valor Totaldo orcamento', 'o.total',3),
(3, 'Observacoes','Observações contidas no orçamento', 'o.obeservacoes',1);

insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(4, 'Código','Código dos pedidos gerados', 'p.code',2),
(4, 'Cliente','Cliente vinculado ao pedido', 't.razao',1),
(4, 'Data de Criação', 'Data dos dos pedidos gerados', 'p.data_mov',5),
(4, 'status','Código dos pedidos gerados', 'tp.nome',1),
(4, 'Total','Valor Total do pedido', 'o.total',3);

insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(5, 'Código','Código dos movimentos de cada produto', 'm_e.code',2),
(5, 'Estoque','Estoque utilizado no movimento', 'm_e.estoque',2),
(5, 'Pedido', 'Número do pedido vinculado ao movimento', 'm_e.pedido',2),
(5, 'Cód Produto', 'Código do Produto movimentado', 'm_e.produto',2),
(5, 'Nome Produto','Nome Produto movimentado', 'p.nome',1);

insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(5, 'Cód. Cliente','Código do cliente vinculado ao movimento', 'm_e.cliente',2),
(5, 'Nome Cliente','Nome do cliente vinculado ao movimento', 't.razao',1),
(5, 'Movimento Saídas','Quantidade de saídas no movimento', 'm_e.saidas',3),
(5, 'Movimento Entradas','Quantidade de entradas no movimento', 'm_e.entradas',3),
(5, 'Tipo','Tipo de movimento (venda,compra,devolução)', 't_m.nome',2),
(5, 'Data','Data do movimento', 'm_e.data_mov',5);

insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(6, 'Cód.','Código dos movimentos de venda', 'f.code',2),
(6, 'Cód. Pedido','Código dos pedido vinculado ao faturamento', 'p.code',2),
(6, 'Valor Entrada','Valor de entradas faturamento', 'f.entrada',4),
(6, 'Valor Saída','Valor de saidas faturamento', 'f.saida',4),
(6, 'Data','Data do movimento no faturamento', 'f.data_mov',5),
(6, 'Tipo Op.','Tipo de movimento(venda,devolução)', 't_m.nome',1);

insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(7, 'Cliente','Cliente vinculado ao orcamento', 't.razao',1),
(7, 'Data de Criação', 'Data dos dos orcamentos gerados', 'o.dia',5),
(7, 'tipopag','Tipo de pagamento (faturado, a vista)', 'tp.nome',1),
(7, 'Total','Valor Totaldo orcamento', 'o.total',3),
(7, 'Observacoes','Observações contidas no orçamento', 'o.obeservacoes',1),
(7, 'Código Pród.' , 'Visualizar código do produto', 'p.code',2),
(7, 'Nome Produto',  'Visualizar nome do produto', 'p.nome ',1),
(7, 'Peso',  'Visualizar peso do produto', 'p.peso',3);

insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(7, 'UND. Varejo', 'Unidades para venda varejo', 'u.nome',1),
(7, 'UND. Atacado', 'Unidades para venda Atacado', 'u.nome',1),
(7, 'Qnt Item','Quantidade vendida do item', 'p_o.unidades',3),
(7, 'Vlr Unit Item','Valor unitário de cada item', 'p_o.valor_unit',3),
(7, 'Vlr Item','Valor Total de cada item', 'p_o.total',3);

insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(7, 'Vlr Desc Item','Valor desconto cada item', 'p_o.desconto',3),
(7, 'Fornecedor', 'Terceiro fornecedor do produto', 't.razao',1),
(7, 'Nivel Grupo', 'Nivel do grupo vinculado (Não utilizado)', 'p.grupo_nivel',2),
(7, 'Observações', 'Observações do produto', 'o.observacoes',1);

insert into credenciadoras
  values
  ( 1, '001', 'Administradora de Cartões Sicredi Ltda.', '03.106.213/0001-90'),
  ( 2, '002', 'Administradora de Cartões Sicredi Ltda.(filial RS)', '03.106.213/0002-71'),
  ( 3, '003', 'Banco American Express S/A - AMEX', '60.419.645/0001-95'),
  ( 4, '004', 'BANCO GE - CAPITAL', '62.421.979/0001-29'),
  ( 5, '005', 'BANCO SAFRA S/A', '58.160.789/0001-28'),
  ( 6, '006', 'BANCO TOPÁZIO S/A', '07.679.404/0001-00'),
  ( 7, '007', 'BANCO TRIANGULO S/A', '17.351.180/0001-59'),
  ( 8, '008', 'BIGCARD Adm. de Convenios e Serv.', '04.627.085/0001-93'),
  ( 9, '009', 'BOURBON Adm. de Cartões de Crédito', '01.418.852/0001-66');

insert into credenciadoras
  values
  ( 10, '010', 'CABAL Brasil Ltda.', '03.766.873/0001-06'),
  ( 11, '011', 'CETELEM Brasil S/A - CFI', '03.722.919/0001-87'),
  ( 12, '012', 'CIELO S/A', '01.027.058/0001-91'),
  ( 13, '013', 'CREDI 21 Participações Ltda.', '03.529.067/0001-06'),
  ( 14, '014', 'ECX CARD Adm. e Processadora de Cartões S/A', '71.225.700/0001-22'),
  ( 15, '015', 'Empresa Bras. Tec. Adm. Conv. Hom. Ltda. - EMBRATEC', '03.506.307/0001-57'),
  ( 16, '016', 'EMPÓRIO CARD LTDA', '04.432.048/0001-20'),
  ( 17, '017', 'FREEDDOM e Tecnologia e Serviços S/A', '07.953.674/0001-50');

insert into credenciadoras
  values
  ( 18, '018', 'FUNCIONAL CARD LTDA.', '03.322.366/0001-75'),
  ( 19, '019', 'HIPERCARD Banco Multiplo S/A', '03.012.230/0001-69'),
  ( 20, '020', 'MAPA Admin. Conv. e Cartões Ltda.', '03.966.317/0001-75'),
  ( 21, '021', 'Novo Pag Adm. e Proc. de Meios Eletrônicos de Pagto. Ltda.', '00.163.051/0001-34'),
  ( 22, '022', 'PERNAMBUCANAS Financiadora S/A Crédito, Fin. e Invest.', '43.180.355/0001-12'),
  ( 23, '023', 'POLICARD Systems e Serviços Ltda.', '00.904.951/0001-95');

insert into credenciadoras
  values
  ( 24, '024', 'PROVAR Negócios de Varejo Ltda.', '33.098.658/0001-37'),
  ( 25, '025', 'REDECARD S/A', '01.425.787/0001-04'),
  ( 26, '026', 'RENNER Adm. Cartões de Crédito Ltda.', '90.055.609/0001-50'),
  ( 27, '027', 'RP Administração de Convênios Ltda.', '03.007.699/0001-00'),
  ( 28, '028', 'SANTINVEST S/A Crédito, Financiamento e Investimentos', '00.122.327/0001-36'),
  ( 29, '029', 'SODEXHO Pass do Brasil Serviços e Comércio S/A', '69.034.668/0001-56');

insert into credenciadoras
  values
  ( 30, '030', 'SOROCRED Meios de Pagamentos Ltda.', '60.114.865/0001-00'),
  ( 31, '031', 'Tecnologia Bancária S/A - TECBAN', '51.427.102/0004-71'),
  ( 32, '032', 'TICKET Serviços S/A', '47.866.934/0001-74'),
  ( 33, '033', 'TRIVALE Administração Ltda.', '00.604.122/0001-97'),
  ( 34, '034', 'Unicard Banco Múltiplo S/A - TRICARD', '61.071.387/0001-61'),
  ( 35, '035', '998 Reservado', ''),
  ( 36, '999', 'Outros', '');


  insert into prod_origem values(1,0,"Nacional, exceto as indicadas nos códigos 3, 4, 5 e 8 ", 7);
  insert into prod_origem values(2,1,"Estrangeira – Importação direta, exceto a indicada no código 6  ", 4);
  insert into prod_origem values(3,2,"Estrangeira – Adquirida no mercado interno, exceto a indicada no código 7 ", 4);
  insert into prod_origem values(4,3,"Nacional, Conteúdo de Import. superio a 40%, inferior ou igual a 70%", 4);
  insert into prod_origem values(5,4,"Nacional, cuja prod. tenha sido feita em conformidade com os processos prod. básicos", 7);
  insert into prod_origem values(6,5,"Nacional, Conteúdo de Import. inferior ou igual a 40% (quarenta por cento)", 7);
  insert into prod_origem values(7,6,"Estrangeira – Importação direta, (Ver lista de Bens Sem Similar Nacional – LESSIN)", 7);
  insert into prod_origem values(8,7,"Estrangeira – Adquirida no mercado interno(Ver lista de Bens Sem Similar Nac. – LESSIN)", 7);
  insert into prod_origem values(9,8,"Nacional, Conteúdo de Importação superior a 70%", 4);

  insert into cst_cson values(1,"101", "Tributada pelo S.N. com perm. de créd.", 1);
  insert into cst_cson values(2,"102", "Tributada pelo S.N. sem perm. de créd.", 1);
  insert into cst_cson values(3,"103", "Isenção do ICMS no S.N. para faixa de receita bruta", 1);
  insert into cst_cson values(4,"201", "Tributada pelo S.N. com perm. de créd. e com cobrança do ICMS por ST", 1);
  insert into cst_cson values(5,"202", "Tributada pelo S.N. sem permissão de crédito e com cobrança do ICMS por ST", 1);
  insert into cst_cson values(6,"203", "Isenção do ICMS no S.N. para faixa de receita bruta e com cobrança do ICMS por ST", 1);
  insert into cst_cson values(7,"300", "Imune", 1);
  insert into cst_cson values(8,"400", "Não tributada pelo S.N.", 1);
  insert into cst_cson values(9,"500", "ICMS cobrado anteriormente por ST (substituído) ou por antecipação", 1);
  insert into cst_cson values(10,"900", "Outros", 1);

  insert into cst_cson values(11,"00", "Tributada integralmente", 3);
  insert into cst_cson values(12,"10", "Tributada e com cobrança do ICMS por substituição tributária", 3);
  insert into cst_cson values(13,"20",  "Com redução de base de cálculo", 3);
  insert into cst_cson values(14,"30", "Isenta ou não tributada e com cobrança do ICMS por substituição tributária", 3);
  insert into cst_cson values(15,"40", "Isenta", 3);
  insert into cst_cson values(16,"41", "Não tributada", 3);
  insert into cst_cson values(17,"50", "Suspensão", 3);
  insert into cst_cson values(18,"51", "Diferimento", 3);
  insert into cst_cson values(19,"60", "ICMS cobrado anteriormente por substituição tributária", 3);
  insert into cst_cson values(20,"70", "Com redução de base de cálculo e cobrança do ICMS por substituição tributária", 3);
  insert into cst_cson values(21,"90", "Outras", 3);
