int relat_mov_query_fun()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	int campos_qnt=0;
	char ini_query[] = "select";
	char *end_query;
	char query[MAX_QUERY_LEN];
	char campo_query_cp[MAX_ROW_LEN*2];
	char tipo_mov_query[MAX_ROW_LEN];
	char filtros_query_gchar[MAX_ROW_LEN*4];
	char filtros_order_by[MAX_ROW_LEN*2];

	relat_mov_gerando=1;

	if(relat_mov_codigo_fun()!=0)
		return 1;

	gint relat_mov_int1_mov_int, relat_mov_int2_mov_int,
	relat_mov_int1_ter_int, relat_mov_int2_ter_int,
	relat_mov_int1_prod_int, relat_mov_int2_prod_int,
	relat_mov_int1_grp_int, relat_mov_int2_grp_int,
	relat_mov_int1_ped_int, relat_mov_int2_ped_int,
	relat_mov_tipo_int,
	relat_mov_ordem_int,relat_mov_cresc_int;

  relat_mov_int1_mov_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_mov_int1_mov_entry));
	relat_mov_int2_mov_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_mov_int2_mov_entry));
	relat_mov_int1_ter_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_mov_int1_ter_entry));
	relat_mov_int2_ter_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_mov_int2_ter_entry));
	relat_mov_int1_prod_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_mov_int1_prod_entry));
	relat_mov_int2_prod_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_mov_int2_prod_entry));
	relat_mov_int1_grp_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_mov_int1_grp_entry));
	relat_mov_int2_grp_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_mov_int2_grp_entry));
	relat_mov_int1_ped_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_mov_int1_ped_entry));
	relat_mov_int2_ped_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_mov_int2_ped_entry));
	relat_mov_tipo_int = gtk_combo_box_get_active(GTK_COMBO_BOX(relat_mov_tipo_combo));
	relat_mov_ordem_int = gtk_combo_box_get_active(GTK_COMBO_BOX(relat_mov_ordem_combo));
	relat_mov_cresc_int = gtk_combo_box_get_active(GTK_COMBO_BOX(relat_mov_cresc_combo));

	if(relat_mov_ordem_int == 0){
		popup(NULL,"Selecione a ordenação");
		gtk_widget_grab_focus(relat_mov_ordem_combo);
		relat_mov_gerando = 0;
		return 1;
	}

	if(campos_query[relat_mov_ordem_int-1]){
		sprintf(filtros_order_by,"order by %s",campos_query[relat_mov_ordem_int-1]);
	}else{
		popup(NULL,"Não foi possivel encontrar query para ordenação");
	}

	if(relat_mov_tipo_int == 0){
		strcat(tipo_mov_query," and m_e.tipo_mov >= 0");
	}else{
		sprintf(tipo_mov_query," and m_e.tipo_mov = %i",relat_mov_tipo_int-1);
	}

	if(relat_mov_cresc_int==0)
		strcat(filtros_order_by," asc");
	else
	if(relat_mov_cresc_int==1)
		strcat(filtros_order_by," desc");

	sprintf(filtros_query_gchar,"where m_e.code >= %i and m_e.code <= %i and m_e.cliente >= %i and m_e.cliente <= %i and m_e.produto >= %i and m_e.produto <= %i and m_e.pedido >= %i and m_e.pedido <= %i %s %s",
	relat_mov_int1_mov_int, relat_mov_int2_mov_int,
	relat_mov_int1_ter_int, relat_mov_int2_ter_int,
	relat_mov_int1_prod_int, relat_mov_int2_prod_int,
	relat_mov_int1_ped_int, relat_mov_int2_ped_int,
	tipo_mov_query,
	filtros_order_by);

	sprintf(query,"select b.query,t.inner_query from criador_relat as a inner join relat_tab_campos as b inner join relat_tabelas_id as t on a.campos = b.code and a.tabela = t.code where a.code = %s",relat_mov_codigo_gchar);

	if((res = consultar(query))==NULL){
		popup(NULL,"Não foi possivel receber campos do relatorio");
		return 1;
	}

	while((row = mysql_fetch_row(res))!=NULL){

		if(campos_qnt==0)
			sprintf(mov_query.campos,"%s, ",row[0]);
		else
		{
			sprintf(mov_query.campos," %s %s,",campo_query_cp,row[0]);//backup + campo novo
		}

		strcpy(campo_query_cp,mov_query.campos); //pega backup query

		strcpy(mov_query.campo_query[campos_qnt],row[0]);

		g_print("%s\n",mov_query.campo_query[campos_qnt]);

		end_query = malloc(strlen(row[1]));
		sprintf(end_query,"%s",row[1]);

		campos_qnt++;
	}
	mov_query.campos_qnt = campos_qnt;


	mov_query.campos[strlen(mov_query.campos)-1] = '\0';
	relat_mov_query_gchar = malloc(strlen(ini_query)+strlen(mov_query.campos)+strlen(end_query)+strlen(filtros_query_gchar)+1);

	sprintf(relat_mov_query_gchar,"%s%s%s %s",ini_query,mov_query.campos,end_query,filtros_query_gchar);
	gtk_entry_set_text(GTK_ENTRY(relat_mov_query_entry),relat_mov_query_gchar);
	relat_mov_gerar_fun();
	relat_mov_gerando=0;

	return 0;
}
