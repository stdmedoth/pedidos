int trsp_cad_excluir_fun(){
	char query[MAX_QUERY_LEN];
	if(trsp_cad_code_fun())
		return 1;

	sprintf(query,"delete from servico_transporte where code = %s",trsp_cad_code_gchar);
	if(enviar_query(query)){
		popup(NULL,"Não foi possível deletar servico");
		return 1;
	}
	popup(NULL,"Excluído com sucesso");
	trsp_cad_cancelar_fun();
	return 0;
}
