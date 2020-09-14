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
	fprintf(file,"<td>%s</td>\n",orc->infos.data);
	fprintf(file,"<tr>\n");

	fprintf(file,"</table>\n");

	fprintf(file,"</div>\n");

  return 0;
}
