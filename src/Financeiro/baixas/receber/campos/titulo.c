int cad_bxs_rec_tit_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  cad_bxs_rec_code_gchar = (gchar* ) gtk_entry_get_text(GTK_ENTRY(cad_bxs_rec_code_entry));
  if(!strlen(cad_bxs_rec_code_gchar)){
    popup(NULL,"Insira o título");
    return 1;
  }
  sprintf(query,"select t.razao from titulos as tit inner join terceiros as t on tit.cliente = t.code where tit.code = %s and tit.tipo_titulo = %i",cad_bxs_rec_code_gchar,TP_TIT_REC);

  if(!(res = consultar(query))){
    popup(NULL,"Erro ao consultar existencia do título");
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Título não existente");
    return 1;
  }
  rec_baixas.titulo_code = atoi(cad_bxs_rec_code_gchar);

  gtk_entry_set_text(GTK_ENTRY(cad_bxs_rec_cli_nome_entry),row[0]);

  gtk_widget_grab_focus(cad_bxs_rec_parcela_spin);
  return 0;
}
