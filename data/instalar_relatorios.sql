use erp;

create table dados (code int primary key,
nome varchar(50) not null default 'TipoIndefinido');

create table relat_tabelas_id( code int primary key auto_increment,
nome varchar(50) not null,
sobre varchar(300),
inner_query varchar(300),
qnt_colunas int);

create table relat_tab_campos( code int primary key auto_increment,
tabela int default 1,
nome varchar(50),
sobre varchar(300),
query varchar(100),
tipo_dado int default 1,
foreign key(tabela) references relat_tabelas_id(code),
foreign key(tipo_dado) references dados(code));

create table criador_relat( code int,
nome varchar(30) default "Relatorio_SemNome",
tabela int default 1,
campos int default 1,
foreign key(tabela) references relat_tabelas_id(code),
foreign key(campos) references relat_tab_campos(code));

insert into dados(code,nome) values
(1,"texto"),
(2,"numero inteiro"),
(3,"numero real"),
(4,"dinheiro"),
(5,"data");

insert into relat_tabelas_id(nome, sobre, inner_query, qnt_colunas) values
('produtos','Tabela responsável por armazenar os dados dos produtos',
' from produtos as p inner join unidades as u inner join grupos as g inner join terceiros as t on p.fornecedor = t.code and p.grupo = g.code and p.unidades = u.code',8),

('terceiros','Tabela responsável por armazenar os dados dos clientes e fornecedores',
' from terceiros as t',34),

('orçamentos','Tabela responsável por armazenar os orcamentos criados e seus status',
' from orcamentos as o inner join terceiros as t inner join tipo_pagamento as tp on o.cliente = t.code and o.tipopag = tp.code',5),

('pedidos','Tabela responsável por armazenar os pedidos criados e seus status',
' from pedidos as p',5),

('Movimentos estoque','Tabela responsável por mostrar movimentações de produtos no estoque',
' from movimento_estoque as m_e inner join estoques as e inner join terceiros as t inner join produtos as p inner join grupos as g on m_e.estoque = e.code and m_e.cliente = t.code and m_e.produto = p.code and m_e.subgrupo = g.code;',10),

('Produtos por Orçamento/Pedidos','Tabela responsável por armazenar os produtos contidos em orçamentos',
' from Produto_Orcamento as p_o',10),

('Faturamento','Tabela responsável pela visualização de valor das vendas',
  ' from faturamento as f inner join pedidos as p inner join terceiros as t inner join tipo_movimentos as t_m on p.code = f.pedido and f.cliente = t.code and f.tipo_mov = t_m.code',7);



insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(1, 'Código' , 'Visualizar código do produto', 'p.code',2),
(1, 'Nome',  'Visualizar nome do produto', 'p.nome ',1),
(1, 'Peso',  'Visualizar peso do produto', 'p.peso',3),
(1, 'UND. Varejo', 'Unidades para venda varejo', 'u.nome',3),
(1, 'UND. Atacado', 'Unidades para venda Atacado', 'u.nome',3),
(1, 'Fornecedor', 'Terceiro fornecedor do produto', 't.razao',2),
(1, 'Grupo', 'Grupo vinculado ao produto', 'g.nome',1),
(1, 'Nivel Grupo', 'Nivel do grupo vinculado (Não utilizado)', 'p.grupo_nivel',2),
(1, 'Observações', 'Observações do produto', 'observacoes',1);

insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(2, 'Código' , 'Visualizar código do terceiro', 't.code',2),
(2, 'Código NF-e',  'Visualizar código do terceiro para tirar nfe', 't.code_nfe',1),
(2, 'Razão Social/Nome',  'Visualizar Nome ou Razão da empresa/pessoa', 't.razao',1),
(2, 'Documento', 'CNPJ ou RG do Terceiro', 't.doc',1),
(2, 'IE', 'CEP do Terceiro', 't.ie',1),
(2, 'CEP', 'CEP do Terceiro', 't.cep',1),
(2, 'Logradouro', 'Logradouro do Terceiro', 't.endereco',1),
(2, 'Cidade', 'Cidade do Terceiro', 't.cidade',1),
(2, 'Número ', 'Unidade Federativa do Terceiro', 't.uf',1),
(2, 'Tipo Log', 'Tipo de logradouro: Rua,Avenida,Rodovia', 't.uf',1),
(2, 'Telefone', 'Número de telefone do terceiro', 't.telefone',1),
(2, 'Contato telefone', 'Contato para o telefone', 't.contatot',1),
(2, 'Celular', 'Número de celular do terceiro', 't.celular',1),
(2, 'Contato celular', 'Contato para o celular', 't.contatoc',1),
(2, 'Email', 'Email do terceiro', 't.email',1),
(2, 'Contato Email', 'Contato para o email', 't.contatoe',1),
(2, 'Transp. Nome', 'Nome da transp. vinc. ao Terceiro', 't.transp_nome',1),
(2, 'Transp. Documento', 'CNPJ da transp. vinc. ao Terceiro', 't.transp_cnpj',1),
(2, 'Transp. IE', 'Inscrição Estadual da transp. vinc. ao Terceiro', 't.transp_ie',1),
(2, 'Transp .Logradouro', 'Logradouro da transp. vinc. ao Terceiro', 't.transp_logradouro',1),
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
(5, 'Nome Produto','Nome Produto movimentado', 'p.nome',1),
(5, 'Subgrupo', 'Subgrupo movimentado', 'g.nome',1),
(5, 'Cód. Cliente','Código do cliente vinculado ao movimento', 'm_e.cliente',2),
(5, 'Nome Cliente','Nome do cliente vinculado ao movimento', 't.razao',1),
(5, 'Movimento Saídas','Quantidade de saídas no movimento', 'm_e.saidas',3),
(5, 'Movimento Entradas','Quantidade de entradas no movimento', 'm_e.entradas',3),
(5, 'Tipo','Tipo de movimento (venda,compra,devolução)', 'm_e.tipo_mov',2),
(5, 'Data','Data do movimento', 'm_e.data_mov',5);

insert into relat_tab_campos(tabela, nome, sobre, query, tipo_dado) values
(7, 'Cód.','Código dos movimentos de venda', 'f.code',2),
(7, 'Cód. Pedido','Código dos pedido vinculado ao faturamento', 'p.code',2),
(7, 'Valor Entrada','Valor de entradas faturamento', 'f.entrada',4),
(7, 'Valor Saída','Valor de entradas faturamento', 'f.saida',4),
(7, 'Data','Data do movimento no faturamento', 'f.data_mov',5),
(7, 'Tipo','Tipo de movimento(venda,devolução)', 't_m.nome',1);
