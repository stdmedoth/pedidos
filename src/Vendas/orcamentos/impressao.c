FILE *orc;
int imp_head()
{
	fprintf(orc,"<head>\n");
	fprintf(orc,"<link href=\"%s\" rel=\"stylesheet\">\n",CSS_ORC);
	fprintf(orc,"<title>Orcamento</title>\n");
	fprintf(orc,"<div id=\"div-titulo\">\n");
	fprintf(orc,"<img id=\"logo_img\" src=\"%s\" alt=\"PETITTO\">\n",IMG_IMP_LOGO);
	fprintf(orc,"</div>\n");
	fprintf(orc,"</head>\n");
	return 0;
}

int imp_cli()
{
	char query[MAX_QUERY_LEN];
	MYSQL_ROW row;
	MYSQL_RES *res;
	sprintf(query,"select * from terceiros where code = %s",cliente_orc_gchar);
	res = consultar(query);
	if(res==NULL)
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		g_print("Erro na query de codigo no orcamento\n");
		autologger("Erro na query de codigo no orcamento\n");
		autologger(query);
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
	fprintf(orc,"Cliente: <span id=\"string-black\">%s</span>\n",row[RAZ_ROW_POS]);
	fprintf(orc,"<hr>\n");
	fprintf(orc,"Endereco: <span id=\"string-black\">%s</span>\n",row[END_ROW_POS]);
	fprintf(orc,"<hr>\n");
	fprintf(orc,"Telefone: <span id=\"string-black\">%s</span></td>\n",row[TEL_ROW_POS]);
	fprintf(orc,"<hr>\n");
	fprintf(orc,"Celular: <span id=\"string-black\">%s</span></td>\n",row[CEL_ROW_POS]);
	fprintf(orc,"<hr>\n");
	fprintf(orc,"Email: <span id=\"string-black\">%s</span></td>\n",row[EMAIL_ROW_POS]);
	fprintf(orc,"<hr>\n");
	fprintf(orc,"</div>\n");
	return 0;
}
