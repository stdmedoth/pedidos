int est_sald_subgrp_fun(){
	char query[MAX_QUERY_LEN];
	MYSQL_RES *estado;
	MYSQL_ROW campo;

	char *source,*dest, **familia_char;
	int grupo_len;

	gtk_entry_set_text(GTK_ENTRY(est_sld_prod_entry),"");
	gtk_entry_set_text(GTK_ENTRY(est_sld_data_entry),"");
	gtk_entry_set_text(GTK_ENTRY(est_sld_min_entry),"");

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
	sprintf(query,"select * from grupos where code = %i",atoi(est_sld_subgrp_cod_gchar));
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
	if(calcula_saldo())
		return 0;
	else
		return 1;
}
