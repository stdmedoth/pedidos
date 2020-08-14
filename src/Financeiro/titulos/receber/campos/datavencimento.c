int cad_rec_datavencimento_fun(){
  cad_rec_datavencimento_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_rec_datavencimento_entry));

  if(!strlen(cad_rec_datavencimento_gchar)){
    popup(NULL,"Insira a data de Vencimento");
    return 1;
  }

  gtk_widget_grab_focus(cad_rec_valor_entry);
  return 0;
}
