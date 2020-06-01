void est_cad_concluir()
{	
	char query[MAX_QUERY_LEN];
	if(est_cad_nome()!=0)
		return ;
	
	sprintf(query,"insert into estoques(nome) values('%s')",est_cad_nome_gchar);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao cadastrar estoque");
		return ;
	}
	
	popup(NULL,"Estoque criado com sucesso");
	
}
