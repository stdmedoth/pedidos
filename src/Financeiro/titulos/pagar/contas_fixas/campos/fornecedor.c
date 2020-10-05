int cad_conta_fixa_fornecedor(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  conta_fix_forn_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(conta_fix_forn_entry));
  if(!conta_fix_forn_gchar || strlen(conta_fix_forn_gchar)<=0){
    popup(NULL,"Insira o código do Fornecedor");
    gtk_widget_grab_focus(conta_fix_forn_entry);
    return 1;
  }
  sprintf(query,"select razao from terceiros where code = %s",conta_fix_forn_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível buscar Fornecedor");
    gtk_widget_grab_focus(conta_fix_forn_entry);
    return 1;
  }
  if((row = mysql_fetch_row(res))){
    gtk_entry_set_text(GTK_ENTRY(conta_fix_nomeforn_entry),row[0]);
  }
  gtk_widget_grab_focus(conta_fix_dtini_entry);

  return 0;
}
