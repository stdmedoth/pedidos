int cad_relat_excluir()
{
	MYSQL_ROW row;

	char query[MAX_QUERY_LEN];
	if(cad_relat_code()!=0)
		return 1;

	sprintf(query,"select * from criador_relat where code = %s",cad_rel_code_gchar);
	if((row = mysql_fetch_row(consultar(query)))==NULL)
	{
		alterando_cad_rel = 0;
		popup(NULL,"Relatório não existe para ser excluido");
		return 1;
	}

	sprintf(query,"delete from criador_relat where code = %s",cad_rel_code_gchar);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Não foi possivel excluir Relatorio");
		return 1;
	}
	popup(NULL,"Relatorio excluido com sucesso!");
	cad_relat_cancelar();
	return 0;
}
