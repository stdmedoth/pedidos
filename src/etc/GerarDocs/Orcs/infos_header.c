int gerar_orc_infosheader(FILE *file, struct _orc *orc){

  fprintf(file,"<div id=\"orc-infos\" align=left>\n");

	fprintf(file,"<table>\n");

	fprintf(file,"<tr>\n");
	fprintf(file,"<td id=\"info-row1\">Número do Pedido</td>\n");
	//fprintf(filerc,"<td id=\"info-row1\">Cliente:</td>\n");
	fprintf(file,"<td id=\"info-row1\">Data</td>\n");
	fprintf(file,"</tr>\n");

	fprintf(file,"<tr>\n");
	fprintf(file,"<td>%i</td>\n",orc->infos.code);
  int ano, mes, dia;
  if(sscanf(orc->infos.data, "%d-%d-%d", &ano, &mes, &dia) == EOF){
    popup(NULL,"Não foi possivel interpretar data");
    g_print("Erro no parser de data: %s\n",strerror(errno));
    return 1;
  }
  GTimeZone *timezone = g_time_zone_new_identifier(NULL);
  GDateTime  *gdate = g_date_time_new(timezone,ano,mes,dia,0,0,0);
  gchar *formated_date = g_date_time_format(gdate,"%d/%m/%Y");
  if(!formated_date){
    popup(NULL,"Não foi possivel formatar data do orçamento");
    g_print("Erro no parser de data: %s\n",strerror(errno));
    return 1;
  }

	fprintf(file,"<td>%s</td>\n",formated_date);
	fprintf(file,"<tr>\n");

	fprintf(file,"</table>\n");

	fprintf(file,"</div>\n");

  return 0;
}
