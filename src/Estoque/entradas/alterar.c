void est_ent_alterar_fun()
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	
	alterando_mov_ent_est=1;
	
	if(est_ent_codigo_fun()!=0)
		return ;

	sprintf(query,"select * from movimento_estoque where code = %s",est_ent_cod_gchar);
	if((estado = consultar(query))==NULL)
		return ;

	if((campo = mysql_fetch_row(estado))==NULL)
	{
		popup(NULL,"O movimento não existe");
		return ;
	}

	gtk_entry_set_text(GTK_ENTRY(est_ent_data_entry),campo[DATA_MOV_EST]);
	gtk_widget_activate(est_ent_data_entry);
	gtk_entry_set_text(GTK_ENTRY(est_ent_client_entry),campo[CLI_MOV_EST]);
	gtk_widget_activate(est_ent_client_entry);
	gtk_entry_set_text(GTK_ENTRY(est_ent_prod_entry),campo[PROD_MOV_EST]);
	gtk_widget_activate(est_ent_prod_entry);
	gtk_entry_set_text(GTK_ENTRY(est_ent_subgrp_entry),campo[SUBGRP_MOV_EST]);
	gtk_widget_activate(est_ent_subgrp_entry);
	gtk_entry_set_text(GTK_ENTRY(est_ent_qnt_entry),campo[ENTS_MOV_EST]);
	gtk_widget_activate(est_ent_qnt_entry);
	if(atoi(campo[PED_MOV_EST])!=0)
		gtk_entry_set_text(GTK_ENTRY(est_ent_ped_entry),campo[PED_MOV_EST]);
	gtk_widget_activate(est_ent_ped_entry);
	gtk_combo_box_set_active(GTK_COMBO_BOX(est_ent_tipo_combo),atoi(campo[TIPO_MOV_EST]));
	gtk_combo_box_set_active(GTK_COMBO_BOX(est_ent_est_combo),atoi(campo[EST_MOV_EST]));
	gtk_widget_set_sensitive(est_ent_altera_button,FALSE);
}
