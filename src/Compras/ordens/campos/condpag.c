int ordem_cmp_condpag_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  ordem_cmp_condpag_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(ordem_cmp_condpag_entry));
  if(!strlen(ordem_cmp_condpag_gchar)){
    popup(NULL,"A Condição de pagamento deve ser inserida");
    gtk_widget_grab_focus(ordem_cmp_condpag_entry);
    return 1;
  }

  sprintf(query, "select * from pag_cond where code = %s", ordem_cmp_condpag_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar existencia da Condição de Pagamento");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL, "Condição de pagamento não existente");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(ordem_cmp_condpagnome_entry), row[PAGCND_NOM_COL]);
  gtk_widget_grab_focus(ordem_cmp_req_treeview);
  return 0;
}
