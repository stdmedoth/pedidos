int cad_rec_valor_fun(){

  char valor[MAX_PRECO_LEN];
  cad_rec_valor_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_rec_valor_entry));
  if(!strlen(cad_rec_valor_gchar)){
    popup(NULL,"Insira o valor da parcela");
    return 1;
  }

  if(critica_real(cad_rec_valor_gchar, cad_rec_valor_entry))
    return 1;


  gtk_widget_grab_focus(cad_rec_concluir_button);
  return 0;
}
