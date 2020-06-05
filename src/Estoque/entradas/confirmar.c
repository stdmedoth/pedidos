void est_ent_confirmar_fun()
{	
	concluindo_mov_ent_est=1;

	if(est_ent_codigo_fun()!=0)
		return ;
	if(est_ent_data_fun()!=0)
		return ;
	if(est_ent_tipo_fun()!=0)
		return ;
	if(est_ent_client_fun()!=0)
		return ;
	if(est_ent_est_fun()!=0)
		return ; 
	if(est_ent_produto_fun()!=0)
		return ;
	if(est_ent_subgrp_fun()!=0)
		return ;
	if(est_ent_qnt_fun()!=0)
		return ;
	if(est_ent_ped_fun()!=0)
		return ;
	
	char *query;
	query = malloc(MAX_QUERY_LEN);
	if(alterando_mov_ent_est == 0)
	{
		sprintf(query,"insert into movimento_estoque( cliente, produto, estoque, pedido, subgrupo, entradas, tipo_mov, data_mov) values(%s,%s,%i, %s, %s,%s,%i,'%s')",
		est_ent_client_gchar, est_ent_prod_gchar, est_ent_est_int, est_ent_ped_gchar, est_ent_subgrp_gchar, est_ent_qnt_gchar, est_ent_tipo_int, est_ent_data_gchar);	
	}
	else
	{
			sprintf(query,"update movimento_estoque set cliente = %s, produto = %s, estoque = %i, pedido = %s, subgrupo = %s, entradas = %s, tipo_mov = %i, data_mov = '%s' where code = %s",
		est_ent_client_gchar, est_ent_prod_gchar, est_ent_est_int, est_ent_ped_gchar, est_ent_subgrp_gchar, est_ent_qnt_gchar, est_ent_tipo_int, est_ent_data_gchar, est_ent_cod_gchar);	
	}
	if(enviar_query(query)!=0)
	{	
		popup(NULL,"Erro ao tentar movimentar estoque");
		return ;
	}
	if(alterando_mov_ent_est == 0)
		popup(NULL,"Movimento feito com sucesso");
	else
		popup(NULL,"Movimento atualizado com sucesso");
		
	est_ent_cancelar_fun();
	
	return ;
}
