int cad_conta_fixa_concluir(){

  if(cad_conta_fixa_descr()){
    return 1;
  }
  if(cad_conta_fixa_dtinicial()){
    return 1;
  }
  if(cad_conta_fixa_dtinicial()){
    return 1;
  }
  if(cad_conta_fixa_intervalo()){
    return 1;
  }
  if(cad_conta_fixa_tipo()){
    return 1;
  }
  if(cad_conta_fixa_vlr()){
    return 1;
  }
  int ano_ini=0,mes_ini=0,dia_ini=0;
  int ano_fim=0,mes_fim=0,dia_fim=0;
  int parcs_qnt=0;
  int parcelas_ger_qnt=0;
  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;

  if(!(parcelas_ger_qnt = cad_conta_fixa_gerar(PAG_CONT_FIX))){
    popup(NULL,"Nenhum título foi criado");
    return 1;
  }
  if( !PopupBinario("Aguarde e confira os títulos antes de confirmar", "Data e Valores corretos", "Erros encontrados, Não prosseguir")){
    popup(NULL,"Nenhum título criado");
    return 1;
  }

  if(sscanf(conta_fix_dtini_gchar, "%d/%d/%d", &dia_ini, &mes_ini, &ano_ini) != 3){
    popup(NULL,"Não foi possivel ler data");
    g_print("Erro no parser de data: %s\n",strerror(errno));
    return 1;
  }
  if(sscanf(conta_fix_dtend_gchar, "%d/%d/%d", &dia_fim, &mes_fim, &ano_fim) != 3){
    popup(NULL,"Não foi possivel ler data");
    g_print("Erro no parser de data: %s\n",strerror(errno));
    return 1;
  }

  GTimeZone *timezone = g_time_zone_new(NULL);

  GDateTime *gdate_ini = g_date_time_new(timezone,ano_ini,mes_ini,dia_ini,0,0,0);
  GDateTime *gdate_int = g_date_time_new(timezone,ano_ini,mes_ini,dia_ini,0,0,0);
  if(!gdate_ini){
    popup(NULL,"Data Inicial incorreta");
    return 1;
  }

  GDateTime *gdate_fim = g_date_time_new(timezone,ano_fim,mes_fim,dia_fim,0,0,0);
  if(!gdate_fim){
    popup(NULL,"Data Final incorreta");
    return 1;
  }

  sprintf(query,"insert into titulos(code,cliente,pedido,status, qnt_parcelas, tipo_titulo) values(%i,%i,0,%i,%i,%i)",
  atoi(conta_fix_id_gchar),
  atoi(conta_fix_forn_gchar),
  parcelas_ger_qnt-1,
  STAT_PENDENTE,
  TP_TIT_PAG);

  if(enviar_query(query)){
    popup(NULL,"Não foi possível criar Título");
    return 1;
  }

  sprintf(query,"select * from titulos where code = %i", atoi(conta_fix_id_gchar));
  if(!(res=consultar(query))){
    popup(NULL,"Erro ao confirmar existencia do título");
    return 1;
  }
  if(!(row=mysql_fetch_row(res))){
    popup(NULL,"Título base não existente");
    return 1;
  }

  while(1){

    if(conta_fix_tipo_int == CONTA_FIXA_DIAS)
      gdate_int = g_date_time_add_days(gdate_int,conta_fix_int_int);
    else
    if(conta_fix_tipo_int == CONTA_FIXA_MES)
      gdate_int = g_date_time_add_days(gdate_int,conta_fix_int_int);
    else{
      popup(NULL,"Não foi possível identificar tipo de intervalo");
      return 1;
    }

    if(g_date_time_compare(gdate_int, gdate_fim) >= 0){
      break;
    }

    sprintf(query,"insert into parcelas_tab(parcelas_id, posicao, data_criacao, data_vencimento, valor) values(%i, %i, STR_TO_DATE('%s','%%d/%%m/%%Y'), STR_TO_DATE('%s','%%d/%%m/%%Y'), '%s')",
    atoi(conta_fix_id_gchar),
    parcs_qnt,
    conta_fix_dtini_gchar,
    g_date_time_format(gdate_int,"%d/%m/%Y"),
    conta_fix_valor_gchar);

    if(enviar_query(query)){
      popup(NULL,"Erro ao inserir parcela");
      return 1;
    }

    parcs_qnt++;
  }
  popup(NULL,"Processo concluído");

  return 0;
}
