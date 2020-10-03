int cad_rec_datavencimento_fun(){
  char *formatado;
  cad_rec_datavencimento_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_rec_datavencimento_entry));

  if(!strlen(cad_rec_datavencimento_gchar)){
    popup(NULL,"Insira a data de Vencimento");
    return 1;
  }
  if(!(formatado = formatar_data(cad_rec_datavencimento_gchar))){
    gtk_widget_grab_focus(cad_rec_datavencimento_entry);
    return 1;
  }
  gtk_entry_set_text(GTK_ENTRY(cad_rec_datavencimento_entry),formatado);

  gtk_widget_grab_focus(cad_rec_valor_entry);
  return 0;
}
