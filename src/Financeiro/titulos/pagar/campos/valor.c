int cad_pag_valor_fun(){

  char valor[MAX_PRECO_LEN];
  cad_pag_valor_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_pag_valor_entry));
  if(!strlen(cad_pag_valor_gchar)){
    popup(NULL,"Insira o valor da parcela");
    return 1;
  }
  sprintf(valor,"%.2f",atof(cad_pag_valor_gchar));
  gtk_entry_set_text(GTK_ENTRY(cad_pag_valor_entry),valor);


  gtk_widget_grab_focus(cad_pag_concluir_button);
  return 0;
}
