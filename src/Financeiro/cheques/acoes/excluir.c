int cheque_excluir_fun(){
	char query[MAX_QUERY_LEN];

	if(cheque_code_fun())
		return 1;

	sprintf(query, "delete from cheque where code = %s", cheque_code_gchar);
	if(enviar_query(query)){
		popup(NULL, "Não foi possível excluir");
		return 1;
	}

	popup(NULL,"Cheque excluído com sucesso");
	cheque_cancelar_fun();
	return 0;
}