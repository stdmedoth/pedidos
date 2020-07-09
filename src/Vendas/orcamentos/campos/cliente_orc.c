static int alerta_obs=0;
gchar *orc_ter_obs_char;

void ter_alert_obs()
{
		GtkWidget *janela,*obs_label,*box,*fixed_fecha,*botao_fecha,*obs_caixa;
		janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
		gtk_window_set_title(GTK_WINDOW(janela),"Aviso de Observações");
		gtk_window_set_position(GTK_WINDOW(janela),3);
		gtk_widget_set_size_request(janela,200,100);
		fixed_fecha = gtk_fixed_new();
		box = gtk_box_new(1,0);
		obs_caixa = gtk_box_new(0,0);
		obs_label = gtk_label_new(orc_ter_obs_char);
		gtk_widget_set_name(GTK_WIDGET(obs_label),"colunas");
		botao_fecha = gtk_button_new_with_label("Fechar");
		gtk_box_pack_start(GTK_BOX(obs_caixa),obs_label,0,0,20);
		gtk_fixed_put(GTK_FIXED(fixed_fecha),botao_fecha,60,0);

		gtk_box_pack_start(GTK_BOX(box),obs_caixa,0,0,20);
		gtk_box_pack_start(GTK_BOX(box),fixed_fecha,0,00,10);

		gtk_container_add(GTK_CONTAINER(janela),box);
		g_signal_connect(botao_fecha,"clicked",G_CALLBACK(close_window_callback),janela);
		gtk_widget_show_all(janela);
}

int codigo_cli_orc()
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	cliente_orc_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(cliente_orc_entry));
	if(strlen(cliente_orc_gchar)<=0)
	{
		popup(NULL,"O código cliente deve ser inserido");
		gtk_widget_grab_focus(cliente_orc_entry);
		return 1;
	}

	if(stoi(cliente_orc_gchar)==-1)
	{
		popup(NULL,"O código do cliente deve ser numérico");
		gtk_widget_grab_focus(cliente_orc_entry);
		return 1;
	}

	sprintf(query,"select razao,endereco,telefone,obs from terceiros where code = %s",cliente_orc_gchar);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		autologger("Erro na query de cliente no orcamento\n");
		gtk_widget_grab_focus(cliente_orc_entry);
		return 1;
	}

	campos = mysql_fetch_row(vetor);
	if(campos == NULL)
	{
		popup(NULL,"Cliente não existente");
		gtk_widget_grab_focus(cliente_orc_entry);
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(cliente_orc_name_entry),campos[0]);
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_end_entry),campos[1]);
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_tel_entry),campos[2]);

	strcpy(orc_ter_obs_char,campos[3]);

	if(strlen(orc_ter_obs_char)>0&&alerta_obs==0)
	{
		ter_alert_obs();
		alerta_obs = 1;
	}

	if(GTK_IS_WIDGET(codigo_prod_orc_entry[1]))
		gtk_widget_grab_focus(orc_pag_cond_entry);
	return 0;
}
