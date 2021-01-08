int cad_ceps_cep_fun(){

  char query[MAX_QUERY_LEN];
  MYSQL_RES *vetor;
  MYSQL_ROW campos;

  cad_ceps_cep_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_ceps_cep_entry));
  if(!strlen(cad_ceps_cep_gchar)){
    popup(NULL,"Necessário inserir o cep");
    return 1;
  }

  gchar *cep = format_only_num(cad_ceps_cep_gchar);
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_cep_entry), cep);

  if(strlen(cep) != CEP_LEN){
    popup(NULL,"CEP mal estruturado");
    return 1;
  }

  cad_ceps_cep_gchar = strdup(cep);

  sprintf(query,"select l.code, l.descricao, l.tipo, l.id_cidade, c.descricao, l.UF, l.descricao_bairro from logradouro as l inner join cidade as c on l.id_cidade = c.code where CEP = '%s'",cad_ceps_cep_gchar);
  if(!(vetor = consultar(query))){
    popup(NULL,"Erro ao consultar o cep");
    gtk_widget_grab_focus(GTK_WIDGET(cad_ceps_cep_entry));
    return 1;
  }
  if(!(campos = mysql_fetch_row(vetor))){
    gtk_widget_grab_focus(cad_ceps_descr_entry);
    return 0;
  }else{
    if(!cad_ceps_alterando && !cad_ceps_concluindo)
      cad_ceps_alterar_fun();
  }

  gtk_widget_grab_focus(cad_ceps_descr_entry);

  return 0;
}
