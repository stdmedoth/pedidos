int preco_prod_orc(GtkWidget *widget,int posicao)
{
	preco_prod_orc_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(preco_prod_orc_entry[posicao]));
	if(strlen(preco_prod_orc_gchar)<=0&&criticar.preco!=0)
	{	
		popup(NULL,"O preco deve ser inserido");
		gtk_widget_grab_focus(preco_prod_orc_entry[posicao]);
		return 1;
	}
	ativos[posicao].preco_f = atof(preco_prod_orc_gchar);
	g_print("float preco %.2f\n",ativos[posicao].preco_f);
	gtk_widget_grab_focus(orig_preco_prod_orc_entry[posicao]);
	return 0;
}
