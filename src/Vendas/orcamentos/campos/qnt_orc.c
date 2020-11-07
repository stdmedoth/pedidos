int qnt_prod_orc(GtkWidget *widget,int posicao)
{
	qnt_prod_orc_calc = 1;
	qnt_prod_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(qnt_prod_orc_entry[posicao]));

  if(strlen(qnt_prod_orc_gchar)<=0){
    popup(NULL,"A quantidade deve ser inserida");
    gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
    return 1;
  }

  if(critica_real(qnt_prod_orc_gchar,qnt_prod_orc_entry[posicao])!=0){
    gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
    return 1;
  }

	if(calcula_prod_orc(NULL, posicao)){
		return 1;
	}

	gtk_widget_grab_focus(orig_preco_prod_orc_combo[posicao]);
	qnt_prod_orc_calc = 0;
	return 0;
}
