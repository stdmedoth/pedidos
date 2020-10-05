int cad_conta_fixa_vlr(){
  conta_fix_valor_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(conta_fix_valor_entry));

  if(strlen(conta_fix_valor_gchar)<=0){
    popup(NULL,"O valor deve ser inserido");
    gtk_widget_grab_focus(conta_fix_valor_entry);
    return 1;
  }

  if(critica_real(conta_fix_valor_gchar,conta_fix_valor_entry))
    return 1;

  gtk_widget_grab_focus(conta_fix_concluir_button);

  return 0;
}
