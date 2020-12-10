#include <gtk/gtk.h>
int relat_prod_query_fun()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	int campos_qnt=0;
	char ini_query[] = "select";
	char *query = malloc(MAX_QUERY_LEN*3);
	char *end_query;
	char *campo_query_cp;
	char *filtros_query_gchar = malloc(MAX_QUERY_LEN*2), *filtros_order_by = malloc(MAX_QUERY_LEN);

	gint relat_prod_cod_int1_int, relat_prod_cod_int2_int,
	relat_prod_forn_int1_int, relat_prod_forn_int2_int,
	relat_prod_grp_int1_int, relat_prod_grp_int2_int,
	relat_prod_ordem_int,relat_prod_cresc_int;

	relat_prod_gerando=1;

	if(relat_prod_codigo_fun()!=0)
		return 1;

	relat_prod_cod_int1_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_prod_cod_int1_entry));
	relat_prod_cod_int2_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_prod_cod_int2_entry));

	relat_prod_forn_int1_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_prod_forn_int1_entry));
	relat_prod_forn_int2_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_prod_forn_int2_entry));

	relat_prod_grp_int1_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_prod_grp_int1_entry));
	relat_prod_grp_int2_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(relat_prod_grp_int2_entry));

	relat_prod_ordem_int = gtk_combo_box_get_active(GTK_COMBO_BOX(relat_prod_ordem_combo));
	relat_prod_cresc_int = gtk_combo_box_get_active(GTK_COMBO_BOX(relat_prod_crescente_combo));

	if( relat_prod_ordem_int <= 0 ){
		popup(NULL,"Selecione a ordenação");
		gtk_widget_grab_focus(relat_prod_ordem_combo);
		relat_prod_gerando = 0;
		return 1;
	}

	if( !relat_prod_ordem_int || !campos_query[relat_prod_ordem_int-1] )
		return 1;

	sprintf(filtros_order_by,"order by %s",campos_query[relat_prod_ordem_int-1]);

	if(!relat_prod_cresc_int){
		gchar *copy = strdup(filtros_order_by);
		sprintf(filtros_order_by,"%s asc", copy);
	}
	else
	if(relat_prod_cresc_int){
		gchar *copy = strdup(filtros_order_by);
		sprintf(filtros_order_by,"%s desc",copy);
	}

	sprintf(filtros_query_gchar,"where p.code >= %i and p.code <= %i and p.fornecedor >= %i and p.fornecedor <= %i and p.grupo >= %i and p.grupo <= %i %s",
	relat_prod_cod_int1_int, relat_prod_cod_int2_int, relat_prod_forn_int1_int, relat_prod_forn_int2_int, relat_prod_grp_int1_int, relat_prod_grp_int2_int, filtros_order_by);

	sprintf(query,"select b.query,t.inner_query from criador_relat as a inner join relat_tab_campos as b inner join relat_tabelas_id as t on a.campos = b.code and a.tabela = t.code where a.code = %s",
	relat_prod_codigo_gchar);

	if( !(res = consultar(query)) ){
		popup(NULL,"Não foi possivel receber campos do relatorio");
		relat_prod_gerando = 0;
		return 1;
	}
	campos_qnt=0;
	int qnt = mysql_num_rows(res);
	end_query = malloc(MAX_QUERY_LEN);
	while((row = mysql_fetch_row(res))){

		if( campos_qnt >= MAX_RELAT_CAMPOS ){
			popup(NULL,"Máximo de campos excedido");
			return 1;
		}

		if( !campos_qnt ){
			prod_query.campos = malloc( strlen(row[0]) + 4 );
			sprintf(prod_query.campos,"%s, ",row[0]);
		}else{
			prod_query.campos = malloc( strlen(campo_query_cp) + strlen(row[0]) + 4 );
			sprintf(prod_query.campos," %s %s,", campo_query_cp, row[0] );//backup + campo novo
		}

		campo_query_cp = malloc( strlen(prod_query.campos) );
		prod_query.campo_query[campos_qnt] = malloc( strlen(row[0]) );

		strcpy(campo_query_cp, prod_query.campos); //pega backup query
		strcpy(prod_query.campo_query[campos_qnt], row[0]);

		sprintf(end_query,"%s", row[1] );

		campos_qnt++;
	}

	if(campos_qnt<=0){
		popup(NULL,"Campos de relatorios vazios");
		return 1;
	}

	prod_query.campos_qnt = campos_qnt;

	if( strlen(prod_query.campos) )
		prod_query.campos[ strlen(prod_query.campos)-1 ] = '\0';

	relat_prod_query_gchar = malloc( strlen(ini_query) + strlen(prod_query.campos) + strlen(end_query) + strlen(filtros_query_gchar) + 10);

	sprintf(relat_prod_query_gchar,"%s%s%s %s",ini_query,prod_query.campos,end_query,filtros_query_gchar);
	gtk_entry_set_text(GTK_ENTRY(relat_prod_query_entry), relat_prod_query_gchar);

	relat_prod_gerar_fun();

	relat_prod_gerando = 0;

	return 0;
}
