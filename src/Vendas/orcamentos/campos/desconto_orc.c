int desconto_prod_orc(GtkWidget *widget,int posicao)
{
	g_print("Analisando campo desconto\n");
	desconto_prod_orc_gchar = malloc(sizeof(char*)*MAX_PRECO_LEN);
	desconto_prod_orc_gchar =(gchar*)gtk_entry_get_text(GTK_ENTRY(desconto_prod_orc_entry[posicao]));
	critica_real(desconto_prod_orc_gchar,desconto_prod_orc_entry[posicao]);
	
	ativos[posicao].desconto_f = atof(desconto_prod_orc_gchar);
	strcpy(ativos[posicao].desconto_c,desconto_prod_orc_gchar);
	critica_real(ativos[posicao].desconto_c,desconto_prod_orc_entry[posicao]);
	
	g_print("float desconto %.2f\n",ativos[posicao].desconto_f);	
	g_print("Ok!");		
	
	g_print("Total: ");
	ativos[posicao].total_f = ((ativos[posicao].qnt_f)*(ativos[posicao].preco_f))-ativos[posicao].desconto_f;
	if(ativos[posicao].total_f<0)
	{
		popup(NULL,"Total Negativo, verifique o desconto");
		return 1;
	}
	g_print("float: %.2f ",ativos[posicao].total_f);
	
	sprintf(total_prod_orc_gchar,"%.2f",ativos[posicao].total_f);
	g_print("string: %s \n",total_prod_orc_gchar);
	critica_real(total_prod_orc_gchar,total_prod_orc_entry[posicao]);
	
	strcpy(ativos[posicao].total_c,total_prod_orc_gchar);
	critica_real(ativos[posicao].total_c,total_prod_orc_entry[posicao]);
	
	gerar_total_geral();
	gtk_widget_grab_focus(total_prod_orc_entry[posicao]);
	return 0;
}
