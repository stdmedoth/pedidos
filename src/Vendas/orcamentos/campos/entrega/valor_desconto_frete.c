int orc_transp_desconto_frete(){
  char floating[MAX_PRECO_LEN];
  orc_transp_desconto = (gchar*)gtk_entry_get_text(GTK_ENTRY(orc_transp_desconto_frete_entry));

  if(!strlen(orc_transp_desconto)){
    orc_transp_desconto = malloc(MAX_PRECO_LEN);
    strcpy(orc_transp_desconto,"0");
  }
  sprintf(floating,"%.2f",atof(orc_transp_desconto));
  gtk_entry_set_text(GTK_ENTRY(orc_transp_desconto_frete_entry),floating);
  orc_valores.desconto_frete = atof(orc_transp_desconto);

  if(gerar_total_geral())
    return 1;

  gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),2);
	gtk_widget_grab_focus(orc_pag_datas_entry);
  return 0;
}
