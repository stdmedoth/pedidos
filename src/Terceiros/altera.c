int altera_ter(GtkWidget *botao,gpointer *ponteiro)
{
	char task[10];
	char query[100];
	gchar *cod_delel,*nome_delel;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	cod_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(code_ter_field));
	nome_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(name_ter_field));
	sprintf(query,"select * from terceiros where code = '%s' or name = '%s';",cod_delel,nome_delel);
	g_print("query: %s\n",query);
	autologger(query);
	estado = consultar(query);
	g_print("verificando estado da alteracao\n");
	campo = mysql_fetch_row(estado);
	if(campo==NULL)
	{
		g_print("terceiro não existe para ser alterado\n");
		popup(NULL,"Terceiro não existe");
		sprintf(task,"%i",tasker("terceiros"));
		gtk_entry_set_text(GTK_ENTRY(code_ter_field),task);
		gtk_entry_set_text(GTK_ENTRY(name_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(address_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(type_ter_field),"");
		gtk_widget_grab_focus (GTK_WIDGET(code_ter_field));
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(code_ter_field),campo[0]);
	code_terc();
	gtk_entry_set_text(GTK_ENTRY(name_ter_field),campo[1]);
	name_terc();
	gtk_entry_set_text(GTK_ENTRY(address_ter_field),campo[2]);
	address_terc();
	gtk_entry_set_text(GTK_ENTRY(type_ter_field),campo[3]);
	set_cliente();
	sprintf(query,"delete from terceiros where code = '%s' or name = '%s';",cod_delel,nome_delel);
	autologger("Alterou o produto abaixo");
	autologger(query);
	consultar(query);
	query[0] = '\0';
	sprintf(query,"select * from terceiros where code = '%s' or name = '%s';",cod_delel,nome_delel);
	estado = consultar(query);
	campo = mysql_fetch_row(estado);
	if(campo!=NULL)
	{
		popup(NULL,"Não será possivel alterar");
		return 1;
	}
	return 0;
}
