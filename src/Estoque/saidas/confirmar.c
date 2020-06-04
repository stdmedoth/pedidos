void est_said_confirma_fun()
{	
	
	if(est_said_codigo_fun()!=0)
		return ;
	if(est_said_data_fun()!=0)
		return ;
	if(est_said_tipo_fun()!=0)
		return ;
	if(est_said_client_fun()!=0)
		return ;
	if(est_said_produto_fun()!=0)
		return ;
	if(est_said_subgrp_fun()!=0)
		return ;
	if(est_said_qnt_fun()!=0)
		return ;
	
	char *query;
	query = malloc(MAX_QUERY_LEN);
	sprintf(query,"insert into movimento_estoque( cliente, produto, subgrupo, saidas, tipo_mov, data_mov) values(%s,%s,%s,%s,%i,'%s')",
	est_said_client_gchar, est_said_prod_gchar, est_said_subgrp_gchar, est_said_qnt_gchar, est_said_tipo_int, est_said_data_gchar);	
	if(enviar_query(query)!=0)
	{	
		popup(NULL,"Erro ao tentar movimentar estoque");
		return ;
	}
	popup(NULL,"Movimento feito com sucesso");
	return ;
}
