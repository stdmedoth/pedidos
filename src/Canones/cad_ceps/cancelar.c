int cad_ceps_cancelar_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN],code_task[MAX_CODE_LEN];

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


  sprintf(query,"select MAX(id_logradouro)+1 from logradouro");
  if(!(res=consultar(query))){
    popup(NULL,"Não foi possivel receber task do logradouro");
    return 1;
  }
  if(!(row = mysql_fetch_row(res)))
      strcpy(code_task,"1");
    else
      strcpy(code_task,row[0]);
      
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_code_entry),code_task);
  return 0;
}