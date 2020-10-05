int cad_conta_fixa_gerar(gchar *filepath){
  int ano_ini=0,mes_ini=0,dia_ini=0;
  int ano_fim=0,mes_fim=0,dia_fim=0;
  int parcs_qnt=0;

  if(sscanf(conta_fix_dtini_gchar, "%d/%d/%d", &dia_ini, &mes_ini, &ano_ini) != 3){
    popup(NULL,"Não foi possivel ler data");
    g_print("Erro no parser de data: %s\n",strerror(errno));
    return 0;
  }
  if(sscanf(conta_fix_dtend_gchar, "%d/%d/%d", &dia_fim, &mes_fim, &ano_fim) != 3){
    popup(NULL,"Não foi possivel ler data");
    g_print("Erro no parser de data: %s\n",strerror(errno));
    return 0;
  }

  GTimeZone *timezone = g_time_zone_new(NULL);

  GDateTime *gdate_ini = g_date_time_new(timezone,ano_ini,mes_ini,dia_ini,0,0,0);
  GDateTime *gdate_int = g_date_time_new(timezone,ano_ini,mes_ini,dia_ini,0,0,0);
  if(!gdate_ini){
    popup(NULL,"Data Inicial incorreta");
    return 0;
  }

  GDateTime *gdate_fim = g_date_time_new(timezone,ano_fim,mes_fim,dia_fim,0,0,0);
  if(!gdate_fim){
    popup(NULL,"Data Final incorreta");
    return 0;
  }

  FILE *arquivo = fopen(filepath,"w");
  if(!arquivo){
    popup(NULL,"Arquivo não pode ser aberto");
    return 0;
  }

  doc_gerar_header(arquivo,"Contas Fixas");

  fprintf(arquivo,"<div>");
  fprintf(arquivo,"<table>");
  fprintf(arquivo,"<tr>");
  fprintf(arquivo,"<td>Posição</td>");
  fprintf(arquivo,"<td>Datas</td>");
  fprintf(arquivo,"<td>Valor</td>");
  fprintf(arquivo,"</tr>");
  while(1){

    fprintf(arquivo,"<tr>");
    fprintf(arquivo,"<td>%i</td>",parcs_qnt);
    fprintf(arquivo,"<td>%s</td>",g_date_time_format(gdate_int,"%d/%m/%Y"));
    fprintf(arquivo,"<td>R$ %.2f</td>",atof(conta_fix_valor_gchar));
    fprintf(arquivo,"</tr>");

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

    parcs_qnt++;
  }
  fprintf(arquivo,"</table>");
  fprintf(arquivo,"</div>");
  fprintf(arquivo,"</html>");
  fclose(arquivo);
  desenhar_pdf(filepath);
  return parcs_qnt;
}
