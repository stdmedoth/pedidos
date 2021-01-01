void est_ent_confirmar_fun()
{
	concluindo_mov_ent_est=1;

	if(est_ent_codigo_fun())
		return ;

	if(est_ent_data_fun())
		return ;

	if(est_ent_tipo_fun())
		return ;

	if(est_ent_client_fun())
		return ;

	if(est_ent_est_fun())
		return ;

	if(est_ent_produto_fun())
		return ;

	if(est_ent_qnt_fun())
		return ;

	if(est_ent_ped_fun())
		return ;

	if(est_ent_obs_fun())
		return ;

	char *query;
	query = malloc(MAX_QUERY_LEN);
	if(alterando_mov_ent_est == 0){
		sprintf(query,"insert into movimento_estoque( cliente, produto, estoque, pedido, entradas, tipo_mov, data_mov, obs) values(%s,%s,%i, %s, %s,%i,STR_TO_DATE('%s','%%d/%%m/%%Y'), '%s')",
		est_ent_client_gchar, est_ent_prod_gchar, est_ent_est_int, est_ent_ped_gchar, est_ent_qnt_gchar, est_ent_tipo_int, est_ent_data_gchar, est_ent_obs_gchar);
	}
	else{
			sprintf(query,"update movimento_estoque set cliente = %s, produto = %s, estoque = %i, pedido = %s, entradas = %s, tipo_mov = %i, data_mov = STR_TO_DATE('%s','%%d/%%m/%%Y'), obs = '%s' where code = %s",
		est_ent_client_gchar, est_ent_prod_gchar, est_ent_est_int, est_ent_ped_gchar, est_ent_qnt_gchar, est_ent_tipo_int, est_ent_data_gchar, est_ent_obs_gchar, est_ent_cod_gchar);
	}
	if(enviar_query(query)!=0){
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
