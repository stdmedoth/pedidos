int verifica_ter_chaves(){
	
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	gchar *cod_delel;
	char query[MAX_QUERY_LEN];
	cod_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(code_ter_field));

	//fornecedor - cotacoes
	sprintf(query,"select * from itens_cotacoes where participante_id = %s;",cod_delel);
	vetor = consultar(query);
	if(!vetor){
		popup(NULL,"Erro ao tentar verificar cotacoes para o fornecedor");
		return 1;
	}
	if((campos = mysql_fetch_row(vetor))){
		popup(NULL,"Existem cotações para esse fornecedor");
		return 1;
	}

	//fornecedor - lista distribuição
	sprintf(query,"select * from PessoasDistribuicao where pessoa = %s",cod_delel);
	vetor = consultar(query);
	if(!vetor){
		popup(NULL,"Erro ao tentar verificar lista de distribuicao para a pessoa");
		return 1;
	}
	if((campos = mysql_fetch_row(vetor))){
		popup(NULL,"Esta pessoa está vinculada à uma lista de distribuição");
		return 1;
	}

	//fornecedor - produtos
	sprintf(query,"select * from produtos where fornecedor = %s",cod_delel);
	vetor = consultar(query);
	if(!vetor){
		popup(NULL,"Erro ao tentar verificar produtos para o fornecedor");
		return 1;
	}
	if((campos = mysql_fetch_row(vetor))){
		popup(NULL,"Existem Produtos para esse Fornecedor");
		return 1;
	}

	//cliente - pedidos
	sprintf(query,"select * from pedidos where cliente = %s",cod_delel);
	vetor = consultar(query);
	if(!vetor){
		popup(NULL,"Erro ao tentar verificar pedidos para o terceiro");
		return 1;
	}
	if((campos = mysql_fetch_row(vetor))){
		popup(NULL,"Existem Pedidos para esse cliente");
		return 1;
	}

	//pedidos - vendedor
	sprintf(query,"select * from pedidos where vendedor = %s",cod_delel);
	vetor = consultar(query);
	if(!vetor){
		popup(NULL,"Erro ao tentar verificar pedidos para o terceiro");
		return 1;
	}
	if((campos = mysql_fetch_row(vetor))){
		popup(NULL,"Existem Pedidos para esse vendedor");
		return 1;
	}

	return 0;
}
int exclui_ter(GtkWidget *botao,gpointer *ponteiro)
{
	char stringer[10];
	char query[100];
	gchar *cod_delel;
	GtkTextBuffer *buffer;
	GtkTextIter inicio,fim;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	cod_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(code_ter_field));
	sprintf(query,"select code from terceiros where code = '%s';",cod_delel);
	autologger(query);
	estado = consultar(query);
	campo = mysql_fetch_row(estado);
	if(campo==NULL)
	{
		popup(NULL,"Não existe para ser excluido");
		cancelar_ter();
		return 1;
	}

	if(verifica_ter_chaves()!=0)
		return 1;

	sprintf(query,"delete from terceiros where code = '%s';",cod_delel);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao tentar excluir terceiro");
		return 1;
	}

	sprintf(query,"select code from terceiros where code = '%s';",cod_delel);
	estado = consultar(query);
	campo = mysql_fetch_row(estado);

	if(campo==NULL)
	{
		popup(NULL,"Deletado com sucesso");
		cancelar_ter();
		return 0;
	}
	else
	{
		popup(NULL,"Não foi possivel deletar");
		return 1;
	}


	return 0;
}
