FILE *orc;

int imp_cli()
{
	char query[MAX_QUERY_LEN];
	MYSQL_ROW row;
	MYSQL_RES *res;
	sprintf(query,"select razao,endereco,numrua,telefone,celular,email from terceiros where code = %s",cliente_orc_gchar);
	res = consultar(query);
	if(res==NULL)
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		autologger("Erro na query de codigo no orcamento\n");
		fclose(orc);
		return 1;
	}
	row = mysql_fetch_row(res);
	if(row == NULL)
	{
		popup(NULL,"Erro ao buscar cliente\n\tPeça suporte");
		autologger((char*)mysql_error(&conectar));
		return 1;
	}

	fprintf(orc,"<div id=\"orc-cliente\" align=right>\n");
	if(strlen(row[0])){
		fprintf(orc,"<img src=\"%s\" alt=\"\"> Cliente: <span id=\"string-black\">%s</span> \n",IMG_IMP_CLI,row[0]);
		fprintf(orc,"<hr>\n");
	}
	if(strlen(row[1])){
		fprintf(orc,"<img src=\"%s\" alt=\"\"> Endereco: <span id=\"string-black\">%s,%s</span> \n",IMG_IMP_LOCAL,row[1],row[2]);
		fprintf(orc,"<hr>\n");
	}
	if(strlen(row[3])){
		fprintf(orc,"<img src=\"%s\" alt=\"\"> Telefone: <span id=\"string-black\">%s</span> \n",IMG_IMP_TEL,row[3]);
		fprintf(orc,"<hr>\n");
	}
	if(strlen(row[4])){
		fprintf(orc,"<img src=\"%s\" alt=\"\"> Celular: <span id=\"string-black\">%s</span>\n",IMG_IMP_CEL,row[4]);
		fprintf(orc,"<hr>\n");
	}
	if(strlen(row[5])){
		fprintf(orc,"<img src=\"%s\" alt=\"\"> Email: <span id=\"string-black\">%s</span> \n",IMG_IMP_EMAIL,row[5]);
		fprintf(orc,"<hr>\n");
	}
	fprintf(orc,"</div>\n");
	return 0;
}
