int trsp_cad_concluir_fun(){
	char query[MAX_QUERY_LEN];

	trsp_cad_concluindo = 1;
	if(trsp_cad_code_fun())
		return 1;

	if(trsp_cad_trspcode_fun())
		return 1;

	if(trsp_cad_cli_fun())
		return 1;

	if(trsp_cad_cepini_fun())
		return 1;

	if(trsp_cad_cepentr_fun())
		return 1;

	if(trsp_cad_nument_fun())
		return 1;

	if(trsp_cad_orc_fun())
		return 1;

	if(trsp_cad_vlrfrt_fun())
		return 1;

	if(trsp_cad_descfrt_fun())
		return 1;

	if(trsp_cad_obs_fun())
		return 1;

	if(!trsp_cad_alterando){
		sprintf(query,"insert into servico_transporte(code,transportador,cliente,cep_inicio,cep_entrega,num_entrega,orcamento,vlr_frete,valor_desconto_frete,observacoes_entrega) values(%s,%s,%s,'%s','%s',%s,%s,%s,%s,'%s')",
		trsp_cad_code_gchar,
		trsp_cad_trspcode_gchar,
		trsp_cad_clicode_gchar,
		trsp_cad_cepini_gchar,
		trsp_cad_cepentr_gchar,
		trsp_cad_nument_gchar,
		trsp_cad_orc_gchar,
		trsp_cad_vlrfrt_gchar,
		trsp_cad_descfrt_gchar,
		trsp_cad_obs_gchar);
	}else{
		sprintf(query,"update servico_transporte set transportador = %s, cliente = %s, cep_inicio = '%s', cep_entrega = '%s', num_entrega = %s, orcamento = %s, vlr_frete = %s, valor_desconto_frete = %s, observacoes_entrega = '%s' where code = %s",
		trsp_cad_trspcode_gchar,
		trsp_cad_clicode_gchar,
		trsp_cad_cepini_gchar,
		trsp_cad_cepentr_gchar,
		trsp_cad_nument_gchar,
		trsp_cad_orc_gchar,
		trsp_cad_vlrfrt_gchar,
		trsp_cad_descfrt_gchar,
		trsp_cad_obs_gchar,
		trsp_cad_code_gchar);
	}

	if(enviar_query(query)){
		popup(NULL,"Não foi possivel concluir serviço");
		return 1;
	}

	if(trsp_cad_alterando)
		popup(NULL,"serviço atualizado com sucesso");
	else
		popup(NULL,"serviço concluído com sucesso");

	trsp_cad_cancelar_fun();
	return 0;
}
