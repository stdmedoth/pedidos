int cad_ceps_alterar_fun(){

  MYSQL_RES *vetor;
  MYSQL_ROW campos;
  char query[MAX_QUERY_LEN];
  int tipo_rua_escolhido=0,uf_escolhido=0;

  cad_ceps_alterando = 1;

  if(cad_ceps_cep_fun())
    return 1;

  sprintf(query,"select l.code, l.descricao, l.tipo, l.id_cidade, c.descricao, l.UF, l.descricao_bairro from logradouro as l inner join cidade as c on l.id_cidade = c.code where CEP = '%s'",cad_ceps_cep_gchar);
  if(!(vetor = consultar(query))){
    popup(NULL,"Erro na query para CEP\n\tConsulte suporte");
    gtk_widget_grab_focus(GTK_WIDGET(cad_ceps_cep_entry));
    return 1;
  }
  if(!(campos = mysql_fetch_row(vetor))){
    popup(NULL,"CEP não existente");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(cad_ceps_code_entry),campos[0]);
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_descr_entry),campos[1]);

  for(int cont=0;cont<=6;cont++){
    if(strcmp(campos[2],tip_logds[cont])==0){
      gtk_combo_box_set_active(GTK_COMBO_BOX(cad_ceps_tipo_combo),cont);
      cad_ceps_tipo_int = cont;
      tipo_rua_escolhido = 1;
      break;
    }
  }
  if(tipo_rua_escolhido==0){
    gtk_combo_box_set_active(GTK_COMBO_BOX(cad_ceps_uf_combo),7);
  }

  if(campos[3])
    gtk_entry_set_text(GTK_ENTRY(cad_ceps_cid_code_entry),campos[3]);

  if(campos[4])
    gtk_entry_set_text(GTK_ENTRY(cad_ceps_cid_descr_entry),campos[4]);

  for(int cont=0;cont<=cad_ceps_uf_qnt;cont++){
    if(strcmp(campos[5],uf_list[cont])==0){
      gtk_combo_box_set_active(GTK_COMBO_BOX(cad_ceps_uf_combo),cont);
      uf_escolhido=1;
      break;
    }
  }
  if(uf_escolhido==0)
    gtk_combo_box_set_active(GTK_COMBO_BOX(cad_ceps_uf_combo),cad_ceps_uf_qnt);

  if(campos[6])
    gtk_entry_set_text(GTK_ENTRY(cad_ceps_bairro_entry),campos[6]);

  gtk_widget_set_sensitive(cad_cep_altera_button, FALSE);
  gtk_widget_set_sensitive(cad_ceps_cep_entry, FALSE);
  gtk_widget_set_sensitive(psq_cep_button, FALSE);
  return 0;
}
