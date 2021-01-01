void est_said_alterar_fun()
{
	char query[MAX_QUERY_LEN], data_gchar[42];
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	int dia,mes,ano;

	GDateTime  *gdate;
	GTimeZone *timezone;

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

	if(sscanf(campo[DATA_MOV_EST], "%d-%d-%d", &ano, &mes, &dia) == EOF)
  {
    g_print("Erro no parser de data: %s\n",strerror(errno));
    return ;
  }

	timezone = g_time_zone_new(NULL);

	gdate = g_date_time_new(timezone,ano,mes,dia,0,0,0);
	if(!g_date_time_format(gdate,"%d/%m/%Y")){
		popup(NULL,"Data incorreta");
	}

	if(atoi(campo[EST_MOV_EST])){
		gtk_combo_box_set_active_id(GTK_COMBO_BOX(est_said_est_combo),campo[EST_MOV_EST]);
	}
	
	gtk_entry_set_text(GTK_ENTRY(est_said_data_entry),g_date_time_format(gdate,"%d/%m/%Y"));
	gtk_widget_activate(est_said_data_entry);
	gtk_entry_set_text(GTK_ENTRY(est_said_client_entry),campo[CLI_MOV_EST]);
	gtk_widget_activate(est_said_client_entry);
	gtk_entry_set_text(GTK_ENTRY(est_said_prod_entry),campo[PROD_MOV_EST]);
	gtk_widget_activate(est_said_prod_entry);
	gtk_entry_set_text(GTK_ENTRY(est_said_qnt_entry),campo[SAID_MOV_EST]);

	gtk_widget_activate(est_said_qnt_entry);
	if(atoi(campo[PED_MOV_EST])!=0)
		gtk_entry_set_text(GTK_ENTRY(est_said_ped_entry),campo[PED_MOV_EST]);
	gtk_widget_activate(est_said_ped_entry);


	if(atoi(campo[TIPO_MOV_EST])  == VENDA)
		gtk_combo_box_set_active(GTK_COMBO_BOX(est_said_tipo_combo),1);

	if(atoi(campo[TIPO_MOV_EST])  == DEV_COMPRA)
		gtk_combo_box_set_active(GTK_COMBO_BOX(est_said_tipo_combo),2);

	est_said_obs_gchar = strdup(campo[OBS_MOV_EST]);
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(est_said_obs_view));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), est_said_obs_gchar, strlen(est_said_obs_gchar));


	gtk_widget_set_sensitive(est_said_altera_button,FALSE);
	gtk_widget_set_sensitive(est_said_cod_entry,FALSE);
	gtk_widget_set_sensitive(est_said_psqcod_button,FALSE);
}
