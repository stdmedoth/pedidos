int trsp_cad_code_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  trsp_cad_code_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(trsp_cad_code_entry));

  if(!strlen(trsp_cad_code_gchar)){
    popup(NULL,"O código do transporte precisa ser inserido");
    return 1;
  }

  if(!trsp_cad_alterando && !trsp_cad_concluindo){

    sprintf(query,"select code  from servico_transporte where code = %s",trsp_cad_code_gchar);
    if(!(res = consultar(query))){
      popup(NULL,"Não foi possível consultar transporte");
      return 1;
    }

    if((row = mysql_fetch_row(res))){
      trsp_cad_alterar_fun();
      return 0;
    }
  }

  gtk_widget_grab_focus(trsp_cad_trspcode_entry);
  return 0;
}
