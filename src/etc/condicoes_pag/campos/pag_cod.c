int pag_cod_fun(){
  char code[MAX_CODE_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  pag_cod_gchar = (gchar *) gtk_entry_get_text(GTK_ENTRY(pag_cod_entry));
  if(strlen(pag_cod_gchar)<=0){
    sprintf(code,"%i",tasker("pag_cond"));
    gtk_entry_set_text(GTK_ENTRY(pag_cod_entry),code);
    popup(NULL,"O código deve ser inserido");
    return 1;
  }
  sprintf(query,"select * from pag_cond where code = %s",pag_cod_gchar);
  if(pag_concluindo == 0 && pag_alterando == 0){

    if((res = consultar(query) ) == NULL){
      popup(NULL,"Erro ao buscar existencia do código");
      return 1;
    }

    if((row = mysql_fetch_row(res) ) != NULL){
      pag_alterar_fun();
      return 1;
    }
  }



  gtk_widget_grab_focus(pag_nome_entry);
  return 0;
}
