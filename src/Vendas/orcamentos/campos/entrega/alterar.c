int orc_transp_alterar_fun(){
  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;

  codigo_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(codigo_orc_entry));

  sprintf(query,"select * from servico_transporte where orcamento = %i",atoi(codigo_orc_gchar));

  if(!(res = consultar(query)))
	{
		popup(NULL,"Verifique query de transportador com suporte");
		return 1;
	}

	if(!(row= mysql_fetch_row(res)))
	{
      orc_com_entrega = 0;
      return 0;
	}

  orc_transp_codigo = malloc(MAX_CODE_LEN);
  strcpy(orc_transp_codigo,row[1]);

	gtk_entry_set_text(GTK_ENTRY(orc_transp_cep_entry),row[4]);

  sprintf(query,"select * from terceiros where code = %s",orc_transp_codigo);
	res = consultar(query);
	if(res==NULL)
	{
		popup(NULL,"Verifique query de transportador com suporte");
		return 1;
	}
	row = mysql_fetch_row(res);
	if(row==NULL)
	{
		popup(NULL,"Nenhum transportador para o código indicado");
		return 1;
	}
	if(row[RAZ_TER_COL])
		gtk_entry_set_text(GTK_ENTRY(orc_transp_nome_entry),row[RAZ_TER_COL]);

	if(row[DOC_TER_COL])
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cnpj_entry),row[DOC_TER_COL]);

	if(row[IE_TER_COL])
		gtk_entry_set_text(GTK_ENTRY(orc_transp_ie_entry),row[IE_TER_COL]);

	orc_com_entrega = 1;

	gtk_widget_grab_focus(orc_transp_nome_entry);


  return 0;
}
