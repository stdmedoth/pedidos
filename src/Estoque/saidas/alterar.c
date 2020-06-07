void est_said_alterar_fun()
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	
	alterando_mov_said_est=1;
	
	if(est_said_codigo_fun()!=0)
		return ;

	sprintf(query,"select * from movimento_estoque where code = %s",est_said_cod_gchar);
	if((estado = consultar(query))==NULL)
		return ;

	if((campo = mysql_fetch_row(estado))==NULL)
	{
		popup(NULL,"O movimento não existe");
		return ;
	}

	gtk_entry_set_text(GTK_ENTRY(est_said_data_entry),campo[DATA_MOV_EST]);
	gtk_widget_activate(est_said_data_entry);
	gtk_entry_set_text(GTK_ENTRY(est_said_client_entry),campo[CLI_MOV_EST]);
	gtk_widget_activate(est_said_client_entry);
	gtk_entry_set_text(GTK_ENTRY(est_said_prod_entry),campo[PROD_MOV_EST]);
	gtk_widget_activate(est_said_prod_entry);
	gtk_entry_set_text(GTK_ENTRY(est_said_subgrp_entry),campo[SUBGRP_MOV_EST]);
	gtk_widget_activate(est_said_subgrp_entry);
	gtk_entry_set_text(GTK_ENTRY(est_said_qnt_entry),campo[SAID_MOV_EST]);

	gtk_widget_activate(est_said_qnt_entry);
	if(atoi(campo[PED_MOV_EST])!=0)
		gtk_entry_set_text(GTK_ENTRY(est_said_ped_entry),campo[PED_MOV_EST]);
	gtk_widget_activate(est_said_ped_entry);
	gtk_combo_box_set_active(GTK_COMBO_BOX(est_said_tipo_combo),atoi(campo[TIPO_MOV_EST]));
	gtk_combo_box_set_active(GTK_COMBO_BOX(est_said_est_combo),atoi(campo[EST_MOV_EST]));
	gtk_widget_set_sensitive(est_said_altera_button,FALSE);
}
