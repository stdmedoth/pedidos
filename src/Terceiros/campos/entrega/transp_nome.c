int transp_nomec()
{
	
	transp_nome = (gchar *) gtk_entry_get_text(GTK_ENTRY(transp_nome_entry));
	if(strlen(transp_nome)>MAX_RAZ_LEN)
	{
		popup(NULL,"Nome muito grande\nPor favor diminua");
		gtk_widget_grab_focus(GTK_WIDGET(transp_nome_entry));
		return 1;
	}
	if(strlen(transp_nome)<=0)
	{
		popup(NULL,"Por favor insira um nome para a Transportadora");
		gtk_widget_grab_focus(GTK_WIDGET(transp_nome_entry));
		return 1;
	}
	else
	{
		gtk_widget_grab_focus(transp_cnpj_entry);
	}
	g_print("nome: %s\n",transp_nome);
	return 0;
}
