int relat_ter_gerar_fun()
{
	MYSQL_RES *res1,*res2;
	MYSQL_ROW row1,row2;
	char html_header[] = "<!DOCTYPE html><html><head><meta charset=\"utf-8\"/><title>Relatório de Terceiros</title><link href=\"../styles/relatorios.css\" rel=\"stylesheet\"></head>";
	char banner[55+strlen(IMG_IMP_LOGO)];
	char *gerando_file;
	char *tipo_nome;
	sprintf(banner,"<img id=\"logo-img\" src=\"%s\" alt=\"LOGO PETITTO\">",IMG_IMP_LOGO);

	char query[MAX_QUERY_LEN];
	FILE *relatorio_file;
	int cont=0,list_qnt=0;
	gerando_file = malloc(500);

	do{
		sprintf(gerando_file,"%srelat%i.html",TER_RELAT_FILE,cont);
		cont++;
		if(cont>100)
			return 1;
	}
	while(!(relatorio_file = fopen(gerando_file,"w")));

	if(relatorio_file == NULL)
	{
		popup(NULL,"Não foi possivel abrir o arquivo de relatorio");
		return 1;
	}

	sprintf(query,"select b.nome from criador_relat as a inner join relat_tab_campos as b on a.campos = b.code where a.code = %s",relat_ter_codigo_gchar);

	fprintf(relatorio_file,html_header);
	fprintf(relatorio_file,"<body>");
	fprintf(relatorio_file,"<div id=\"div-titulo\">");
	fprintf(relatorio_file,banner);
	fprintf(relatorio_file,"</div>");

	fprintf(relatorio_file,"<div id=\"div-relat\" align=\"center\">");
	fprintf(relatorio_file,"<h1>Relatório de Terceiros</h1>");
	fprintf(relatorio_file,"<div>");
	fprintf(relatorio_file,"<div>Data: %s</div>",data_sys);
	fprintf(relatorio_file,"<div>");
	fprintf(relatorio_file,"<div>Filtros: </div>");
	fprintf(relatorio_file,"<div>Cod Terceiros: de %i à %i</div>",relat_ter_cod_int1_int, relat_ter_cod_int2_int);
	if(relat_ter_tipo_int){
		g_print("valor numerico '%i'\n",relat_ter_tipo_int);
		tipo_nome = tipo_ter_num_to_str(relat_ter_tipo_int);
		if(tipo_nome)
			fprintf(relatorio_file,"<div>Tipo - %s</div>",tipo_nome);
	}
	else
		fprintf(relatorio_file,"<div>Tipo Todos</div>");
	fprintf(relatorio_file,"</div>");
	fprintf(relatorio_file,"</div>");
	fprintf(relatorio_file,"<hr>");

	fprintf(relatorio_file,"<table>");

	if((res1 = consultar(query))==NULL){
		popup(NULL,"Não foi possivel receber nome dos campos do relatorio");
		return 1;
	}

	fprintf(relatorio_file,"<tr>");
	while((row1 = mysql_fetch_row(res1))!=NULL){
		   	fprintf(relatorio_file,"<th>%s</th>",row1[0]);
	}
	fprintf(relatorio_file,"</tr>");

	if((res2 = consultar(relat_ter_query_gchar))==NULL){
		popup(NULL,"Erro ao receber dados do relatorio");
		return 1;
	}

	while((row2 = mysql_fetch_row(res2))!=NULL){
		list_qnt++;
		cont = 0;
		fprintf(relatorio_file,"<tr>");
		while(cont<ter_query.campos_qnt)
		{
			if(row2[cont])
				fprintf(relatorio_file,"<td>%s</td>",row2[cont]);
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
	fclose(relatorio_file);

	escolher_finalizacao(gerando_file);
	return 0;
}
