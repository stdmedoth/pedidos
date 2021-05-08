int cheque_concluir_fun(){

	char query[MAX_QUERY_LEN];

	if(cheque_code_fun()){
		return 1;
	}
	if(cheque_conta_fun()){
		return 1;
	}
	if(cheque_numero_fun()){
		return 1;
	}
	if(cheque_serie_fun()){
		return 1;
	}
	if(cheque_bnc_fun()){
		return 1;
	}
	if(cheque_pgnt_fun()){
		return 1;
	}
	if(cheque_valor_fun()){
		return 1;
	}
	if(cheque_dtemissao_fun()){
		return 1;
	}
	if(cheque_alterando){
		sprintf(query, "update cheque set conta = '%s', numero = '%s', serie = '%s', banco = %s, pagante = %s, data_emissao = STR_TO_DATE('%s', '%%d/%%m/%%Y'), valor = %s where code = %s",
			cheque_conta_gchar,
			cheque_numero_gchar,
			cheque_serie_gchar,
			cheque_bnccode_gchar,
			cheque_pgntcode_gchar,
			cheque_dtemissao_gchar,
			cheque_valor_gchar,
			cheque_code_gchar);	
	}else{

		sprintf(query, "insert into cheque values(%s, '%s', '%s', '%s', %s, %s, STR_TO_DATE('%s', '%%d/%%m/%%Y'), %s)",
			cheque_code_gchar,
			cheque_conta_gchar,
			cheque_numero_gchar,
			cheque_serie_gchar,
			cheque_bnccode_gchar,
			cheque_pgntcode_gchar,
			cheque_dtemissao_gchar,
			cheque_valor_gchar);
	}

	if(enviar_query(query)){
		popup(NULL,"Não foi possível enviar cheque");
		return 1;
	}

	if(cheque_alterando){
		popup(NULL,"Cheque atualizado com sucesso");
	}else{
		popup(NULL,"Cheque criado com sucesso");
	}
	cheque_cancelar_fun();
	return 0;
	
}