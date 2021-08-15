void planilha_create_querys(){
	planilhas_gerar_querys[PLANL_MOD_TERCEIROS] = malloc(MAX_QUERY_LEN);
	sprintf(planilhas_gerar_querys[PLANL_MOD_TERCEIROS],
		"SELECT t.code, t.razao as 'Nome', t.nome_fantasia as 'Nome Fantasia', t.doc as 'CPF/CNPJ', t.ie as 'IE/RG', t.cep as 'CEP', t.endereco as 'Logradouro', t.numrua as 'Numero', t.bairro as 'Bairro', t.cidade as 'Cidade', t.uf as 'UF', IF(t.transp_code = 0, 'Não Inf.', t.transp_code) as 'Código Transportadora', t.transp_cep as 'CEP Entrega', t.transp_logradouro as 'Logradouro Entrega', t.transp_bairro as 'Bairro Entrega', t.transp_cidade as 'Cidade Entrega', t.transp_telefone as 'Telefone  Entrega', (SELECT GROUP_CONCAT(nome ORDER BY code SEPARATOR ' | ') from contatos c2 where terceiro = t.code) as 'nome', (SELECT GROUP_CONCAT(telefone ORDER BY code SEPARATOR ' | ') from contatos c2 where terceiro = t.code) as 'telefone', (SELECT GROUP_CONCAT(celular ORDER BY code SEPARATOR ' | ') from contatos c2 where terceiro = t.code) as 'celular', (SELECT GROUP_CONCAT(email ORDER BY code SEPARATOR ' | ') from contatos c2 where terceiro = t.code) as 'email' FROM terceiros t;");

	planilhas_gerar_querys[PLANL_MOD_PRODUTOS] = malloc(MAX_QUERY_LEN);
	sprintf(planilhas_gerar_querys[PLANL_MOD_PRODUTOS],
		"SELECT * FROM produtos");

	planilhas_gerar_querys[PLANL_MOD_MOVIMENTOS] = malloc(MAX_QUERY_LEN);
	sprintf(planilhas_gerar_querys[PLANL_MOD_MOVIMENTOS],
		"SELECT me.code as 'Código Movimento',  me.pedido as 'Código Pedido', p.nome as 'Produto', t.razao as 'Cliente/Fornecedor', me.entradas - saidas as 'Entradas/Saidas', DATE_FORMAT(data_mov, '%%d/%%m/%%Y'),  CASE  WHEN tipo_mov = 0 THEN 'Venda' WHEN tipo_mov = 1 THEN 'Dev. Venda' WHEN tipo_mov = 2 THEN 'Compra' WHEN tipo_mov = 3 THEN 'Dev. Compra' WHEN tipo_mov = 4 THEN 'Outras' END as 'Operação', me.obs as 'Observação' FROM movimento_estoque me  INNER JOIN estoques e  on me.estoque = e.code INNER JOIN terceiros t  on me.cliente = t.code  INNER JOIN produtos p  on me.produto = p.code");


	planilhas_gerar_querys[PLANL_MOD_PEDIDOS] = malloc(MAX_QUERY_LEN);
	sprintf(planilhas_gerar_querys[PLANL_MOD_PEDIDOS],
		"select p2.code as 'Cód. Pedido', CASE WHEN p2.status = 0 THEN  'Pendente' WHEN p2.status = 1 THEN 'emitido' WHEN p2.status THEN 'Cancelado' END as 'Status Pedidos', t.code as 'Cód. Cliente', t.razao as 'Nome/Razão Cliente', po.item as 'Item', p.code as 'Cód. Produto', p.nome as 'Nome Produto', po.unidades as 'Quantidade', po.valor_unit as 'Valor Unitário', po.valor_orig as 'Origem Valor' from Produto_Orcamento po INNER JOIN pedidos p2 ON  po.code = p2.code INNER JOIN produtos p on p.code = po.produto INNER JOIN terceiros t ON p2.cliente = t.code ;");

	planilhas_gerar_querys[PLANL_MOD_ORCAMENTOS] = malloc(MAX_QUERY_LEN);
	sprintf(planilhas_gerar_querys[PLANL_MOD_ORCAMENTOS],
		"select o.code as 'Cód. Orçamento', t.code as 'Cód. Cliente', t.razao as 'Nome/Razão Cliente', po.item as 'Item', p.code as 'Cód. Produto', p.nome as 'Nome Produto', po.unidades as 'Quantidade', po.valor_unit as 'Valor Unitário', po.valor_orig as 'Origem Valor' from Produto_Orcamento po INNER JOIN orcamentos o ON  po.code = o.code  INNER JOIN produtos p on p.code = po.produto INNER JOIN terceiros t ON o.cliente = t.code ;");

	planilhas_gerar_querys[PLANL_MOD_FINAN_REC] = malloc(MAX_QUERY_LEN);
	sprintf(planilhas_gerar_querys[PLANL_MOD_FINAN_REC],
		"SELECT  t.code as 'Código Título',pt.posicao as 'Parcela',t2.razao as 'Cliente/Fornecedor',CASE WHEN status = 0 THEN 'Baixado'WHEN status = 1 THEN 'Parciamente Baixado'WHEN status = 2 THEN 'Pendente'END as 'Situação do Título',t.qnt_parcelas as 'Qnt. Parcelas',CASE WHEN t.tipo_titulo = 0 THEN 'Receber'WHEN t.tipo_titulo = 1 THEN 'Pagar'END  as 'Tipo Título',b.nome ,DATE_FORMAT(pt.data_criacao, '%%d/%%m/%%Y') as 'Criado em',DATE_FORMAT(pt.data_vencimento , '%%d/%%m/%%Y') as 'Vence em',  REPLACE(valor, '.', ',') as 'Valor' FROM titulos t INNER JOIN terceiros t2 ON t2.code = t.cliente INNER JOIN parcelas_tab pt ON t.code = pt.parcelas_id LEFT JOIN bancos b ON b.code = pt.banco WHERE t.tipo_titulo = 0");

	planilhas_gerar_querys[PLANL_MOD_FINAN_PAG] = malloc(MAX_QUERY_LEN);
	sprintf(planilhas_gerar_querys[PLANL_MOD_FINAN_PAG],
		"SELECT  t.code as 'Código Título',pt.posicao as 'Parcela',t2.razao as 'Cliente/Fornecedor',CASE WHEN status = 0 THEN 'Baixado'WHEN status = 1 THEN 'Parciamente Baixado'WHEN status = 2 THEN 'Pendente'END as 'Situação do Título',t.qnt_parcelas as 'Qnt. Parcelas',CASE WHEN t.tipo_titulo = 0 THEN 'Receber'WHEN t.tipo_titulo = 1 THEN 'Pagar'END as 'Tipo Título' ,b.nome ,DATE_FORMAT(pt.data_criacao, '%%d/%%m/%%Y') as 'Criado em',DATE_FORMAT(pt.data_vencimento , '%%d/%%m/%%Y') as 'Vence em',  REPLACE(valor, '.', ',') as 'Valor' FROM titulos t INNER JOIN terceiros t2 ON t2.code = t.cliente INNER JOIN parcelas_tab pt ON t.code = pt.parcelas_id LEFT JOIN bancos b ON b.code = pt.banco WHERE t.tipo_titulo = 1");

	planilhas_gerar_querys[PLANL_MOD_FINAN_FLUXO] = malloc(MAX_QUERY_LEN);
	sprintf(planilhas_gerar_querys[PLANL_MOD_FINAN_FLUXO],
		"SELECT   t.code as 'Código Título', pt.posicao as 'Parcela', t2.razao as 'Cliente/Fornecedor', CASE  WHEN status = 0 THEN 'Baixado' WHEN status = 1 THEN 'Parciamente Baixado' WHEN status = 2 THEN 'Pendente' END as 'Situação do Título', t.qnt_parcelas as 'Qnt. Parcelas', CASE  WHEN t.tipo_titulo = 0 THEN 'Receber' WHEN t.tipo_titulo = 1 THEN 'Pagar' END as 'Tipo Título' , b.nome , DATE_FORMAT(pt.data_criacao, '%%d/%%m/%%Y') as 'Criado em', DATE_FORMAT(pt.data_vencimento , '%%d/%%m/%%Y') as 'Vence em', CASE  WHEN t.tipo_titulo = 0 THEN REPLACE(valor, '.', ',') WHEN t.tipo_titulo = 1 THEN REPLACE(concat('-',valor), '.', ',') END as 'Valor' FROM titulos t  INNER JOIN terceiros t2  ON t2.code = t.cliente  INNER JOIN parcelas_tab pt  ON t.code = pt.parcelas_id  LEFT JOIN bancos b  ON b.code = pt.banco;");
}
