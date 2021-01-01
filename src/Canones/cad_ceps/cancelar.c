int cad_ceps_cancelar_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  gtk_entry_set_text(GTK_ENTRY(cad_ceps_code_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_cep_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_descr_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_cid_code_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_cid_descr_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_bairro_entry),"");
  gtk_combo_box_set_active(GTK_COMBO_BOX(cad_ceps_uf_combo),0);
  gtk_combo_box_set_active(GTK_COMBO_BOX(cad_ceps_uf_combo),0);
  cad_ceps_alterando=0;
  cad_ceps_concluindo=0;
  cad_ceps_consultando = 0;

  gchar *code_task = malloc(MAX_CODE_LEN);
  sprintf(query,"select MAX(id_logradouro) from logradouro");
  if(!(res=consultar(query))){
    popup(NULL,"Não foi possivel receber task do logradouro");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    strcpy(code_task,"1");
  }
  else{
    if(!row[0]){
      strcpy(code_task,"1");
    }else{
      sprintf(code_task,"%i",atoi(row[0])+1);
    }
  }

  gtk_widget_set_sensitive(cad_cep_consulta_button, TRUE);
  gtk_widget_set_sensitive(cad_cep_altera_button, TRUE);
  gtk_widget_set_sensitive(cad_ceps_cep_entry, TRUE);
  gtk_widget_set_sensitive(psq_cep_button, TRUE);
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_code_entry),code_task);
  return 0;
}
