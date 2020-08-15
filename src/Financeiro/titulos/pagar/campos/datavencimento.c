int cad_pag_datavencimento_fun(){
  cad_pag_datavencimento_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_pag_datavencimento_entry));

  if(!strlen(cad_pag_datavencimento_gchar)){
    popup(NULL,"Insira a data de Vencimento");
    return 1;
  }

  gtk_widget_grab_focus(cad_pag_valor_entry);
  return 0;
}
