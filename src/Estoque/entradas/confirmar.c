void est_ent_confirma_fun()
{	
	
	if(est_ent_codigo_fun()!=0)
		return ;
	if(est_ent_data_fun()!=0)
		return ;
	if(est_ent_tipo_fun()!=0)
		return ;
	if(est_ent_client_fun()!=0)
		return ;
	if(est_ent_produto_fun()!=0)
		return ;
	if(est_ent_subgrp_fun()!=0)
		return ;
	if(est_ent_qnt_fun()!=0)
		return ;
	
	char *query;
	query = malloc(MAX_QUERY_LEN);
	sprintf(query,"insert into movimento_estoque( cliente, produto, subgrupo, entradas, tipo_mov, data_mov) values(%s,%s,%s,%s,%i,'%s')",
	est_ent_client_gchar, est_ent_prod_gchar, est_ent_subgrp_gchar, est_ent_qnt_gchar, est_ent_tipo_int, est_ent_data_gchar);	
	if(enviar_query(query)!=0)
	{	
		popup(NULL,"Erro ao tentar movimentar estoque");
		return ;
	}
	popup(NULL,"Movimento feito com sucesso");
	return ;
}
