void est_said_confirmar_fun()
{
	concluindo_mov_said_est=1;

	if(est_said_codigo_fun()!=0)
		return ;
	if(est_said_data_fun()!=0)
		return ;
	if(est_said_tipo_fun()!=0)
		return ;
	if(est_said_client_fun()!=0)
		return ;
	if(est_said_est_fun()!=0)
		return ;
	if(est_said_produto_fun()!=0)
		return ;
	if(est_said_qnt_fun()!=0)
		return ;
	if(est_said_ped_fun()!=0)
		return ;
	if(est_said_obs_fun())
		return ;

	char *query;
	query = malloc(MAX_QUERY_LEN);
	if(alterando_mov_said_est == 0){
		sprintf(query,"insert into movimento_estoque( cliente, produto, estoque, pedido, saidas, tipo_mov, data_mov, obs) values(%s,%s,%i, %s,%s,%i,STR_TO_DATE('%s','%%d/%%m/%%Y'),'%s')",
		est_said_client_gchar, est_said_prod_gchar, est_said_est_int, est_said_ped_gchar, est_said_qnt_gchar, est_said_tipo_int, est_said_data_gchar, est_said_obs_gchar);
	}
	else{
		sprintf(query,"update movimento_estoque set cliente = %s, produto = %s, estoque = %i, pedido = %s, saidas = %s, tipo_mov = %i, data_mov = STR_TO_DATE('%s','%%d/%%m/%%Y'), obs = '%s' where code = %s",
		est_said_client_gchar, est_said_prod_gchar, est_said_est_int, est_said_ped_gchar, est_said_qnt_gchar, est_said_tipo_int, est_said_data_gchar, est_said_obs_gchar, est_said_cod_gchar);
	}
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao tentar movimentar estoque");
		return ;
	}
	if(alterando_mov_said_est == 0)
		popup(NULL,"Movimento feito com sucesso");
	else
		popup(NULL,"Movimento atualizado com sucesso");

	est_said_cancelar_fun();

	return ;
}
