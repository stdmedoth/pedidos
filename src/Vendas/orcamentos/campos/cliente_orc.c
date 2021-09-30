static int alerta_obs=0;
static gchar *orc_ter_obs_char;

void ter_alert_obs()
{
	GtkWidget *janela,*obs_label,*box,*fixed_fecha,*botao_fecha,*obs_caixa;
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(janela,"caixa_frame");
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
	if(strlen(cliente_orc_gchar)<=0){
		popup(NULL,"O código cliente deve ser inserido");
		gtk_widget_grab_focus(cliente_orc_entry);
		return 1;
	}

	orc_infos.cliente = terceiros_get_simp_terceiro(atoi(cliente_orc_gchar));
	if(!orc_infos.cliente){
		popup(NULL,"Não foi possível buscar informações do terceiro");
		gtk_widget_grab_focus(cliente_orc_entry);
		return 1;
	}

	enum CLIENTE_INFOS{
		RAZAO,
		ENDERECO,
		OBS,
		PRAZO,
		TRANSP_CODE,
		TRANSP_CEP,
		FRETE_PAGO,
		VLR_FRETE_PAGO
	};

	sprintf(query,"select razao, endereco, obs, prazo, transp_code, transp_cep, frete_pago, vlr_frete_pago from terceiros where code = %s", cliente_orc_gchar);

	if(!(vetor = consultar(query))){
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		autologger("Erro na query de cliente no orcamento\n");
		gtk_widget_grab_focus(cliente_orc_entry);
		return 1;
	}

	if(!(campos = mysql_fetch_row(vetor))){
		popup(NULL,"Cliente não existente");
		gtk_widget_grab_focus(cliente_orc_entry);
		return 1;
	}

	if(!orc_transp_frete_pago_mudado){

		if(atoi(campos[FRETE_PAGO])){
			orc_transp_frete_pago_int = 1;
			gchar msg[200];
			orc_transp_frete_pago_vlr = atof(campos[VLR_FRETE_PAGO]);
			sprintf(msg, "Frete gratuito apartir de R$ %.2f (Cadastro Vinculado)", atof(campos[VLR_FRETE_PAGO]));
			gtk_label_set_text(GTK_LABEL(orc_transp_frete_pago_label), msg);
		}else{
			orc_transp_frete_pago_int = 0;
			orc_transp_frete_pago_vlr = 0;
			gchar msg[200];
			sprintf(msg, "Frete pago (Sem Vínculos)");
			gtk_label_set_text(GTK_LABEL(orc_transp_frete_pago_label), msg);
		}

	}

	gtk_entry_set_text(GTK_ENTRY(cliente_orc_name_entry),campos[RAZAO]);
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_end_entry),campos[ENDERECO]);

	strcpy(orc_ter_obs_char,campos[OBS]);

	if(strlen(orc_ter_obs_char)>0 && is_texto(orc_ter_obs_char) &&alerta_obs==0){
		ter_alert_obs();
		alerta_obs = 1;
	}

	if( !alterando_orc && !concluindo_orc ){

		if( campos[PRAZO] && atoi(campos[PRAZO]) && !orc_pag_cond_activated){
			gtk_entry_set_text(GTK_ENTRY(orc_pag_cond_entry),campos[PRAZO]);
			gtk_widget_activate(orc_pag_cond_entry);
		}

		if( !transp_verified ){
			if(orc_com_entrega) {
				if( strlen(campos[TRANSP_CODE]) && atoi(campos[TRANSP_CODE]) ){
					gtk_entry_set_text(GTK_ENTRY(orc_transp_codigo_entry),campos[TRANSP_CODE]);
					gtk_widget_activate(orc_transp_codigo_entry);
				}

				if( strlen(campos[TRANSP_CEP]) ){
					gtk_entry_set_text(GTK_ENTRY(orc_transp_cep_entry),campos[TRANSP_CEP]);
				}
			}
		}

	}

	gtk_widget_grab_focus(orc_pag_cond_entry);
	gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),0);
	return 0;
}
