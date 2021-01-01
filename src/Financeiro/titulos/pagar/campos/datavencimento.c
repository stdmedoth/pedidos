int cad_pag_datavencimento_fun(){
  char *formatado;

  cad_pag_datavencimento_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_pag_datavencimento_entry));

  if(!(formatado = formatar_data(cad_pag_datavencimento_gchar))){
    gtk_widget_grab_focus(cad_pag_datavencimento_entry);
    return 1;
  }
  cad_pag_datavencimento_gchar = strdup(formatado);
  gtk_entry_set_text(GTK_ENTRY(cad_pag_datavencimento_entry),formatado);

  if(!cad_pag_datacriacao_gchar || !strlen(cad_pag_datacriacao_gchar)){
    if(cad_pag_datacriacao_fun())
      return 1;
  }

  int res = comparar_datas(cad_pag_datacriacao_gchar, cad_pag_datavencimento_gchar);
  if(res==DEFAULT_ERROR_CODE){
    popup(NULL,"Erro ao comparar datas");
    return 1;
  }
  if(res>=1){
    popup(NULL,"Data de criação maior que data de Vencimento");
    return 1;
  }

  gtk_widget_grab_focus(cad_pag_valor_entry);
  return 0;
}
