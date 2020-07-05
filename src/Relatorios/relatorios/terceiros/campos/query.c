int relat_ter_query_fun()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	int campos_qnt=0;
	char ini_query[] = "select";
	char end_query[MAX_QUERY_LEN];
	char query[MAX_QUERY_LEN];
	char campo_query_cp[MAX_QUERY_ELM_LEN];
	char filtros_query_gchar[MAX_QUERY_LEN],filtros_order_by[MAX_QUERY_LEN/2];

	gint relat_ter_cod_int1_int, relat_ter_cod_int2_int,
	relat_ter_tipo_int1_int, relat_ter_tipo_int2_int,
	relat_ter_cep_int1_int, relat_ter_cep_int2_int,
	relat_ter_ordem_int,relat_ter_cresc_int;

	relat_ter_gerando = 1;

	if(relat_ter_codigo_fun()!=0)
		return 1;

	relat_ter_cod_int1_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_ter_cod_int1_entry));
	relat_ter_cod_int2_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_ter_cod_int2_entry));

	relat_ter_tipo_int1_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_ter_tipo_int1_entry));
	relat_ter_tipo_int2_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_ter_tipo_int2_entry));

	relat_ter_cep_int1_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_ter_cep_int1_entry));
	relat_ter_cep_int2_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_ter_cep_int2_entry));

	relat_ter_ordem_int = gtk_combo_box_get_active(GTK_COMBO_BOX(relat_ter_ordem_combo));
	relat_ter_cresc_int = gtk_combo_box_get_active(GTK_COMBO_BOX(relat_ter_crescente_combo));

	if(relat_ter_ordem_int == 0){
		popup(NULL,"Selecione a ordenação");
		gtk_widget_grab_focus(relat_ter_ordem_combo);
		relat_ter_gerando = 0;
		return 1;
	}

	sprintf(filtros_order_by,"order by %s",campos_query[relat_ter_ordem_int-1]);

	if(relat_ter_cresc_int==0)
		strcat(filtros_order_by," asc");
	else
	if(relat_ter_cresc_int==1)
		strcat(filtros_order_by," desc");

	sprintf(filtros_query_gchar,"where t.code >= %i and t.code <= %i and t.tipo >= %i and t.tipo <= %i and t.cep >= %i and t.cep <= %i %s",
	relat_ter_cod_int1_int, relat_ter_cod_int2_int, relat_ter_tipo_int1_int, relat_ter_tipo_int2_int, relat_ter_cep_int1_int, relat_ter_cep_int2_int, filtros_order_by);

	sprintf(query,"select b.query,t.inner_query from criador_relat as a inner join relat_tab_campos as b inner join relat_tabelas_id as t on a.campos = b.code and a.tabela = t.code where a.code = %s",relat_ter_codigo_gchar);

	if((res = consultar(query))==NULL){
		popup(NULL,"Não foi possivel receber campos do relatorio");
		return 1;
	}

	while((row = mysql_fetch_row(res))!=NULL){

		if(campos_qnt==0)
			sprintf(ter_query.campos," %s,",row[0]);
		else
		{
			sprintf(ter_query.campos," %s %s,",campo_query_cp,row[0]);
		}

		strcpy(campo_query_cp,ter_query.campos);

		strcpy(ter_query.campo_query[campos_qnt],row[0]);

		g_print("%s\n",ter_query.campo_query[campos_qnt]);
		sprintf(end_query,"%s",row[1]);
		campos_qnt++;
	}

	ter_query.campos_qnt = campos_qnt;

	ter_query.campos[strlen(ter_query.campos)-1] = '\0';

	relat_ter_query_gchar = malloc(strlen(ini_query)+strlen(ter_query.campos)+strlen(end_query)+1);
	relat_ter_query_gchar = malloc(strlen(ini_query)+strlen(ter_query.campos)+strlen(end_query)+strlen(filtros_query_gchar)+1);

	sprintf(relat_ter_query_gchar,"%s%s%s %s",ini_query,ter_query.campos,end_query,filtros_query_gchar);

	relat_ter_gerar_fun();
	relat_ter_gerando = 0;

	gtk_entry_set_text(GTK_ENTRY(relat_ter_query_entry),relat_ter_query_gchar);
	gtk_widget_set_sensitive(relat_ter_query_entry,TRUE);

	return 0;
}
