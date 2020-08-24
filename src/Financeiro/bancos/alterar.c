int cad_bancos_alterar_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  cad_bancos_alterando = 1;
  if(cad_bancos_code_fun())
    return 1;

  sprintf(query,"select * from bancos where code = %s",cad_bancos_code_gchar);

  if(!(res = consultar(query))){
    popup(NULL,"Falha ao receber bancos");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"O banco não existe");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(cad_bancos_nome_entry),row[1]);
  gtk_entry_set_text(GTK_ENTRY(cad_bancos_conta_entry),row[2]);
  gtk_combo_box_set_active(GTK_COMBO_BOX(cad_bancos_tipoconta_combo),atoi(row[3]));
  gtk_entry_set_text(GTK_ENTRY(cad_bancos_agencia_entry),row[4]);
  gtk_entry_set_text(GTK_ENTRY(cad_bancos_usuario_entry),row[5]);
  gtk_entry_set_text(GTK_ENTRY(cad_bancos_doc_entry),row[6]);
  gtk_entry_set_text(GTK_ENTRY(cad_bancos_saldoini_entry),row[7]);
  cad_bancos_alterando = 1;
  gtk_widget_grab_focus(cad_bancos_nome_entry);
  return 0;
}
