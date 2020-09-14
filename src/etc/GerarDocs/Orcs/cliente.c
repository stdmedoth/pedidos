int gerar_orc_cli(FILE *file, struct _orc *orc)
{
	char query[MAX_QUERY_LEN];
	MYSQL_ROW row;
	MYSQL_RES *res;
	sprintf(query,"select razao,endereco,numrua,bairro,cidade,uf,telefone,celular,email from terceiros where code = %i",orc->infos.cliente);
	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		autologger("Erro na query de codigo no orcamento\n");
		return 1;
	}
	if(!(row = mysql_fetch_row(res)))
	{
		popup(NULL,"Erro ao buscar cliente\n\tPeça suporte");
		autologger((char*)mysql_error(&conectar));
		return 1;
	}

	fprintf(file,"<div id=\"orc-cliente\" align=right>\n");
	if(strlen(row[0])){
		fprintf(file,"<img src=\"%s\" alt=\"\"> Cliente: <span id=\"string-black\">%s</span> \n",IMG_IMP_CLI,row[0]);
		fprintf(file,"<hr>\n");
	}
	if(strlen(row[1])){
		fprintf(file,"<img src=\"%s\" alt=\"\"> Endereco: <span id=\"string-black\">%s,%s, %s, %s, %s</span> \n",IMG_IMP_LOCAL,row[1],row[2],row[3],row[4],row[5]);
		fprintf(file,"<hr>\n");
	}

	fprintf(file,"<div style='display: flex'>");

	if(strlen(row[3])){
		fprintf(file,"<div>");
		fprintf(file,"<img src=\"%s\" alt=\"\"> Telefone: <span id=\"string-black\">%s</span> \n",IMG_IMP_TEL,row[6]);
		fprintf(file,"</div>");
	}
	if(strlen(row[4])){
		fprintf(file,"<div class='cli-info-sec-col'>");
		fprintf(file,"<img src=\"%s\" alt=\"\"> Celular: <span id=\"string-black\">%s</span>\n",IMG_IMP_CEL,row[7]);
		fprintf(file,"</div>");
	}

	fprintf(file,"</div>");
	fprintf(file,"<hr>\n");

	if(strlen(row[8])){
		fprintf(file,"<img src=\"%s\" alt=\"\"> Email: <span id=\"string-black\">%s</span> \n",IMG_IMP_EMAIL,row[8]);
		fprintf(file,"<hr>\n");
	}
	fprintf(file,"</div>\n");
	return 0;
}
