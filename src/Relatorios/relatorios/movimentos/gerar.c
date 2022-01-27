int relat_mov_gerar_fun()
{
	MYSQL_RES *res1,*res2;
	MYSQL_ROW row1,row2;
	gchar *gerando_file;
	int tipos_colunas[MAX_RELAT_CAMPOS];
	int list_qnt=0;
	char html_header[] = "<!DOCTYPE html>\
		<html>\
			<head>\
				<meta charset=\"utf-8\"/>\
				<title>Relatório de Movimentos de Estoque</title>\
				<link href=\"../styles/relatorios.css\" rel=\"stylesheet\">\
			</head>";

	char banner[55+strlen(IMG_IMP_LOGO)];
	g_print("Iniciando relat_mov_gerar_fun()\n");
	sprintf(banner,"<img id=\"logo-img\" src=\"%s\" alt=\"LOGO\">",IMG_IMP_LOGO);

	char query[MAX_QUERY_LEN];

	FILE *relatorio_file;

	int cont=0;
	gerando_file = malloc(500);

	do{
		sprintf(gerando_file,"%srelat%i.html",MOV_RELAT_FILE,cont);
		cont++;
		if(cont>100)
			return 1;
	}
	while(!(relatorio_file = fopen(gerando_file,"w")));

	if(relatorio_file == NULL)
	{
		popup(NULL,"Não foi possivel abrir o arquivo de relatorio");
		g_print("%s\n",strerror(errno));
		return 1;
	}

	sprintf(query,"select b.nome,b.tipo_dado from criador_relat as a inner join relat_tab_campos as b on a.campos = b.code where a.code = %s",relat_mov_codigo_gchar);

	fprintf(relatorio_file,"%s",html_header);
	fprintf(relatorio_file,"<body>");
	fprintf(relatorio_file,"<div id=\"div-titulo\">");
	fprintf(relatorio_file,"%s",banner);
	fprintf(relatorio_file,"</div>");

	fprintf(relatorio_file,"<div id=\"div-relat\" align=\"center\">");
	fprintf(relatorio_file,"<h1>Movimentos de Estoque</h1>");
	fprintf(relatorio_file,"<table>");

	if((res1 = consultar(query))==NULL){
		popup(NULL,"Não foi possivel receber nome dos campos do relatorio");
		return 1;
	}
	fprintf(relatorio_file,"<tr>");
	cont = 0;
	while((row1 = mysql_fetch_row(res1))!=NULL){
   	fprintf(relatorio_file,"<th>%s</th>",row1[0]);
		tipos_colunas[cont] = atoi(row1[1]);
		g_print("valor tipo coluna row: %i\n",tipos_colunas[cont]);
		cont++;
	}
	fprintf(relatorio_file,"</tr>");
	if(cont==0){
		popup(NULL,"As colunas em movimentos estão vazias");
		return 1;
	}

	if(!(res2 = consultar(relat_mov_query_gchar))){
		popup(NULL,"Erro ao receber dados do relatorio");
		return 1;
	}

	while((row2 = mysql_fetch_row(res2))){
		cont = 0;

		fprintf(relatorio_file,"<tr class='tr-estilo'>");
		list_qnt++;
		while(cont<mov_query.campos_qnt)
		{
			if(tipos_colunas[cont] == 1)//texto
					fprintf(relatorio_file,"<td>%s</td>",row2[cont]);
			else
			if(tipos_colunas[cont] == 2)//inteiro
					fprintf(relatorio_file,"<td>%s</td>",row2[cont]);
			else
			if(tipos_colunas[cont] == 3)//float
					fprintf(relatorio_file,"<td>%.2f</td>",atof(row2[cont]));
			else
			if(tipos_colunas[cont] == 4)//dinheiro
					fprintf(relatorio_file,"<td>R$ %.2f</td>",atof(row2[cont]));
			else
			if(tipos_colunas[cont] == 5)//data
					fprintf(relatorio_file,"<td>%s</td>",row2[cont]);
			else
			{
				g_print("valor tipo coluna: %i\n",tipos_colunas[cont]);
				popup(NULL,"Não foi possivel receber tipo de dados! verifique!");
				fprintf(relatorio_file,"<td>%s</td>",row2[cont]);
			}
			cont++;
		}
		fprintf(relatorio_file,"</tr>");
	}

	if(!list_qnt){
		popup(NULL,"Nenhum listagem gerada");
		return 0;
	}

	fprintf(relatorio_file,"</table>");
	fprintf(relatorio_file,"</div>");
	fprintf(relatorio_file,"</body>");

	if(fclose(relatorio_file))
		return 1;
	g_print("Finalizando relat_mov_gerar_fun()\n");

	if(escolher_finalizacao(gerando_file))
		return 1;

	return 0;
}
