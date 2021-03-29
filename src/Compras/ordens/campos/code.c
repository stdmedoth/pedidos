int ordem_cmp_code_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  ordem_cmp_code_gchar =  (gchar*) gtk_entry_get_text(GTK_ENTRY(ordem_cmp_code_entry));
  if(!strlen(ordem_cmp_code_gchar)){
    popup(NULL,"O código deve ser inserido");
    gtk_widget_grab_focus(ordem_cmp_code_entry);
  }

  sprintf(query, "select * from ordens_compra where code = %s", ordem_cmp_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar existencia da ordem de compra");
    return 1;
  }
  if((row = mysql_fetch_row(res))){
    if(!ordem_cmp_alterando && !ordem_cmp_concluindo){
      ordem_cmp_alterar_fun();
    }
  }

  gtk_widget_grab_focus(ordem_cmp_forncode_entry);
  return 0;
}
