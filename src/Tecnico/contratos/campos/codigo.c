int cntrats_code_fun(){

  cntrats_code_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cntrats_code_entry));
  if(!strlen(cntrats_code_gchar)){
    popup(NULL,"Insira o código do contrato");
    return 1;
  }

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  sprintf(query, "SELECT * FROM contratos WHERE code = %s", cntrats_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL, "Não foi possível buscar contrato");
    return 1;
  }

  if((row = mysql_fetch_row(res))){
    if(!cntrats_alterando && !cntrats_concluindo){
      cntrats_alterar_fun();
      return 0;
    }
  }

  gtk_widget_grab_focus(cntrats_vencimento_entry);
  return 0;
}
