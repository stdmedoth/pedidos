int total_prod_orc(GtkWidget *widget,int posicao)
{
	total_prod_orc_gchar = malloc(MAX_PRECO_LEN);
	total_prod_orc_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(total_prod_orc_entry[posicao]));
	if(strlen(total_prod_orc_gchar)<=0&&criticar.total!=0)
	{
		popup(NULL,"O valor total deve ser inserido,\n\tDeixe o sistema inserir, ou insira manualmente");
	}
	ativos[posicao].total_f = (ativos[posicao].qnt_f)*(ativos[posicao].preco_f);
	
	g_print("float: %.2f ",ativos[posicao].total_f);
	
	gtk_widget_grab_focus(codigo_prod_orc_entry[posicao+1]);
	return 0;
}
