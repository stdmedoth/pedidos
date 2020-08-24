int cad_bxs_rec_id_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  cad_bxs_rec_code_id_gchar = (gchar* ) gtk_entry_get_text(GTK_ENTRY(cad_bxs_rec_code_id_spin));
  rec_baixas.id = atoi(cad_bxs_rec_code_id_gchar);

  if(!cad_bxs_rec_alterando && !cad_bxs_rec_concluindo){
    sprintf(query,"select * from baixas_titulos where parcelas_id = %i and posicao = %i and id_baixa = %i",
    rec_baixas.titulo_code,
    rec_baixas.parcela,
    rec_baixas.id);

    if(!(res = consultar(query))){
      popup(NULL,"Erro ao consultar existencia da baixa");
      return 1;
    }

    if((row = mysql_fetch_row(res))){
      cad_bxs_rec_alterar_fun();
      return 0;
    }

    gtk_entry_set_text(GTK_ENTRY(cad_bxs_rec_datacriacao_entry),"");
    gtk_entry_set_text(GTK_ENTRY(cad_bxs_rec_valor_entry),"");
  }


  gtk_widget_grab_focus(cad_bxs_rec_datacriacao_entry);
  return 0;
}
