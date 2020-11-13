int cotacao_alterar_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  cotac_alterando = 1;

  if(cotac_code_fun())
    return 1;

  sprintf(query,"SELECT *, DATE_FORMAT(data,'%%d/%%m/%%Y'), DATE_FORMAT(validade,'%%d/%%m/%%Y') FROM cotacoes WHERE code = %i",cotacao_new->code);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar cotação");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Cotação não existente");
    return 1;
  }

  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(cotac_descricao_view));
  gtk_text_buffer_set_text(buffer,row[COTAC_DESCR_COL],strlen(row[COTAC_DESCR_COL]));
  gtk_combo_box_set_active(GTK_COMBO_BOX(cotac_status_combo),atoi(row[COTAC_STAT_COL]));
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cotac_publica_check),atoi(row[COTAC_PUB_COL]));
  gtk_entry_set_text(GTK_ENTRY(cotac_data_entry),row[COTAC_DATA_COL+2]);
  gtk_entry_set_text(GTK_ENTRY(cotac_validade_entry),row[COTAC_VAL_COL+2]);

  return 0;
}
