int orc_transp_valor_frete(){
  char floating[MAX_PRECO_LEN];
  orc_transp_valor = (gchar*)gtk_entry_get_text(GTK_ENTRY(orc_transp_valor_frete_entry));

  if(!strlen(orc_transp_valor)){
    orc_transp_valor = malloc(MAX_PRECO_LEN);
    strcpy(orc_transp_valor,"0");
  }

  sprintf(floating,"%.2f",atof(orc_transp_valor));
  gtk_entry_set_text(GTK_ENTRY(orc_transp_valor_frete_entry),floating);
  orc_valores.valor_frete = atof(orc_transp_valor);

  if(gerar_total_geral())
    return 1;

  gtk_widget_grab_focus(orc_transp_desconto_frete_entry);
  return 0;
}
