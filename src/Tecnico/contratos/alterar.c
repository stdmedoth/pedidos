int cntrats_alterar_fun(){
  cntrats_alterando =1;

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  sprintf(query, "SELECT * FROM contratos WHERE code = %s", cntrats_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL, "Não foi possível buscar contrato");
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Contrato não existente");
    return 1;
  }
  int dia=0, ano=0, mes=0;
  gchar *date = strdup(row[CONTRATOS_VENC_COL]);
  if(sscanf(date, "%d-%d-%d", &ano, &mes, &dia) == EOF){
    popup(NULL,"Não foi possivel ler data");
    autologger("Erro no parser de data: %s\n");
		autologger(strerror(errno));
    return 1;
  }
  GTimeZone *timezone = g_time_zone_new_identifier(NULL);
	GDateTime  *gdate = g_date_time_new(timezone,ano,mes,dia,0,0,0);
  gchar *formated_date = g_date_time_format(gdate,"%d/%m/%Y");
  if(!formated_date){
    popup(NULL, "Formato de data não identificado");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(cntrats_code_entry), row[CONTRATOS_CODE_COL]);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_cadastro_check), atoi(row[CONTRATOS_CAD_COL]));
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_compras_check), atoi(row[CONTRATOS_CMP_COL]));
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_faturamento_check), atoi(row[CONTRATOS_FAT_COL]));
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_estoque_check), atoi(row[CONTRATOS_EST_COL]));
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_financeiro_check), atoi(row[CONTRATOS_FIN_COL]));
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_marketing_check), atoi(row[CONTRATOS_MARKT_COL]));
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_relatorios_check), atoi(row[CONTRATOS_REL_COL]));
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_ativo_check), atoi(row[CONTRATOS_ATIVO_COL]));
  gtk_entry_set_text(GTK_ENTRY(cntrats_vencimento_entry), formated_date);

  return 0;
}
