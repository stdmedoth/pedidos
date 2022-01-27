int relat_prod_gerar_fun(struct _relat_query *prod_query)
{
	MYSQL_RES *res1,*res2;
	MYSQL_ROW row1,row2;
	char *gerando_file = malloc(strlen(PROD_RELAT_FILE) + 100);
	int *tipos_colunas = NULL, list_qnt=0;
	int num_rows;
	relat_prod_gerando=1;
	char html_header[] = "<!DOCTYPE html>"
		"<html>"
			"<head>"
				"<meta charset=\"utf-8\"/>"
				"<title>Relatório de Produtos</title>"
				"<link href=\"../styles/relatorios.css\" rel=\"stylesheet\">"
			"</head>";

	char *banner = malloc(strlen(IMG_IMP_LOGO) + 100);

	sprintf(banner,"<img id=\"logo-img\" src=\"%s\" alt=\"LOGO PEDIDOS\">",IMG_IMP_LOGO);

	char query[MAX_QUERY_LEN];
	FILE *relatorio_file;
	int cont=0,pos=0;

	sprintf(gerando_file, "%sprodutos.html", PROD_RELAT_FILE);
	if( !(relatorio_file = fopen(gerando_file, "w")) ){
		popup(NULL,"Não foi possivel abrir o arquivo de relatorio");
		relat_prod_gerando=0;
		return 1;
	}

	fprintf(relatorio_file,"%s",html_header);
	fprintf(relatorio_file,"<body>");
	fprintf(relatorio_file,"<div id=\"div-titulo\">");
	fprintf(relatorio_file,"%s",banner);
	fprintf(relatorio_file,"</div>");

	fprintf(relatorio_file,"<div id=\"div-relat\" align=\"center\">");
	fprintf(relatorio_file,"<h1>Relatório de Produtos</h1>");
	fprintf(relatorio_file,"<div>Data: %s</div>",data_sys);
	fprintf(relatorio_file,"<div>Filtros: </div>");
	fprintf(relatorio_file,"<table>");

	fprintf(relatorio_file,"<tr>");

	sprintf(query,"select b.nome,b.tipo_dado from criador_relat as a inner join relat_tab_campos as b on a.campos = b.code where a.code = %s",relat_prod_codigo_gchar);

	if( !(res1 = consultar(query)) ){
		popup(NULL,"Não foi possivel receber colunas do relatorio");
		relat_prod_gerando=0;
		return 1;
	}
	num_rows = mysql_num_rows(res1);
	if(!num_rows){
		popup(NULL,"Não há colunas para o relatório");
		relat_prod_gerando=0;
		return 1;
	}

	tipos_colunas = malloc( num_rows * sizeof(int) );
	while((row1 = mysql_fetch_row(res1))){
   	fprintf(relatorio_file,"<th>%s</th>",row1[0]);
		if( cont > num_rows )
			break;

		tipos_colunas[cont] = atoi(row1[1]);
		g_print("valor tipo coluna row: %i\n",tipos_colunas[cont]);
		cont++;
	}

	fprintf(relatorio_file,"</tr>");
	if( !(res2 = consultar(relat_prod_query_gchar)) ){
		popup(NULL,"Erro ao receber dados do relatorio");
		relat_prod_gerando=0;
		return 1;
	}

	while((row2 = mysql_fetch_row(res2))){
		cont = 0;
		fprintf(relatorio_file,"<tr class='tr-estilo'>");
		list_qnt++;
		while(cont < prod_query->campos_qnt){
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
			else{
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
		relat_prod_gerando=0;
		return 0;
	}

	fprintf(relatorio_file,"</table>");
	fprintf(relatorio_file,"</div>");
	fprintf(relatorio_file,"</body>");
	fprintf(relatorio_file,"</html>");

	relat_prod_gerando=0;

	fclose(relatorio_file);

	escolher_finalizacao(gerando_file);

	return 0;
}
