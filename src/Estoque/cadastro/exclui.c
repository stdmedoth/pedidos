int est_cad_excluir()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	if(est_cad_code()!=0)
		return 1;

	sprintf(query,"select * from movimento_estoque where estoque = %s",est_cad_cod_gchar);
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível consultar movimentos existentes");
		return 1;
	}
	if((row = mysql_fetch_row(res))){
		if(PopupBinario("Estoque possui movimentos vinculados, Deseja excluir todos?", "Sim! Remova os movimentos desse estoque", "Não! Cancelar o processo")){
			sprintf(query,"delete from  movimento_estoque where estoque = %s",est_cad_cod_gchar);
			if(enviar_query(query)!=0){
				popup(NULL,"Não foi possível deletar movimentos");
				return 1;
			}
		}else{
			return 1;
		}
	}

	sprintf(query,"delete from estoques where code = %s",est_cad_cod_gchar);
	if(enviar_query(query)!=0){
		popup(NULL,"Não foi possível deletar estoque");
		return 1;
	}

	popup(NULL,"Excluído com sucesso");
	est_cad_cancelar();

	return 0;
}
