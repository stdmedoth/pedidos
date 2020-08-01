int relat_orc_prod_gerar_fun()
{
	MYSQL_RES *res1,*res2;
	MYSQL_ROW row1,row2;
	gchar *gerando_file;
	int tipos_colunas[MAX_RELAT_CAMPOS];
	char html_header[] = "<!DOCTYPE html><html><head><meta charset=\"utf-8\"/><title>Relatório de Orçamentos</title><link href=\"../styles/relatorios.css\" rel=\"stylesheet\"></head>";
	char banner[55+strlen(IMG_IMP_LOGO)];
	int cont=0,cod_backup=0;
	char query[MAX_QUERY_LEN];
	FILE *relatorio_file;

	g_print("Iniciando relat_orc_prod_gerar_fun()\n");
	sprintf(banner,"<img id=\"logo-img\" src=\"%s\" alt=\"LOGO PETITTO\">",IMG_IMP_LOGO);
	gerando_file = malloc(500);

	do{

		sprintf(gerando_file,"%srelat%i.html",ORC_PROD_RELAT_FILE,cont);
		cont++;
		if(cont>3){
			popup(NULL,"Não foi possível abrir arquivo");
			return 1;
		}

	}
	while(!(relatorio_file = fopen(gerando_file,"w")));

	if(relatorio_file == NULL)
	{
		popup(NULL,"Não foi possivel abrir o arquivo de relatorio");
		g_print("%s\n",strerror(errno));
		return 1;
	}
	fprintf(relatorio_file,"<div id=\"div-relat\" align=\"center\">");
	fprintf(relatorio_file,"<h1>Orçamentos/Produtos</h1>");
	fprintf(relatorio_file,"<div class=\"legendas\">");
	fprintf(relatorio_file,"<span><b>Data:</b> %s</span><br>",data_sys);
	fprintf(relatorio_file,"<span><b>Intervalo Orçamentos:</b> %i à %i</span><br>",relat_orc_prod_int1_orc_prod_int,relat_orc_prod_int2_orc_prod_int);
	fprintf(relatorio_file,"<span><b>Intervalo Produtos:</b> %i à %i</span><br>",relat_orc_prod_int1_prod_int,relat_orc_prod_int2_prod_int);
	fprintf(relatorio_file,"<span><b>Intervalo Terceiros:</b> %i à %i</span><br>",relat_orc_prod_int1_ter_int,relat_orc_prod_int2_ter_int);
	fprintf(relatorio_file,"</div>");
	fprintf(relatorio_file,"<div class=\"tabela-conteudo\">");
	fprintf(relatorio_file,"<table>");

	sprintf(query,"select b.nome,b.tipo_dado from criador_relat as a inner join relat_tab_campos as b on a.campos = b.code where a.code = %s",relat_orc_prod_codigo_gchar);

	fprintf(relatorio_file,html_header);
	fprintf(relatorio_file,"<body>");
	fprintf(relatorio_file,"<div id=\"div-titulo\">");
	fprintf(relatorio_file,banner);
	fprintf(relatorio_file,"</div>");

	if((res1 = consultar(query))==NULL){
		popup(NULL,"Não foi possivel receber nome dos campos do relatorio");
		return 1;
	}
	fprintf(relatorio_file,"<tr>");
	cont = 1;
	tipos_colunas[0] = 2;
	while((row1 = mysql_fetch_row(res1))!=NULL){
		   	fprintf(relatorio_file,"<th>%s</th>",row1[0]);
				tipos_colunas[cont] = atoi(row1[1]);
				g_print("valor tipo coluna row: %i\n",tipos_colunas[cont]);
				cont++;
	}

	fprintf(relatorio_file,"</tr>");
	if(cont==0){
		popup(NULL,"As colunas em orçamentos estão vazias");
		return 1;
	}

	if((res2 = consultar(relat_orc_prod_query_gchar))==NULL){
		popup(NULL,"Erro ao receber dados do relatorio");
		return 1;
	}

	while((row2 = mysql_fetch_row(res2))!=NULL){
		cont = 1;

		fprintf(relatorio_file,"<tr>");
		//verifica se o código do orçamento na listagem mudou, para criar o header de orcamento código de orçamento
		if(atoi(row2[0])!=cod_backup){
			fprintf(relatorio_file,"<tr>");
			fprintf(relatorio_file,"<td class=\"header-cod-table\"><b>Orçamento Código:</b> %s</td>",row2[0]);
			fprintf(relatorio_file,"<tr>");
		}
		cod_backup = atoi(row2[0]);

		//recebe os campos dos produtos e imprime pelo tipo
		while(cont<=orc_prod_query.campos_qnt)
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

	fprintf(relatorio_file,"</table>");
	fprintf(relatorio_file,"</div>");
	fprintf(relatorio_file,"</body>");
	fprintf(relatorio_file,"</html>");
	if(fclose(relatorio_file)){
		popup(NULL,"O arquivo foi fechado com erro");
		file_logger(strerror(errno));
		autologger(strerror(errno));
	}
	g_print("Finalizando relat_orc_prod_gerar_fun()\n");

	if(escolher_finalizacao(gerando_file))
		return 1;

	return 0;
}
