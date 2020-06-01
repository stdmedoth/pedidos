void est_cad_excluir()
{
	char query[MAX_QUERY_LEN];
	if(est_cad_code()!=0)
		return;
		
	sprintf(query,"delete from estoques where code = %s",est_cad_cod_gchar);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Estoque possui pedidos/orcamentos vinculados");
		return ;
	}
	

}
