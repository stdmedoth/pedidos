int orc_srv_transp_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  orc_srv_transp_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_srv_transp_entry));
  if(!strlen(orc_srv_transp_gchar)){
    orc_srv_transp_cancelar_fun();
    return 0;
  }

  sprintf(query,"select * from servico_transporte where code = %i",atoi(orc_srv_transp_gchar));
  if(!(res = consultar(query)))
  {
    popup(NULL,"Erro ao buscar serviço de transporte");
    return 1;
  }
  if((row=mysql_fetch_row(res)))
  {
    gtk_entry_set_text(GTK_ENTRY(orc_srv_transp_entry), row[TRSP_CODE_COL]);
    if(orc_transp_alterar_fun()){
      return 1;
    }
  }
  
  gtk_widget_grab_focus(orc_transp_codigo_entry);

  return 0;
}
