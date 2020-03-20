
int exclui_ter(GtkWidget *botao,gpointer *ponteiro)
{
	char stringer[10];
	char query[100];
	gchar *cod_delel,*nome_delel;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	cod_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(code_ter_field));
	nome_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(name_ter_field));
	sprintf(query,"select code from terceiros where code = '%s' or name = '%s';",cod_delel,nome_delel);
	autologger(query);
	estado = consultar(query);
	campo = mysql_fetch_row(estado);
	if(campo==NULL)
	{
		popup(NULL,"Terceiro já não existe");
		sprintf(stringer,"%i",tasker("terceiros"));
		gtk_entry_set_text(GTK_ENTRY(code_ter_field),stringer);
		gtk_entry_set_text(GTK_ENTRY(name_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(address_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(type_ter_field),"");
		return 1;
	}
	sprintf(query,"delete from terceiros where code = '%s' or name = '%s';",cod_delel,nome_delel);
	consultar(query);
	query[0] = '\0';
	sprintf(query,"select code from terceiros where code = '%s' or name = '%s';",cod_delel,nome_delel);
	estado = consultar(query);
	campo = mysql_fetch_row(estado);
	if(campo==NULL)
	{
		popup(NULL,"Deletado com sucesso");
		sprintf(stringer,"%i",tasker("terceiros"));
		gtk_entry_set_text(GTK_ENTRY(code_ter_field),stringer);
		gtk_entry_set_text(GTK_ENTRY(name_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(address_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(type_ter_field),"");
		return 0;
		gtk_widget_grab_focus(GTK_WIDGET(code_ter_field));
	}
	else
	{
		popup(NULL,"Não foi possivel deletar");
	}
	return 0;
}
