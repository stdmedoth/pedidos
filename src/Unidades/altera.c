int altera_und()
{
	char task[10];
	char query[100];
	gchar *cod_delel,*nome_delel;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	cod_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(code_field));
	nome_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(name_field));
	sprintf(query,"select * from produtos where code = '%s' or name = '%s';",cod_delel,nome_delel);
	g_print("query: %s\n",query);
	autologger(query);
	estado = consultar(query);
	g_print("verificando estado da alteracao\n");
	campo = mysql_fetch_row(estado);
	if(campo==NULL)
	{
		g_print("produto não existe para ser alterado\n");
		popup(NULL,"Produto não existe");
		sprintf(task,"%i",tasker("produtos"));
		gtk_entry_set_text(GTK_ENTRY(code_field),task);
		gtk_entry_set_text(GTK_ENTRY(name_field),"");
		gtk_entry_set_text(GTK_ENTRY(price_field),"");
		gtk_entry_set_text(GTK_ENTRY(supp_field),"");
		gtk_widget_grab_focus (GTK_WIDGET(code_field));
		tipo_ter = NULL;
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(code_field),campo[0]);
	code_prod();
	gtk_entry_set_text(GTK_ENTRY(name_field),campo[1]);
	name_prod();
	gtk_entry_set_text(GTK_ENTRY(price_field),campo[2]);
	price_prod();
	gtk_entry_set_text(GTK_ENTRY(supp_field),campo[3]);
	supp_prod();
	sprintf(query,"delete from produtos where code = '%s' or name = '%s';",cod_delel,nome_delel);
	autologger("Alterou o produto abaixo");
	autologger(query);
	autologger(campo[0]);
	autologger(campo[1]);
	autologger(campo[2]);
	autologger(campo[3]);
	consultar(query);
	query[0] = '\0';
	sprintf(query,"select * from produtos where code = '%s' or name = '%s';",cod_delel,nome_delel);
	estado = consultar(query);
	campo = mysql_fetch_row(estado);
	if(campo!=NULL)
	{
		popup(NULL,"Não será possivel alterar");
		return 1;
	}
	else
	{
		autologger("Alterado com sucesso");
	}
	//tipo_ter = NULL;
	return 0;
}

