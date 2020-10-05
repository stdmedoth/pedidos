int cad_conta_fixa_dtfinal(){

  gchar *formatado;
  conta_fix_dtend_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(conta_fix_dtend_entry));

  if(!strlen(conta_fix_dtend_gchar)){
    gtk_entry_set_text(GTK_ENTRY(conta_fix_dtend_entry),data_sys);
    conta_fix_dtend_gchar = malloc(strlen(data_sys));
    strcpy(conta_fix_dtend_gchar, data_sys);
  }

  formatado = formatar_data(conta_fix_dtend_gchar);
  if(!formatado){
    gtk_widget_grab_focus(conta_fix_dtend_entry);
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(conta_fix_dtend_entry),formatado);
  gtk_widget_grab_focus(conta_fix_int_entry);

  return 0;
}
