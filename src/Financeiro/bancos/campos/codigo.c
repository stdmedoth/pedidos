int cad_bancos_code_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  cad_bancos_code_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_bancos_code_entry));

  if( strlen(cad_bancos_code_gchar) <=0 ){
    popup(NULL,"O código deve ser preenchido");
    return 1;
  }
  if(!cad_bancos_alterando && !cad_bancos_concluindo){
    sprintf(query,"select code from bancos where code = %s",cad_bancos_code_gchar);
    if(!(res = consultar(query))){
      popup(NULL,"Não foi possível buscar existencia do banco");
      return 1;
    }
    if((row = mysql_fetch_row(res))){
      cad_bancos_alterar_fun();
      return 0;
    }
  }

  gtk_widget_grab_focus(cad_bancos_nome_entry);
  return 0;
}
