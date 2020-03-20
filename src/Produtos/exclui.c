
int deleta_prod()
{
	g_print("Iniciando deleta_prod()\n");
	char stringer[10];
	char query[100];
	gchar *cod_delel,*nome_delel;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	cod_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(code_field));
	nome_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(name_field));
	sprintf(query,"select code from produtos where code = '%s' or name = '%s';",cod_delel,nome_delel);
	autologger(query);
	estado = consultar(query);
	campo = mysql_fetch_row(estado);
	if(campo==NULL)
	{
		popup(NULL,"Produto já não existe");
		sprintf(stringer,"%i",tasker("produtos"));
		gtk_entry_set_text(GTK_ENTRY(code_field),stringer);
		gtk_entry_set_text(GTK_ENTRY(name_field),"");
		gtk_entry_set_text(GTK_ENTRY(price_field),"");
		gtk_entry_set_text(GTK_ENTRY(supp_field),"");
		gtk_widget_grab_focus (GTK_WIDGET(listar));
		return 1;
	}
	sprintf(query,"delete from produtos where code = '%s' or name = '%s';",cod_delel,nome_delel);
	consultar(query);
	query[0] = '\0';
	sprintf(query,"select code from produtos where code = '%s' or name = '%s';",cod_delel,nome_delel);
	estado = consultar(query);
	campo = mysql_fetch_row(estado);
	if(campo==NULL)
	{
		popup(NULL,"Deletado com sucesso");
		sprintf(stringer,"%i",tasker("produtos"));
		gtk_entry_set_text(GTK_ENTRY(code_field),stringer);
		gtk_entry_set_text(GTK_ENTRY(name_field),"");
		gtk_entry_set_text(GTK_ENTRY(price_field),"");
		gtk_entry_set_text(GTK_ENTRY(supp_field),"");
		gtk_widget_grab_focus (GTK_WIDGET(code_field));
		return 0;
	}
	else
	{
		popup(NULL,"Não foi possivel deletar");
	}
	return 0;
}

