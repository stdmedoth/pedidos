int tipodesc;

int desconto_prod_orc(GtkWidget *widget,int posicao)
{
	ativos[posicao].desconto_f = 0;
	strcpy(ativos[posicao].desconto_c,"");

	desconto_prod_orc_gchar = malloc(MAX_PRECO_LEN);
	desconto_prod_orc_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(desconto_prod_orc_entry[posicao]));

	critica_real(desconto_prod_orc_gchar,desconto_prod_orc_entry[posicao]);

	tipodesc = gtk_combo_box_get_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[posicao]));

	if(tipodesc==0)
	{
		ativos[posicao].tipodesc = 0;
		ativos[posicao].desconto_f = atof(desconto_prod_orc_gchar);
		strcpy(ativos[posicao].desconto_c,desconto_prod_orc_gchar);
		critica_real(ativos[posicao].desconto_c,desconto_prod_orc_entry[posicao]);
	}
	else
	if(tipodesc==1)
	{
		ativos[posicao].tipodesc = 1;
		ativos[posicao].desconto_f = ((ativos[posicao].qnt_f)*(ativos[posicao].preco_f))*(atof(desconto_prod_orc_gchar)/100);
		strcpy(ativos[posicao].desconto_c,desconto_prod_orc_gchar);
		critica_real(ativos[posicao].desconto_c,desconto_prod_orc_entry[posicao]);
	}
	else
	{
		popup(NULL,"Erro para escolher tipo de desconto");
		return 1;
	}

	ativos[posicao].total_f = ((ativos[posicao].qnt_f)*(ativos[posicao].preco_f))-ativos[posicao].desconto_f;
	if(ativos[posicao].total_f<0)
	{
		popup(NULL,"Total Negativo, verifique o tipo de desconto");
		gtk_widget_grab_focus(desconto_prod_orc_entry[posicao]);
		return 1;
	}

	if(total_prod_orc_gchar!=NULL)
	{
		sprintf(total_prod_orc_gchar,"%.2f",ativos[posicao].total_f);
		critica_real(total_prod_orc_gchar,total_prod_orc_entry[posicao]);

		strcpy(ativos[posicao].total_c,total_prod_orc_gchar);
		critica_real(ativos[posicao].total_c,total_prod_orc_entry[posicao]);

		gerar_total_geral();
	}
	gtk_widget_grab_focus(total_prod_orc_entry[posicao]);
	return 0;
}
