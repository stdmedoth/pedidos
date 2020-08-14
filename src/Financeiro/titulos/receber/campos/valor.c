int cad_rec_valor_fun(){

  char valor[MAX_PRECO_LEN];
  cad_rec_valor_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_rec_valor_entry));
  if(!strlen(cad_rec_valor_gchar)){
    popup(NULL,"Insira o valor da parcela");
    return 1;
  }
  sprintf(valor,"%.2f",atof(cad_rec_valor_gchar));
  gtk_entry_set_text(GTK_ENTRY(cad_rec_valor_entry),valor);

  
  gtk_widget_grab_focus(cad_rec_concluir_button);
  return 0;
}
