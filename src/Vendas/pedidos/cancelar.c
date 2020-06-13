int cancelar_ped()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	if(strlen(gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)))<=0)
	{
		gtk_widget_grab_focus(ped_cod_entry);
		popup(NULL,"Insira o código do orcamento");
		return 1;
	}
	sprintf(query,"delete from faturamento where pedido = %s",gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)));
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao reverter faturamento");
		return 1;
	}
	sprintf(query,"delete from movimento_estoque where pedido = %s",gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)));
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao reverter estoque");
		return 1;
	}
	
	sprintf(query,"update pedidos set status = 2 where code = '%s'",gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)));
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao inserir valor total");
		return 1;
	}

	popup(NULL,"Pedido cancelado com sucesso!");
	return 0;
}
