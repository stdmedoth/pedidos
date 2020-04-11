int orig_preco_prod_orc(GtkWidget *widget,int posicao)
{
	orig_preco_prod_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orig_preco_prod_orc_entry[posicao]));
	if(strlen(orig_preco_prod_orc_gchar)<=0)
	{
		popup(NULL,"Origem Preço é desconhecido, Repasse os campos");
		gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
		return 1;
	}
	gtk_widget_grab_focus(desconto_prod_orc_entry[posicao]);
	return 0;
}
