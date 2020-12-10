int cad_rec_bnc_fun(){

  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;

  cad_rec_bnc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_rec_bnc_entry));

  if(!strlen(cad_rec_bnc_gchar)){
    gchar *cad_rec_bnc_gchar2 = strdup("0");
    cad_rec_bnc_gchar = strdup("0");
    gtk_entry_set_text(GTK_ENTRY(cad_rec_bnc_entry), cad_rec_bnc_gchar2);
  }
  if(atoi(cad_rec_bnc_gchar)!=0){
    sprintf(query,"select nome from bancos where code = %s",cad_rec_bnc_gchar);
    if(!(res = consultar(query))){
      popup(NULL,"Não foi possível consultar Banco");
      return 1;
    }
    if(!(row = mysql_fetch_row(res))){
      popup(NULL,"O Banco não existe");
      return 1;
    }

    gtk_entry_set_text(GTK_ENTRY(cad_rec_bnc_nome_entry),row[0]);
  }else
    gtk_entry_set_text(GTK_ENTRY(cad_rec_bnc_nome_entry),"Sem Banco");
  gtk_widget_grab_focus(cad_rec_cli_entry);
  return 0;
}
