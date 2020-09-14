int gerar_orc_titulos(FILE *file, struct _orc *orc){

  fprintf(file,"<div id=\"campo-titulos\">\n");
  fprintf(file,"<div id=\"campo-totais\">\n");
  fprintf(file,"<p><b>Totalizações</b></p>\n");
  fprintf(file,"<table>\n");

  fprintf(file,"<tr>\n");
  fprintf(file,"<th id=\"prod-row1\">Parcela</th>\n");
  fprintf(file,"<th id=\"prod-row1\">Vencimento</th>\n");
  fprintf(file,"<th id=\"prod-row1\">Valor</th>\n");
  fprintf(file,"</tr>\n");

  for(int cont=0;cont<orc->parcelas.condpag.parcelas_qnt;cont++){
    fprintf(file,"<tr>\n");
    fprintf(file,"<td>%i</td>",cont+1);
    fprintf(file,"<td>%s</td>",orc->parcelas.datas[cont]);
    fprintf(file,"<td>R$ %.2f</td>\n",orc->parcelas.vlrs[cont]);
    fprintf(file,"</tr>\n");
  }

  fprintf(file,"<tr>\n");
  fprintf(file,"<td></td>");
  fprintf(file,"<td></td>");
  fprintf(file,"<td>Total: R$ %.2f</td>\n",orc->parcelas.total_geral);
  fprintf(file,"</tr>\n");
  fprintf(file,"</table>\n");
  fprintf(file,"</div>\n");

  if(orc->parcelas.banco)
    gerar_orc_bancos(file, orc);

  fprintf(file,"</div>\n");
  return 0;
}
