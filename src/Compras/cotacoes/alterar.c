int cotacao_alterar_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  cotac_alterando = 1;
  if(cotac_code_fun())
    return 1;

  int code_backup = cotacao_new->code;
  gchar *code = malloc(20);
  sprintf(code,"%i",code_backup);

  cotacao_cancelar_fun();
  cotac_alterando = 1;

  gtk_entry_set_text(GTK_ENTRY(cotac_code_entry),code);
  cotacao_new->code = code_backup;

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

  sprintf(query,"SELECT participante FROM cotacoes_participantes WHERE cotacoes_id = %i GROUP BY participante ORDER BY participante",cotacao_new->code);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar itens da cotação");
    return 1;
  }
  while((row = mysql_fetch_row(res))){
    gchar *participante = strdup(row[0]);
    gtk_entry_set_text(GTK_ENTRY(cotac_partc_entry),participante);
    gtk_widget_activate(cotac_partc_entry);
  }
  struct _Terceiros *Participantes = cotac_get_participantes();
  if(!Participantes->qnt){
    popup(NULL,"Não há participantes");
    return 1;
  }
  for(int participantes_pos=0; participantes_pos<Participantes->qnt; participantes_pos++){
    int participante_index = Participantes->terceiro[participantes_pos].index;
    g_print("Alterando com fornecedor %i index %i\n",Participantes->terceiro[participantes_pos].code,participantes_pos);
  }

  sprintf(query,"SELECT * FROM itens_cotacoes WHERE cotacoes_id = %i ORDER BY participante_id",cotacao_new->code);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar itens da cotação");
    return 1;
  }

  while((row = mysql_fetch_row(res))){

    int participante = atoi(row[COTAC_ITM_PARTC_COL]);
    int participante_index = cotac_get_participante_index(participante);
    gchar *id = malloc(20);
    sprintf(id,"%i",participante);
    if(!gtk_combo_box_set_active_id(GTK_COMBO_BOX(cotac_partc_combo),id)){
      popup(NULL,id);
      return 1;
    }

    int pos = contac_get_ult_pos();
    gtk_entry_set_text(GTK_ENTRY(cotac_prod_cod_entry[participante_index][pos]),row[COTAC_ITM_PROD_COL]);
    gtk_widget_activate(cotac_prod_cod_entry[participante_index][pos]);

    gtk_entry_set_text(GTK_ENTRY(cotac_prod_qnt_entry[participante_index][pos]),row[COTAC_ITM_QNT_COL]);
    gtk_widget_activate(cotac_prod_qnt_entry[participante_index][pos]);

    gtk_entry_set_text(GTK_ENTRY(cotac_prod_prc_entry[participante_index][pos]),row[COTAC_ITM_PRC_COL]);
    gtk_widget_activate(cotac_prod_prc_entry[participante_index][pos]);

    cotac_add_item(NULL, participante_index);
    cotac_rec_itens_alter_qnt++;
  }

  if(!cotac_rec_itens_alter_qnt){
    popup(NULL,"Sem itens na cotação");
    return 1;
  }

  return 0;
}
