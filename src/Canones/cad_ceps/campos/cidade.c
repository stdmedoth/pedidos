int cad_ceps_cid_code_fun(){

  cad_ceps_cid_code_gchar = (gchar*)  gtk_entry_get_text(GTK_ENTRY(cad_ceps_cid_code_entry));

  MYSQL_RES *vetor;
  MYSQL_ROW campos;
  char query[MAX_QUERY_LEN];

  cad_cid_descr_gchar = malloc(MAX_CID_LEN);
  cad_cid_ibge_gchar = malloc(MAX_CODE_LEN);
  sprintf(query,"select * from cidade where code = '%s'",cad_ceps_cid_code_gchar);
	if(!(vetor = consultar(query))){
		popup(NULL,"Erro na query para cidade\n\tConsulte suporte");
	   gtk_widget_grab_focus(cad_ceps_cid_code_entry);
		return 1;
	}

  if(!(campos = mysql_fetch_row(vetor))){
    cad_cid_descr_gchar = "";
    popup(NULL,"Cidade não existente");
    gtk_widget_grab_focus(cad_ceps_cid_code_entry);
		return 0;
	}

  strcpy(cad_cid_descr_gchar,campos[1]);
  strcpy(cad_cid_ibge_gchar,campos[3]);

	gtk_entry_set_text(GTK_ENTRY(cad_ceps_cid_descr_entry),campos[1]);
  gtk_widget_grab_focus(cad_cep_confirma_button);
  return 0;
}
