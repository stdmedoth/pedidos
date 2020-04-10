int desconto_prod_orc(GtkWidget *widget,int posicao)
{
	g_print("Analisando campo desconto\n");
	//desconto_prod_orc_gchar = malloc(sizeof(char*)*MAX_PRECO_LEN);
	//desconto_prod_orc_gchar =(gchar*)gtk_entry_get_text(GTK_ENTRY(desconto_prod_orc_entry[posicao]));
	//critica_real(desconto_prod_orc_gchar,desconto_prod_orc_entry[posicao]);
	//ativos[posicao].desconto_f = atof(desconto_prod_orc_gchar);
	//strcpy(ativos[posicao].desconto_c,desconto_prod_orc_gchar);
	//g_print("float desconto %.2f\n",ativos[posicao].desconto_f);	
	g_print("Ok!");
	gtk_widget_grab_focus(total_prod_orc_entry[posicao]);
	return 0;
}
