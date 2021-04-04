int concluido_und()
{
	MYSQL_RES *res;
	MYSQL_ROW campo;
	g_print("Iniciando concluido_und()\n");
	char query[MAX_QUERY_LEN];
	char task[MAX_CODE_LEN];

	concluindo_und=1;
	sprintf(task,"%i",tasker("unidades"));

	if(code_und()){
		gtk_widget_grab_focus(code_und_field);
		return 1;
	}

	if(name_und()){
		gtk_widget_grab_focus(name_und_field);
		return 1;
	}

	if(sig_und()){
		gtk_widget_grab_focus(sigla_und_field);
		return 1;
	}

	if(multiplo_und()){
		gtk_widget_grab_focus(mult_und_field);
		return 1;
	}

	if(medida_und()){
		gtk_widget_grab_focus(medida_und_combo_box);
		return 1;
	}

	sprintf(query,"select code from unidades where code = '%s'",codigos_und);
	autologger(query);
	if(!(res = consultar(query))){
		return 1;
	}
	campo = mysql_fetch_row(res);
	if(!campo)
	{
		sprintf(query,"insert into unidades(code,nome,sigla,multiplo,medida) values('%s','%s','%s',%s,%i);",
				codigos_und,
				nomes_und,
				sigla_und,
				mult_und,
				medidas_und);

	}else{

		sprintf(query,"update unidades set nome = '%s', sigla = '%s', multiplo = %s, medida = %i where code = %s",
				nomes_und,
				sigla_und,
				mult_und,
				medidas_und,
				codigos_und);
	}

	if(enviar_query(query)){
		popup(NULL,"O cadastro nao foi feito\nverifique os campos");
		//und_cancelar_fun();
		return 1;
	}

	autologger(query);
	printf("Query envida com sucesso\n");
	popup(NULL,"Concluido");
	und_cancelar_fun();
	return 0;
}
