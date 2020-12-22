int preco_prod_orc(GtkWidget *widget,int posicao)
{
	preco_prod_orc_calc = 1;
	preco_prod_orc_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(preco_prod_orc_entry[posicao]));

	if(strlen(preco_prod_orc_gchar)<=0){
		preco_alterado[posicao] = 0;
		valor_orig[posicao] = 0;
		popup(NULL,"O preco deve ser inserido");
		gtk_widget_grab_focus(preco_prod_orc_entry[posicao]);
		return 1;
	}

	ativos[posicao].preco_f = atof(preco_prod_orc_gchar);
	strcpy(ativos[posicao].preco_c,preco_prod_orc_gchar);
	critica_real(ativos[posicao].preco_c,preco_prod_orc_entry[posicao]);

	if(calcula_prod_orc(NULL, posicao)){
		gtk_widget_grab_focus(preco_prod_orc_entry[posicao]);
		return 1;
	}

	gtk_widget_grab_focus(total_prod_orc_entry[posicao]);
	preco_prod_orc_calc = 0;
	return 0;
}
