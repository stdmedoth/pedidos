int verifica_chaves()
{
	char *query;

	query = malloc(MAX_QUERY_LEN);
	gchar *cod_delel;
	cod_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(code_ter_field));
	//cliente - precos
	sprintf(query,"select * from precos where terceiro = %s;",cod_delel);
	vetor = consultar(query);
	if(vetor ==NULL)
	{
		popup(NULL,"Erro ao tentar verificar pedidos para o terceiro");
		return 1;
	}
	if((campos = mysql_fetch_row(vetor))!=NULL)
	{
		popup(NULL,"Existem Precos para esse Cliente");
		return 1;
	}

	//fornecedor - produtos
	sprintf(query,"select * from produtos where fornecedor = %s",cod_delel);
	vetor = consultar(query);
	if(vetor ==NULL)
	{
		popup(NULL,"Erro ao tentar verificar pedidos para o terceiro");
		return 1;
	}
	if((campos = mysql_fetch_row(vetor))!=NULL)
	{
		popup(NULL,"Existem Produtos para esse Fornecedor");
		return 1;
	}

	//cliente - pedidos
	sprintf(query,"select * from pedidos where cliente = %s",cod_delel);
	vetor = consultar(query);
	if(vetor ==NULL)
	{
		popup(NULL,"Erro ao tentar verificar pedidos para o terceiro");
		return 1;
	}
	if((campos = mysql_fetch_row(vetor))!=NULL)
	{
		popup(NULL,"Existem Pedidos para esse cliente");
		return 1;
	}

	//pedidos - vendedor
	sprintf(query,"select * from pedidos where vendedor = %s",cod_delel);
	vetor = consultar(query);
	if(vetor ==NULL)
	{
		popup(NULL,"Erro ao tentar verificar pedidos para o terceiro");
		return 1;
	}
	if((campos = mysql_fetch_row(vetor))!=NULL)
	{
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

	if(verifica_chaves()!=0)
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
