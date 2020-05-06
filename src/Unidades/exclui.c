int deleta_und()
{
	g_print("Iniciando deleta_prod()\n");
	char stringer[10];
	char query[MAX_QUERY_LEN];
	gchar *codigo;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	codigo = malloc(MAX_CODE_LEN);
	codigo = (gchar *)gtk_entry_get_text(GTK_ENTRY(code_und_field));
	sprintf(query,"select code from unidades where code = '%s'",codigo);
	autologger(query);
	estado = consultar(query);
	campo = mysql_fetch_row(estado);
	if(campo==NULL)
	{
		popup(NULL,"Unidade não existente");
		sprintf(stringer,"%i",tasker("unidades"));
		gtk_entry_set_text(GTK_ENTRY(code_und_field),stringer);
		gtk_entry_set_text(GTK_ENTRY(name_und_field),"");
		gtk_entry_set_text(GTK_ENTRY(sigla_und_field),"");
		gtk_entry_set_text(GTK_ENTRY(mult_und_field),"");
		gtk_widget_grab_focus (GTK_WIDGET(listar));
		return 1;
	}
	sprintf(query,"delete from unidades where code = '%s';",codigo);
	if(enviar_query(query)==0)
	{
		popup(NULL,"Deletado com sucesso");
		sprintf(stringer,"%i",tasker("unidades"));
		gtk_entry_set_text(GTK_ENTRY(code_und_field),stringer);
		gtk_entry_set_text(GTK_ENTRY(name_und_field),"");
		gtk_entry_set_text(GTK_ENTRY(sigla_und_field),"");
		gtk_entry_set_text(GTK_ENTRY(mult_und_field),"");
		gtk_widget_grab_focus (GTK_WIDGET(code_und_field));
	}
	else
	{
		popup(NULL,"Não foi possivel deletar");
	}
	alterando_und=0;
	return 0;
}

