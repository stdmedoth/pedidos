int total_prod_orc(GtkWidget *widget,int posicao)
{
	total_prod_orc_gchar = malloc(MAX_PRECO_LEN);
	ativos[posicao].total_f = 0;
	total_prod_orc_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(total_prod_orc_entry[posicao]));
	
	if(strlen(total_prod_orc_gchar)<=0)
	{
		popup(NULL,"O valor total deve ser inserido,\n\tDeixe o sistema inserir, ou insira manualmente");
	}
	ativos[posicao].total_f = (ativos[posicao].qnt_f)*(ativos[posicao].preco_f)-(ativos[posicao].desconto_f);
	sprintf(total_prod_orc_gchar,"%.2f",ativos[posicao].total_f);
	
	if(ativos[posicao].total_f < 0)
	{
		popup(NULL,"Total com valor incorreto,\n\tVerifique o desconto");
		return 1;
	}
	
	g_print("float: %.2f\n",ativos[posicao].total_f);
	g_print("char:  %s\n",total_prod_orc_gchar);
	critica_real(total_prod_orc_gchar,total_prod_orc_entry[posicao]);
	strcpy(ativos[posicao].total_c,total_prod_orc_gchar);
	gerar_total_geral();

	if(ativos[posicao+1].id == 1)
	{
		if(GTK_IS_WIDGET(codigo_prod_orc_entry[posicao+1]))
			gtk_widget_grab_focus(codigo_prod_orc_entry[posicao+1]);
		else
			gtk_widget_grab_focus(botao_orc_mais);
	}
	else
		gtk_widget_grab_focus(botao_orc_mais);
	return 0;
}
