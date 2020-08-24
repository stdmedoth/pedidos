int trsp_cad_orc_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  trsp_cad_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(trsp_cad_orc_entry));

  if(!strlen(trsp_cad_orc_gchar)){
    popup(NULL,"Um código para orçamento precisa ser inserido");
    return 1;
  }

  if(!atoi(trsp_cad_orc_gchar)){
    gtk_widget_grab_focus(trsp_cad_vlrfrt_entry);
    return 0;
  }

  sprintf(query,"select code from orcamentos where code = %s",trsp_cad_orc_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar orcamento");
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"O orcamento não existe");
    return 1;
  }

  gtk_widget_grab_focus(trsp_cad_vlrfrt_entry);
  return 0;
}
