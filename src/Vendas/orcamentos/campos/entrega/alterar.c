int orc_transp_alterar_fun(){
  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;

  orc_srv_transp_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_srv_transp_entry));
  if(!strlen(orc_srv_transp_gchar)){
    popup(NULL,"Código do serviço deve ser inserido");
    return 1;
  }
  sprintf(query,"select * from servico_transporte where code = %i",atoi(orc_srv_transp_gchar));
  if(!(res = consultar(query)))
	{
		popup(NULL,"Não foi possível verificar existencia do transporte");
		return 1;
	}
	if(!(row= mysql_fetch_row(res)))
	{
    popup(NULL,"Serviço de transporte não existente");
    return 1;
	}

  gtk_entry_set_text(GTK_ENTRY(orc_transp_cep_entry),row[TRSP_CEPFIM_COL]);
  gtk_widget_activate(orc_transp_cep_entry);

  gtk_entry_set_text(GTK_ENTRY(orc_transp_codigo_entry), row[TRSP_TRANSP_COL]);
  if(orc_transp_codigo_fun()){
    return 1;
  }
	alterando_transp = 1;
  return 0;
}
