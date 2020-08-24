int trsp_cad_trspcode_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  trsp_cad_trspcode_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(trsp_cad_trspcode_entry));

  if(!strlen(trsp_cad_trspcode_gchar)){
    popup(NULL,"O código do transportador precisa ser inserido");
    return 1;
  }

  sprintf(query,"select razao from terceiros where code = %s",trsp_cad_trspcode_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar transportador");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"O transportador não existe");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(trsp_cad_trsp_entry),row[0]);

  gtk_widget_grab_focus(trsp_cad_clicode_entry);
  return 0;
}
