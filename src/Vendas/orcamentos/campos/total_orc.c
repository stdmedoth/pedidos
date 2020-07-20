int total_prod_orc(GtkWidget *widget,int posicao)
{
	total_prod_orc_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(total_prod_orc_entry[posicao]));

	if(strlen(total_prod_orc_gchar)<=0)
	{
		total_prod_orc_gchar = malloc(MAX_PRECO_LEN);
		popup(NULL,"O valor total deve ser inserido.\nRepasse os campos");
		gtk_widget_grab_focus(codigo_prod_orc_entry[posicao]);
	}

	return 0;
}
