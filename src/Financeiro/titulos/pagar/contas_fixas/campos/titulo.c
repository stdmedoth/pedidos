int cad_conta_fixa_titulo(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  conta_fix_id_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(conta_fix_id_entry));
  if(!conta_fix_id_gchar || strlen(conta_fix_id_gchar)<=0){
    popup(NULL,"Insira o código do título");
    gtk_widget_grab_focus(conta_fix_id_entry);
    return 1;
  }
  sprintf(query,"select * from titulos where code = %s",conta_fix_id_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível buscar títulos");
    gtk_widget_grab_focus(conta_fix_id_entry);
    return 1;
  }
  if((row = mysql_fetch_row(res))){
    if(!conta_fixa_alterando && !conta_fixa_concluindo)
      cad_conta_fixa_alterar();
  }
  gtk_widget_grab_focus(conta_fix_descr_entry);

  return 0;
}
