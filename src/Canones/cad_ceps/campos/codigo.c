int cad_ceps_code_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  cad_ceps_code_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_ceps_code_entry));
  if(!strlen(cad_ceps_code_gchar)){
    popup(NULL,"Necessário código");
    return 1;
  }

  sprintf(query,"select CEP from logradouro where id_logradouro = %s",cad_ceps_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível carregar cep");
    return 1;
  }
  if((row = mysql_fetch_row(res))){
    gtk_entry_set_text(GTK_ENTRY(cad_ceps_cep_entry),row[0]);
  }

  gtk_widget_grab_focus(cad_ceps_cep_entry);
  return 0;
}
