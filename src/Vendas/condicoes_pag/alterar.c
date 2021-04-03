int pag_alterar_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  pag_alterando = 1;

  sprintf(query,"select * from pag_cond where code = %s",pag_cod_gchar);
  if((res = consultar(query) ) == NULL){
    popup(NULL,"Erro ao buscar existencia do código");
    return 1;
  }

  if((row = mysql_fetch_row(res) ) == NULL){
    popup(NULL,"Condição não existente para ser alterada");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(pag_nome_entry),row[PAGCND_NOM_COL]);
  gtk_combo_box_set_active(GTK_COMBO_BOX(pag_tipo_combo),atoi(row[PAGCND_TIP_COL]));
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pag_dia_fixo_check),atoi(row[PAGCND_DIAFLAG_COL]));
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(pag_init_spin),atoi(row[PAGCND_DIA_COL]));
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(pag_parc_spin),atoi(row[PAGCND_INT_COL]));
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(pag_parc_qnt_spin),atoi(row[PAGCOND_QNT_COL]));
  gtk_widget_set_sensitive(pag_cod_entry,FALSE);
  gtk_widget_set_sensitive(pag_alterar_button,FALSE);
  gtk_widget_set_sensitive(pag_psq_cod_button,FALSE);

  return 0;
}
