int relat_orc_prod_query_fun()
{
	MYSQL_RES *res , *listar_res;
	MYSQL_ROW row, listar_row;
	int campos_qnt=0;
	char ini_query[] = "select ";
	char *end_query;
	char *query = malloc(MAX_QUERY_LEN*3);
	char *campo_query_cp;
	char *tipo_orc_prod_query = malloc(MAX_QUERY_LEN);
	char *filtros_query_gchar = malloc(MAX_QUERY_LEN*2), *filtros_order_by = malloc(MAX_QUERY_LEN);

	struct _relat_query *orc_prod_query = malloc(sizeof(struct _relat_query));
	orc_prod_query->campo_query = malloc( MAX_QUERY_LEN * MAX_RELAT_CAMPOS );

	relat_orc_prod_gerando=1;
	if(relat_orc_prod_codigo_fun()){
		relat_orc_prod_gerando = 0;
		return 1;
	}

  relat_orc_prod_int1_orc_prod_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_orc_prod_int1_orc_prod_entry));
	relat_orc_prod_int2_orc_prod_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_orc_prod_int2_orc_prod_entry));
	relat_orc_prod_int1_ter_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_orc_prod_int1_ter_entry));
	relat_orc_prod_int2_ter_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_orc_prod_int2_ter_entry));
	relat_orc_prod_int1_prod_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_orc_prod_int1_prod_entry));
	relat_orc_prod_int2_prod_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_orc_prod_int2_prod_entry));
	relat_orc_prod_int1_grp_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_orc_prod_int1_grp_entry));
	relat_orc_prod_int2_grp_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_orc_prod_int2_grp_entry));
	relat_orc_prod_tipo_int = gtk_combo_box_get_active(GTK_COMBO_BOX(relat_orc_prod_tipo_combo));
	relat_orc_prod_ordem_int = gtk_combo_box_get_active(GTK_COMBO_BOX(relat_orc_prod_ordem_combo));
	relat_orc_prod_cresc_int = gtk_combo_box_get_active(GTK_COMBO_BOX(relat_orc_prod_cresc_combo));

	if(relat_orc_prod_ordem_int == 0){
		popup(NULL,"Selecione a ordenação");
		gtk_widget_grab_focus(relat_orc_prod_ordem_combo);
		relat_orc_prod_gerando=0;
		return 1;
	}

	if( !relat_orc_prod_ordem_int || !campos_query[relat_orc_prod_ordem_int-1] )
		return 1;

	sprintf(filtros_order_by,"order by %s",campos_query[relat_orc_prod_ordem_int-1]);


	if(relat_orc_prod_tipo_int == 0){
		sprintf(tipo_orc_prod_query," and o.tipo_mov = 0");
	}else{
		sprintf(tipo_orc_prod_query," and o.tipo_mov = %i",relat_orc_prod_tipo_int);
	}

	if(relat_orc_prod_cresc_int==0)
		strcat(filtros_order_by," asc");
	else
	if(relat_orc_prod_cresc_int==1)
		strcat(filtros_order_by," desc");

	sprintf(filtros_query_gchar,"where o.code >= %i and o.code <= %i and o.cliente >= %i and o.cliente <= %i and p_o.produto >= %i and p_o.produto <= %i and p.grupo >= %i and p.grupo <= %i %s %s",
	relat_orc_prod_int1_orc_prod_int, relat_orc_prod_int2_orc_prod_int,
	relat_orc_prod_int1_ter_int, relat_orc_prod_int2_ter_int,
	relat_orc_prod_int1_prod_int, relat_orc_prod_int2_prod_int,
	relat_orc_prod_int1_grp_int, relat_orc_prod_int2_grp_int,
	tipo_orc_prod_query,
	filtros_order_by);

	sprintf(query,"select b.query,t.inner_query from criador_relat as a inner join relat_tab_campos as b inner join relat_tabelas_id as t on a.campos = b.code and a.tabela = t.code where a.code = %s",relat_orc_prod_codigo_gchar);

	if(!(res = consultar(query))){
		popup(NULL,"Não foi possivel receber campos do relatorio");
		return 1;
	}

	while((row = mysql_fetch_row(res))){

		if(campos_qnt==0){
			orc_prod_query->campos = malloc( strlen(row[0]) + 4 );
			sprintf(orc_prod_query->campos,"%s, ",row[0]);
		}
		else{
			orc_prod_query->campos = malloc( strlen(campo_query_cp) + strlen(row[0]) + 4 );
			sprintf(orc_prod_query->campos," %s %s,",campo_query_cp,row[0]);//backup + campo novo
		}

		campo_query_cp = malloc( strlen(orc_prod_query->campos) );
		orc_prod_query->campo_query[campos_qnt] = malloc( strlen(row[0]) );

		strcpy(campo_query_cp, orc_prod_query->campos); //pega backup query
		strcpy(orc_prod_query->campo_query[campos_qnt],row[0]);

		g_print("campo %i: %s\n",campos_qnt, orc_prod_query->campo_query[campos_qnt]);

		end_query = malloc(strlen(row[1]));
		sprintf(end_query,"%s",row[1]);
		campos_qnt++;
	}
	orc_prod_query->campos_qnt = campos_qnt;


	orc_prod_query->campos[strlen(orc_prod_query->campos)-1] = '\0';
	relat_orc_prod_query_gchar = malloc(strlen(ini_query)+strlen(orc_prod_query->campos)+strlen(end_query)+strlen(filtros_query_gchar)+1);

	sprintf(relat_orc_prod_query_gchar,"%s%s%s %s",ini_query,orc_prod_query->campos,end_query,filtros_query_gchar);
	gtk_entry_set_text(GTK_ENTRY(relat_orc_prod_query_entry),relat_orc_prod_query_gchar);
	//relat_orc_prod_gerar_fun();

	relat_orc_prod_grafico_fun();
	relat_orc_prod_gerando = 0;
	return 0;
}
