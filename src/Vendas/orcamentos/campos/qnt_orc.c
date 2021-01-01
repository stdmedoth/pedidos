int qnt_prod_orc(GtkWidget *widget,int posicao)
{
	if(codigo_prod_orc(NULL,posicao))
		return 1;

	qnt_prod_orc_calc = 1;
	qnt_prod_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(qnt_prod_orc_entry[posicao]));

  if(strlen(qnt_prod_orc_gchar)<=0){
    popup(NULL,"A quantidade deve ser inserida");
    gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
    return 1;
  }

	ativos[posicao].qnt_f = atof(qnt_prod_orc_gchar);
	strcpy(ativos[posicao].qnt_c,qnt_prod_orc_gchar);

  if(critica_real(qnt_prod_orc_gchar,NULL)){
    gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
    return 1;
  }

	if(orc_prod_calc_saldo(posicao)){
		g_print("Erro ao calcular saldo do produto\n");
		gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
		return 1;
	}

	if(calcula_prod_orc(NULL, posicao)){
		g_print("Erro ao receber calculos de valor do produto\n");
		return 1;
	}

	gtk_widget_grab_focus(orig_preco_prod_orc_combo[posicao]);
	qnt_prod_orc_calc = 0;
	return 0;
}
