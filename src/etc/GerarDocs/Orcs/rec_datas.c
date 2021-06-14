int rec_orc_datas( struct _orc *orc ){
  MYSQL_RES *res;
  MYSQL_ROW row;
  GDateTime  *gdate;
  GTimeZone *timezone;
  char *query = malloc(MAX_QUERY_LEN);
  char *data_gchar = malloc(MAX_DATE_LEN);
  int dia, mes, ano;
  int cont=0;

  strcpy(data_gchar,data_sys);
  if(sscanf(data_gchar, "%d/%d/%d", &dia, &mes, &ano) == EOF)
  {
    popup(NULL,"Não foi possivel ler data");
    g_print("Erro no parser de data: %s\n",strerror(errno));
    return 1;
  }

  if(orc->parcelas.condpag.dia_inicial_flag == 0)
    orc->parcelas.condpag.dia_inicial = dia;

  if(orc->parcelas.condpag.dia_inicial<atoi(dia_sys))
    mes++;

  timezone = g_time_zone_new_identifier(NULL);
  gdate = g_date_time_new(timezone,ano,mes,orc->parcelas.condpag.dia_inicial,0,0,0);

  if(orc->parcelas.condpag.tipo_parc == CONDPAG_DT_LVR){
    sprintf(query,"select posicao,DATE_FORMAT(data_vencimento,'%%d/%%m/%%y'), valor from orc_datas_livres where orcamento = %i",orc->infos.code);
    if(!(res = consultar(query)))
    {
      popup(NULL,"Erro ao buscar datas das parcelas");
      return 1;
    }

    orc->parcelas.condpag.parcelas_qnt = mysql_num_rows(res);

    while((row = mysql_fetch_row(res))){
      int pos = atoi(row[0]);
      orc->parcelas.datas[pos] = malloc(MAX_DATE_LEN);
      strcpy(orc->parcelas.datas[pos],row[1]);
      orc->parcelas.vlrs[pos] = atof(row[2]);
    }

  }else{

    orc->parcelas.total_geral = 0;
    for(int cont=0;cont< orc->parcelas.condpag.parcelas_qnt; cont++){

      if(!g_date_time_format(gdate,"%d/%m/%Y")){
        popup(NULL,"Erro em uma das datas de pagamento");
        return 1;
      }

      if(orc->parcelas.condpag.tipo_parc == CONDPAG_DIAS)
        gdate = g_date_time_add_days(gdate,orc->parcelas.condpag.intervalos);

      if(orc->parcelas.condpag.tipo_parc == CONDPAG_MESES)
        gdate = g_date_time_add_months(gdate,orc->parcelas.condpag.intervalos);

      if(cont==0){
        orc->parcelas.vlrs[cont] = ( orc->valores.valor_prds_liquido / orc->parcelas.condpag.parcelas_qnt ) + orc->valores.valor_frete_liquido;
      }else{
        orc->parcelas.vlrs[cont] = ( orc->valores.valor_prds_liquido / orc->parcelas.condpag.parcelas_qnt );
      }

      if(g_date_time_format(gdate,"%d/%m/%Y")){
        orc->parcelas.datas[cont] = malloc(strlen(g_date_time_format(gdate,"%d/%m/%Y")));
        strcpy(orc->parcelas.datas[cont],g_date_time_format(gdate,"%d/%m/%Y"));
      }

      orc->parcelas.total_geral += orc->parcelas.vlrs[cont];

      if(orc->parcelas.condpag.tipo_parc == CONDPAG_DADATA)
        gdate = g_date_time_add_days(gdate,orc->parcelas.condpag.intervalos);
    }
  }
  return 0;
}
