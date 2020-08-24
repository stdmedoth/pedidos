int trsp_cad_cli_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  trsp_cad_clicode_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(trsp_cad_clicode_entry));

  if(!strlen(trsp_cad_clicode_gchar)){
    popup(NULL,"O código do cliente precisa ser inserido");
    return 1;
  }

  sprintf(query,"select razao from terceiros where code = %s",trsp_cad_clicode_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar cliente");
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"O cliente não existe");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(trsp_cad_cli_entry),row[0]);

  gtk_widget_grab_focus(trsp_cad_cepini_entry);
  return 0;
}
