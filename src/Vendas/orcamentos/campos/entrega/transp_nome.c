int orc_transp_nomec()
{

	orc_transp_nome = (gchar *) gtk_entry_get_text(GTK_ENTRY(orc_transp_nome_entry));
	if(strlen(orc_transp_nome)>MAX_RAZ_LEN)
	{
		popup(NULL,"Nome muito grande\nPor favor diminua");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_nome_entry));
		return 1;
	}
	if(strlen(orc_transp_nome)<=0)
	{
		if(terceiros.criticar.entrega==0)
		{
			orc_transp_num = malloc(MAX_CODE_LEN);
			gtk_widget_grab_focus(orc_transp_cnpj_entry);
			return 0;
		}
		popup(NULL,"Por favor insira um nome para a Transportadora");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_nome_entry));
		return 1;
	}
	else
	{
		gtk_widget_grab_focus(orc_transp_cnpj_entry);
	}
	g_print("nome: %s\n",orc_transp_nome);
	return 0;
}
