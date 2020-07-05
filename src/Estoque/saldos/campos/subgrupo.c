int est_sald_subgrp_fun()
{
	char query[MAX_QUERY_LEN], valor[MAX_PRECO_LEN*2], **familia_char;
	char *source,*dest;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	int grupo_len;

	est_sld_subgrp_cod_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_sld_grp_cod_entry));
	familia_char = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO-1);
	source = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO);
	dest = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO);

	if(strlen(est_sld_subgrp_cod_gchar)<=0)
	{
		popup(NULL,"Insira o código");
		gtk_widget_grab_focus(est_sld_grp_cod_entry);
		return 1;
	}
	sprintf(query,"select * from grupos where code = %s",est_sld_subgrp_cod_gchar);
	if((estado = consultar(query))==NULL)
		return 1;

	if((campo = mysql_fetch_row(estado))==NULL || atoi(campo[0])==1)
	{
		popup(NULL,"O subgrupo não existe");
		return 1;
	}

	est_sld_prod_est_int = gtk_combo_box_get_active(GTK_COMBO_BOX(est_sld_est_combo));

	if((grupo_len = rec_familia_nome(familia_char, atoi(est_sld_subgrp_cod_gchar) ))<=0)
		return 1;

	memset(dest,0x0,strlen(dest));
	memset(source,0x0,strlen(source));

	for(int cont=grupo_len;cont>0;cont--)
	{
		sprintf(dest,"%s %s",source,familia_char[cont]);

		strcpy(source,dest);
	}

	gtk_entry_set_text(GTK_ENTRY(est_sld_grp_nome_entry),dest);
	gtk_entry_set_text(GTK_ENTRY(est_sld_prod_entry),"");

	sprintf(query,"select SUM(entradas) - SUM(saidas) from movimento_estoque where produto = %s and subgrupo = %s and estoque = %i",
	est_sld_prod_cod_gchar,
	est_sld_subgrp_cod_gchar,
	est_sld_prod_est_int);

	if((estado = consultar(query))==NULL)
		return 1;

	if((campo = mysql_fetch_row(estado))==NULL)
	{
		popup(NULL,"O produto está sem saldo no estoque");
		return 1;
	}
	if(campo[0])
	{
		sprintf(valor,"%.3f",atof(campo[0]));
		gtk_entry_set_text(GTK_ENTRY(est_sld_prod_entry),valor);
	}
	else
	{
		popup(NULL,"O produto nunca foi movimentado");
		return 1;
	}

	return 0;
}
