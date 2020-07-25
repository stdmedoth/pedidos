int cancelar_ped()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	char *ped_code;

	ped_code = (gchar*)gtk_entry_get_text(GTK_ENTRY(ped_cod_entry));

	if(strlen(ped_code)<=0)
	{
		gtk_widget_grab_focus(ped_cod_entry);
		popup(NULL,"Insira o código do orcamento");
		return 1;
	}
	sprintf(query,"delete from faturamento where pedido = %s",ped_code);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao reverter faturamento");
		return 1;
	}
	sprintf(query,"delete from movimento_estoque where pedido = %s",ped_code);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao reverter estoque");
		return 1;
	}

	sprintf(query,"update pedidos set status = 2 where code = '%s'",ped_code);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao inserir valor total");
		return 1;
	}

	popup(NULL,"Pedido cancelado com sucesso!");
	return 0;
}
