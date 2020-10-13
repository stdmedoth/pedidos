int cad_bxs_pag_alterar_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  sprintf(query,"select DATE_FORMAT(data_criacao,'%%d/%%m/%%Y'),valor from baixas_titulos where parcelas_id = %i and posicao = %i and id_baixa = %i",
  pag_baixas.titulo_code,
  pag_baixas.parcela,
  pag_baixas.id);

  cad_bxs_pag_alterando = 1;

  if(!(res = consultar(query))){
    popup(NULL,"Erro ao consultar existencia da baixa");
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"A baixa não existe para ser alterada");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_datacriacao_entry),row[0]);
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_valor_entry),row[1]);


  gtk_widget_set_sensitive(cad_bxs_pag_code_id_spin,FALSE);
  gtk_widget_set_sensitive(cad_bxs_pag_code_button,FALSE);
  gtk_widget_set_sensitive(cad_bxs_pag_parcela_spin,FALSE);
  gtk_widget_set_sensitive(cad_bxs_pag_alterar_button,FALSE);

  gtk_widget_grab_focus(cad_bxs_pag_valor_entry);
  return 0;
}
