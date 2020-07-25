

static int ler_personalizacao()
{
	//*usar gtk_toggle_button_get_active aqui
	personalizacao.tema = gtk_combo_box_get_active(GTK_COMBO_BOX(tema_combo_box));
	personalizacao.janela_init = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(janela_init));
	personalizacao.janela_keep_above = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(janela_keep_above));

	orc_params.est_orc_padrao = gtk_spin_button_get_value(GTK_SPIN_BUTTON(est_orc_padrao));

	strcpy(navegadores.navegador_path1,gtk_entry_get_text(GTK_ENTRY(tecn_param_nav_path1_entry)));
	strcpy(navegadores.navegador_path2,gtk_entry_get_text(GTK_ENTRY(tecn_param_nav_path2_entry)));

	strcpy(navegadores.navegador_path1,gtk_entry_get_text(GTK_ENTRY(tecn_param_nav_path1_entry)));
	strcpy(navegadores.navegador_path2,gtk_entry_get_text(GTK_ENTRY(tecn_param_nav_path2_entry)));

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tecn_param_nav_choose1_radio))){
			if(!strlen(navegadores.navegador_path1)){
				popup(NULL,"Navegador padrão não configurado");
				return 1;
			}
			navegadores.navegador_pdr = 1;
	}


	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tecn_param_nav_choose2_radio))){
		if(!strlen(navegadores.navegador_path2)){
			popup(NULL,"Navegador padrão não configurado");
			return 1;
		}

		navegadores.navegador_pdr = 2;
	}

	strcpy(impressoras.imp_path1,gtk_entry_get_text(GTK_ENTRY(tecn_param_imp_path1_entry)));
	strcpy(impressoras.imp_path2,gtk_entry_get_text(GTK_ENTRY(tecn_param_imp_path2_entry)));
	strcpy(impressoras.imp_path3,gtk_entry_get_text(GTK_ENTRY(tecn_param_imp_path3_entry)));
	if(!strlen(impressoras.imp_path1)&&!strlen(impressoras.imp_path2)&&!strlen(impressoras.imp_path3)){
		popup(NULL,"Nenhuma impressora mapeada");
		return 1;
	}


	return 0;
}

static int receber_personalizacao()
{
	MYSQL_RES *res;
	MYSQL_ROW row;

	char *query;
	query = malloc(MAX_QUERY_LEN);
	sprintf(query,"select * from perfil_desktop where code = %i",sessao_oper.code);

	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro ao receber dados para personalizacao do sistema");
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Sem dados para personalizar o sistema");
		return 1;
	}

	personalizacao.tema = atoi(row[2]);
	personalizacao.janela_init = atoi(row[3]);
	personalizacao.janela_keep_above = atoi(row[4]);

	gtk_combo_box_set_active(GTK_COMBO_BOX(tema_combo_box),atoi(row[2]));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(janela_init), atoi(row[3]));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(janela_keep_above),atoi(row[4]));

	sprintf(query,"select * from orc_param");
	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro ao receber parametros de orçamentos");
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Sem dados para parametrizar orçamentos");
		return 1;
	}
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(est_orc_padrao),atoi(row[0]));
	orc_params.est_orc_padrao = atoi(row[0]);

	sprintf(query,"select * from confs where code = %i",sessao_oper.code);

	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro ao receber dados de configuração");
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Sem dados para configurar o sistema");
		return 1;
	}

	strcpy(navegadores.navegador_path1,row[1]);
	gtk_entry_set_text(GTK_ENTRY(tecn_param_nav_path1_entry),row[1]);

	strcpy(navegadores.navegador_path2,row[2]);
	gtk_entry_set_text(GTK_ENTRY(tecn_param_nav_path2_entry),row[2]);

	navegadores.navegador_pdr = atoi(row[3]);
	if(atoi(row[3])==1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tecn_param_nav_choose1_radio),atoi(row[3]));
	if(atoi(row[3])==2)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tecn_param_nav_choose2_radio),atoi(row[3]));

	gtk_entry_set_text(GTK_ENTRY(tecn_param_imp_path1_entry),row[4]);
	strcpy(impressoras.imp_path1,row[4]);

	gtk_entry_set_text(GTK_ENTRY(tecn_param_imp_path2_entry),row[5]);
	strcpy(impressoras.imp_path2,row[5]);

	gtk_entry_set_text(GTK_ENTRY(tecn_param_imp_path3_entry),row[6]);
	strcpy(impressoras.imp_path2,row[6]);

	return 0;
}

int atualizar_personalizacao()
{
	int erro;
	char *query;
	char *navegador_path1,*navegador_path2,*imp_path1,*imp_path2,*imp_path3;

	query = malloc(MAX_QUERY_LEN);

	navegador_path1 = malloc(MAX_PATH_LEN);
	navegador_path2 = malloc(MAX_PATH_LEN);
	imp_path1 = malloc(MAX_PATH_LEN);
	imp_path2 = malloc(MAX_PATH_LEN);
	imp_path3 = malloc(MAX_PATH_LEN);

	if(ler_personalizacao())
		return 1;

	sprintf(query,"update perfil_desktop set janela_init = %i",personalizacao.janela_init);
	if((erro = enviar_query(query))!=0)
	{
		popup(NULL,"Erro ao configurar janela login");
	}
	sprintf(query,"update perfil_desktop set tema = %i,janelas_keep_above = %i where code = %i",personalizacao.tema,personalizacao.janela_keep_above,sessao_oper.code);
	if((erro = enviar_query(query))!=0)
	{
		popup(NULL,"Erro ao enviar dados para personalizacao do sistema");
		return 1;
	}

	mysql_real_escape_string(&conectar,navegador_path1,navegadores.navegador_path1,strlen(navegadores.navegador_path1));
	mysql_real_escape_string(&conectar,navegador_path2,navegadores.navegador_path2,strlen(navegadores.navegador_path2));

	mysql_real_escape_string(&conectar,imp_path1,impressoras.imp_path1,strlen(impressoras.imp_path1));
	mysql_real_escape_string(&conectar,imp_path2,impressoras.imp_path2,strlen(impressoras.imp_path2));
	mysql_real_escape_string(&conectar,imp_path3,impressoras.imp_path3,strlen(impressoras.imp_path3));

	sprintf(query,"update confs set navegador_path1 = '%s',navegador_path2 = '%s', navegador_pdr = %i, imp_path1 = '%s', imp_path2 = '%s', imp_path3 = '%s'  where code = %i",navegador_path1,navegador_path2,navegadores.navegador_pdr,imp_path1,imp_path2,imp_path3,sessao_oper.code);

	if((erro = enviar_query(query))!=0)
	{
		popup(NULL,"Erro ao enviar dados para configuração do sistema");
		return 1;
	}
	sprintf(query,"update orc_param set est_orc_padrao = '%i'",
	orc_params.est_orc_padrao);
	if((erro = enviar_query(query))!=0)
	{
		popup(NULL,"Erro ao enviar dados para configuração do sistema");
		return 1;
	}

	receber_personalizacao();
	return 0;
}

int ler_criticas()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	int cont=0;
	query = malloc(sizeof(char*)*MAX_QUERY_LEN);
	for(cont=0;cont<=orc_critic_campos_qnt;cont++)
	{
		if(cont<=ter_critic_campos_qnt)
			sprintf(query,"select critica from criticas where opcao_nome = 'terceiros' and campo_nome = '%s'",critica_campos[cont]);
		else
			sprintf(query,"select critica from criticas where opcao_nome = 'orcamentos' and campo_nome = '%s'",critica_campos[cont]);

		res = consultar(query);
		if(res!=NULL)
		{
			row = mysql_fetch_row(res);
			if(row!=NULL)
			{
				if(atoi(row[0])==1)
				{
					switch(cont)
					{
						case 0:
							terceiros.criticar.doc = 1;
							break;
						case 1:
							terceiros.criticar.tipodoc = 1;
							break;
						case 2:
							terceiros.criticar.endereco =1;
							break;
						case 3:
							terceiros.criticar.cep = 1;
							break;
						case 4:
							terceiros.criticar.tipo = 1;
							break;
						case 5:
							terceiros.criticar.celular =1;
							break;
						case 6:
							terceiros.criticar.contatoc =1 ;
							break;
						case 7:
							terceiros.criticar.telefone =1 ;
							break;
						case 8:
							terceiros.criticar.contatot =1;
							break;
						case 9:
							terceiros.criticar.email = 1;
							break;
						case 10:
							terceiros.criticar.contatoe = 1;
							break;
						case 11:
							terceiros.criticar.entrega = 1;
							break;
						case 12:
							terceiros.criticar.prazo = 1;
							break;
						case 13:
							terceiros.criticar.vlr_frete_pago = 1;
							break;
						case 14:
							orcamentos.criticar.prod_movimento = 1;
							break;
						case 15:
							orcamentos.criticar.prod_saldo = 1;
							break;
						case 16:
							orcamentos.criticar.prod_saldo_limite = 1;
							break;
						case 17:
								orcamentos.criticar.orc_ped_cancelado = 1;
								break;
					}
					gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(campos_de_critica[cont]),TRUE);
				}
			}
		}
	}
	return 0;
}

int atualizar_criticas()
{
	char *query;
	int cont=0;
	int erro;
	query = malloc(sizeof(char*)*MAX_QUERY_LEN);
	for(cont=0;cont<=orc_critic_campos_qnt;cont++)
	{
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(campos_de_critica[cont]))==TRUE)
		{
			if(cont<=ter_critic_campos_qnt)
				sprintf(query,"update criticas set critica = 1 where opcao_nome = 'terceiros' and campo_nome = '%s'",critica_campos[cont]);
			else
				sprintf(query,"update criticas set critica = 1 where opcao_nome = 'orcamentos' and campo_nome = '%s'",critica_campos[cont]);
			erro = enviar_query(query);
			if(erro != 0)
			{
				popup(NULL,"Erro ao tentar atualizar parametros");
				return 1;
			}
		}
		else
		{
			if(cont<=ter_critic_campos_qnt)
				sprintf(query,"update criticas set critica = 0 where opcao_nome = 'terceiros' and campo_nome = '%s'",critica_campos[cont]);
			else
				sprintf(query,"update criticas set critica = 0 where opcao_nome = 'orcamentos' and campo_nome = '%s'",critica_campos[cont]);
			erro = enviar_query(query);
			if(erro != 0)
			{
				popup(NULL,"Erro ao tentar atualizar parametros");
				return 1;
			}
		}
	}
	if(configurar_parametros()==0)
		return 0;
	else
		return 1;
	return 0 ;
}

int atualizar_paramentros()
{
	if(atualizar_criticas()!=0)
		return 1;
	if(atualizar_personalizacao()!=0)
		return 1;
	popup(NULL,"Parametros Atualizados");
	return 0;
}
int parametrizar()
{
	GtkWidget *janela_parametros;
	GtkWidget *notebook;
	GtkWidget *caixona,*caixa_superior;
	GtkWidget *geral_criticas_frame,*ter_criticas_frame,*prod_criticas_frame,*orc_criticas_frame;
	GtkWidget *geral_criticas_box,*ter_criticas_box,*prod_criticas_box,*orc_criticas_box;
	GtkWidget *personaliza_box,*personaliza_frame;
	GtkWidget *tema_combo_box_fixed;
	GtkWidget *orc_parametros_frame, *orc_parametros_box, *orc_parametros_fixed;
	GtkWidget *est_orc_padrao_frame;
	char *wallpapers_nome[] = {"Grey","Cascate","Vulcon","Maré","Wallpaper 5","Wallpaper 6"};
	GtkWidget **caixa_wallpapers,**image_wallpapers,**label_wallpapers,**event_wallpapers,
	*wallpapers_box,*wallpapers_scroll,*wallpapers_frame;
	GtkWidget *tecn_caminhos_box, *tecn_caminhos_frame, *tecn_caminhos_fixed;
	GtkWidget *geral_box,*terc_box,*prod_box,*orc_box, *gerencial_box, *tecnico_box, *outros_box;
	GtkWidget *tecn_param_nav_path1_frame, *tecn_param_nav_path2_frame, *tecn_param_nav_choose_frame;
	GtkWidget *tecn_param_imp_path1_frame, *tecn_param_imp_path2_frame, *tecn_param_imp_path3_frame;
	GtkWidget *tecn_param_nav_path1_box, *tecn_param_nav_path2_box, *tecn_param_nav_choose_box;
	GtkWidget *tecn_param_imp_path1_box, *tecn_param_imp_path2_box, *tecn_param_imp_path3_box;
	GtkWidget *tecn_param_nav_path1_fchoose, *tecn_param_nav_path2_fchoose, *tecn_param_nav_choose_fchoose;
	GtkWidget *tecn_param_imp_path1_fchoose, *tecn_param_imp_path2_fchoose, *tecn_param_imp_path3_fchoose;
	GtkWidget *tecn_param_scroll, *tecn_param_box;

	GtkWidget *opcoes_box;

	GtkWidget *atualizar_button;
	GtkWidget *atualizar_image;

	int cont;
	int *vet_pos;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	janela_parametros = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(janela_parametros,600,400);
	gtk_window_set_default_size(GTK_WINDOW(janela_parametros),600,400);
	gtk_window_set_title(GTK_WINDOW(janela_parametros),"Parametros");
	gtk_window_set_keep_above(GTK_WINDOW(janela_parametros),TRUE);
	gtk_window_set_position(GTK_WINDOW(janela_parametros),GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_icon_name(GTK_WINDOW(janela_parametros),"preferences-system");

	janelas_gerenciadas.vetor_janelas[REG_PARAM_WIN].reg_id = REG_PARAM_WIN;
	janelas_gerenciadas.vetor_janelas[REG_PARAM_WIN].aberta = 1;
	if(ger_janela_aberta(janela_parametros, &janelas_gerenciadas.vetor_janelas[REG_PARAM_WIN]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_PARAM_WIN].janela_pointer = janela_parametros;

	notebook = gtk_notebook_new();
	vet_pos = malloc(sizeof(int*)*WALLPAPERS_QNT);

	caixa_wallpapers = malloc(sizeof(GtkBox*)*WALLPAPERS_QNT);
	image_wallpapers = malloc(sizeof(GtkImage*)*WALLPAPERS_QNT);
	label_wallpapers = malloc(sizeof(GtkLabel*)*WALLPAPERS_QNT);
	event_wallpapers = malloc(sizeof(GtkEventBox*)*WALLPAPERS_QNT);
	wallpapers_scroll = gtk_scrolled_window_new(NULL,NULL);
	wallpapers_box = gtk_box_new(0,0);

	personaliza_box = gtk_box_new(1,0);
	personaliza_frame = gtk_frame_new("Personalização");
	gtk_frame_set_shadow_type(GTK_FRAME(personaliza_frame),GTK_SHADOW_ETCHED_OUT);
	janela_init = gtk_check_button_new_with_label("Ativar Login?");
	janela_keep_above = gtk_check_button_new_with_label("Janelas pais sobrepoem ?");

	tema_combo_box = gtk_combo_box_text_new();
	tema_combo_box_fixed = gtk_fixed_new();
	gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(tema_combo_box),3);

	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(tema_combo_box),0,"Escolha Tema:");

	cont=1;
	while(cont<temas_qnt)
	{
		gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(tema_combo_box),cont,nomes_temas[cont]);
		cont++;
	}

	gtk_combo_box_set_active(GTK_COMBO_BOX(tema_combo_box),0);
	gtk_fixed_put(GTK_FIXED(tema_combo_box_fixed),tema_combo_box,10,0);

	gtk_box_pack_start(GTK_BOX(personaliza_box),janela_keep_above,0,0,5);
	gtk_box_pack_start(GTK_BOX(personaliza_box),tema_combo_box_fixed,0,0,10);
	gtk_container_add(GTK_CONTAINER(personaliza_frame),personaliza_box);

	for(cont=0;cont<WALLPAPERS_QNT;cont++)
	{
		/*
		 * wallpapers_nome  = char
		 * wallpapers_label = gtk_label
		 */
		image_wallpapers[cont] = gtk_image_new_from_file(desktop_images_vet[cont]);
		label_wallpapers[cont] = gtk_label_new(wallpapers_nome[cont]);
		caixa_wallpapers[cont] = gtk_box_new(1,0);
		event_wallpapers[cont] = gtk_event_box_new();
		gtk_box_pack_start(GTK_BOX(caixa_wallpapers[cont]),image_wallpapers[cont],0,0,10);
		gtk_box_pack_start(GTK_BOX(caixa_wallpapers[cont]),label_wallpapers[cont],0,0,5);
		gtk_container_add(GTK_CONTAINER(event_wallpapers[cont]),caixa_wallpapers[cont]);
		gtk_box_pack_start(GTK_BOX(wallpapers_box),event_wallpapers[cont],0,0,20);
		vet_pos[cont] = cont;
		//gtk_widget_add_events(event_wallpapers[cont],GDK_ALL_EVENTS_MASK);
		#pragma GCC diagnostic ignored "-Wint-conversion"
		g_signal_connect(event_wallpapers[cont],"button-press-event",G_CALLBACK(trocar_desktop),vet_pos[cont]);
		#pragma GCC diagnostic warning "-Wint-conversion"
	}
	gtk_widget_set_size_request(wallpapers_box,600,120);
	gtk_widget_set_size_request(wallpapers_scroll,600,120);

	gtk_container_add(GTK_CONTAINER(wallpapers_scroll),wallpapers_box);

	wallpapers_frame = gtk_frame_new("Imagens da área de Trabalho");
	gtk_frame_set_shadow_type(GTK_FRAME(wallpapers_frame),GTK_SHADOW_ETCHED_OUT);
	gtk_container_add(GTK_CONTAINER(wallpapers_frame),wallpapers_scroll);
	campos_de_critica = malloc(sizeof(GtkCheckButton*)*orc_critic_campos_qnt+1);

	caixona = gtk_box_new(1,0);
	opcoes_box = gtk_box_new(0,0);
	geral_box = gtk_box_new(1,0);
	terc_box = gtk_box_new(1,0);
	prod_box = gtk_box_new(1,0);
	orc_box = gtk_box_new(1,0);
	gerencial_box = gtk_box_new(1,0);
	tecnico_box = gtk_box_new(1,0);
	outros_box = gtk_box_new(1,0);

	tecn_param_nav_choose1_radio = gtk_radio_button_new_with_label(NULL,"Escolher como padrão");
	tecn_param_nav_choose2_radio = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(tecn_param_nav_choose1_radio),"Escolher como padrão");

	tecn_param_nav_path1_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(tecn_param_nav_path1_entry),50);
	tecn_param_nav_path2_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(tecn_param_nav_path2_entry),50);

	tecn_param_imp_path1_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(tecn_param_imp_path1_entry),50);
	tecn_param_imp_path2_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(tecn_param_imp_path2_entry),50);
	tecn_param_imp_path3_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(tecn_param_imp_path3_entry),50);

	tecn_param_nav_path1_frame = gtk_frame_new("navegador 1");
	tecn_param_nav_path2_frame = gtk_frame_new("navegador 2");

	tecn_param_imp_path1_frame = gtk_frame_new("Impressora 1");
	tecn_param_imp_path2_frame = gtk_frame_new("Impressora 2");
	tecn_param_imp_path3_frame = gtk_frame_new("Impressora 3");

	tecn_param_nav_path1_box = gtk_box_new(0,0);
	tecn_param_nav_path2_box = gtk_box_new(0,0);

	tecn_param_imp_path1_box = gtk_box_new(0,0);
	tecn_param_imp_path2_box = gtk_box_new(0,0);
	tecn_param_imp_path3_box = gtk_box_new(0,0);

	tecn_param_nav_path1_fchoose = gtk_file_chooser_button_new("Escolher Impressora 1",GTK_FILE_CHOOSER_ACTION_OPEN);
	tecn_param_nav_path2_fchoose = gtk_file_chooser_button_new("Escolher Impressora 2",GTK_FILE_CHOOSER_ACTION_OPEN);

	tecn_param_imp_path1_fchoose = gtk_file_chooser_button_new("Escolher Nav. 1",GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	tecn_param_imp_path2_fchoose = gtk_file_chooser_button_new("Escolher Nav. 2",GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	tecn_param_imp_path3_fchoose = gtk_file_chooser_button_new("Escolher Nav. 3",GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);

	tecn_param_nav_path1_box = gtk_box_new(0,0);
	tecn_param_nav_path2_box = gtk_box_new(0,0);

	tecn_param_imp_path1_box = gtk_box_new(0,0);
	tecn_param_imp_path2_box = gtk_box_new(0,0);
	tecn_param_imp_path3_box = gtk_box_new(0,0);

	gtk_box_pack_start(GTK_BOX(tecn_param_nav_path1_box),tecn_param_nav_path1_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(tecn_param_nav_path1_box),tecn_param_nav_path1_fchoose,0,0,0);
	gtk_box_pack_start(GTK_BOX(tecn_param_nav_path1_box),tecn_param_nav_choose1_radio,0,0,0);

	gtk_box_pack_start(GTK_BOX(tecn_param_nav_path2_box),tecn_param_nav_path2_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(tecn_param_nav_path2_box),tecn_param_nav_path2_fchoose,0,0,0);
	gtk_box_pack_start(GTK_BOX(tecn_param_nav_path2_box),tecn_param_nav_choose2_radio,0,0,0);

	gtk_box_pack_start(GTK_BOX(tecn_param_imp_path1_box),tecn_param_imp_path1_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(tecn_param_imp_path1_box),tecn_param_imp_path1_fchoose,0,0,0);

	gtk_box_pack_start(GTK_BOX(tecn_param_imp_path2_box),tecn_param_imp_path2_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(tecn_param_imp_path2_box),tecn_param_imp_path2_fchoose,0,0,0);

	gtk_box_pack_start(GTK_BOX(tecn_param_imp_path3_box),tecn_param_imp_path3_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(tecn_param_imp_path3_box),tecn_param_imp_path3_fchoose,0,0,0);

	gtk_container_add(GTK_CONTAINER(tecn_param_nav_path1_frame),tecn_param_nav_path1_box);
	gtk_container_add(GTK_CONTAINER(tecn_param_nav_path2_frame),tecn_param_nav_path2_box);

	gtk_container_add(GTK_CONTAINER(tecn_param_imp_path1_frame),tecn_param_imp_path1_box);
	gtk_container_add(GTK_CONTAINER(tecn_param_imp_path2_frame),tecn_param_imp_path2_box);
	gtk_container_add(GTK_CONTAINER(tecn_param_imp_path3_frame),tecn_param_imp_path3_box);

	g_signal_connect(tecn_param_nav_path1_fchoose,"file-set",G_CALLBACK(get_filename_to_entry),tecn_param_nav_path1_entry);
	g_signal_connect(tecn_param_nav_path2_fchoose,"file-set",G_CALLBACK(get_filename_to_entry),tecn_param_nav_path2_entry);

	g_signal_connect(tecn_param_imp_path1_fchoose,"file-set",G_CALLBACK(get_filename_to_entry),tecn_param_imp_path1_entry);
	g_signal_connect(tecn_param_imp_path2_fchoose,"file-set",G_CALLBACK(get_filename_to_entry),tecn_param_imp_path2_entry);
	g_signal_connect(tecn_param_imp_path3_fchoose,"file-set",G_CALLBACK(get_filename_to_entry),tecn_param_imp_path3_entry);

	tecn_caminhos_box = gtk_box_new(1,0);
	tecn_caminhos_frame = gtk_frame_new("Caminhos");
	tecn_caminhos_fixed = gtk_fixed_new();

	gtk_box_pack_start(GTK_BOX(tecn_caminhos_box),tecn_param_nav_path1_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(tecn_caminhos_box),tecn_param_nav_path2_frame,0,0,5);

	gtk_box_pack_start(GTK_BOX(tecn_caminhos_box),tecn_param_imp_path1_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(tecn_caminhos_box),tecn_param_imp_path2_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(tecn_caminhos_box),tecn_param_imp_path3_frame,0,0,5);

	gtk_container_add(GTK_CONTAINER(tecn_caminhos_frame),tecn_caminhos_box);
	gtk_fixed_put(GTK_FIXED(tecn_caminhos_fixed),tecn_caminhos_frame,20,20);

	tecn_param_scroll = gtk_scrolled_window_new(NULL,NULL);
	tecn_param_box = gtk_box_new(1,0);

	gtk_box_pack_start(GTK_BOX(tecn_param_box),tecn_caminhos_fixed,0,0,5);

	gtk_container_add(GTK_CONTAINER(tecn_param_scroll),tecn_param_box);

	gtk_widget_set_size_request(tecn_param_box,580,400);
	gtk_widget_set_size_request(tecn_param_scroll,580,400);
	gtk_widget_set_size_request(geral_box,580,400);

	gtk_box_pack_start(GTK_BOX(geral_box),wallpapers_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(geral_box),personaliza_frame,0,0,10);

	atualizar_button = gtk_button_new_with_label("Atualizar");
	atualizar_image = gtk_image_new_from_file(IMG_REC);
	gtk_button_set_image(GTK_BUTTON(atualizar_button),atualizar_image);
	gtk_box_pack_start(GTK_BOX(opcoes_box),atualizar_button,0,0,30);

	ter_criticas_frame = gtk_frame_new("Campos Criticados");
	ter_criticas_box = gtk_box_new(1,0);

	orc_criticas_frame = gtk_frame_new("Produto em Orçamentos");
	orc_criticas_box = gtk_box_new(1,0);

	orc_parametros_fixed = gtk_fixed_new();
	est_orc_padrao = gtk_spin_button_new_with_range(1,5,1);
	est_orc_padrao_frame = gtk_frame_new("Estoque padrão");
	orc_parametros_frame = gtk_frame_new("Parâmetros Orçamentos");
	orc_parametros_box = gtk_box_new(1,0);
	gtk_container_add(GTK_CONTAINER(est_orc_padrao_frame),est_orc_padrao);
	gtk_box_pack_start(GTK_BOX(orc_parametros_box),est_orc_padrao_frame,0,0,0);
	gtk_container_add(GTK_CONTAINER(orc_parametros_frame),orc_parametros_box);
	gtk_fixed_put(GTK_FIXED(orc_parametros_fixed),orc_parametros_frame,20,0);

	sprintf(query,"select nome from criticas");
	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro consultando nome dos campos de criticas");

		return 1;
	}
	cont=0;

	while((row=mysql_fetch_row(res))!=NULL)
	{
		campos_de_critica[cont] = gtk_check_button_new_with_label(row[0]);
		if(cont<=ter_critic_campos_qnt)
			gtk_box_pack_start(GTK_BOX(ter_criticas_box),campos_de_critica[cont],0,0,0);
		else
		if(cont<=orc_critic_campos_qnt)
			gtk_box_pack_start(GTK_BOX(orc_criticas_box),campos_de_critica[cont],0,0,0);

		cont++;
	}

	sprintf(query,"select * from confs");
	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro consultando configurações técnicas");
		return 1;
	}
	cont=0;

	while((row=mysql_fetch_row(res))!=NULL)
	{

		cont++;
	}

	gtk_container_add(GTK_CONTAINER(ter_criticas_frame),ter_criticas_box);

	gtk_box_pack_start(GTK_BOX(terc_box),ter_criticas_frame,0,0,10);

	gtk_container_add(GTK_CONTAINER(orc_criticas_frame),orc_criticas_box);

	gtk_box_pack_start(GTK_BOX(orc_box),orc_criticas_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(orc_box),orc_parametros_fixed,0,0,10);

	gtk_box_pack_start(GTK_BOX(tecnico_box),tecn_param_scroll,0,0,10);

	gtk_box_pack_start(GTK_BOX(gerencial_box),janela_init,0,0,5);

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),geral_box,gtk_label_new("Geral"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),terc_box,gtk_label_new("Terceiros"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),prod_box,gtk_label_new("Produtos"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),orc_box,gtk_label_new("Orçamentos"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),gerencial_box,gtk_label_new("Gerencial"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),tecnico_box,gtk_label_new("Técnico"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),outros_box,gtk_label_new("Outros"));

	if(sessao_oper.nivel < NIVEL_GERENCIAL_CODE)
		gtk_widget_set_sensitive(outros_box,FALSE);

	gtk_box_pack_start(GTK_BOX(caixona),notebook,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixona),opcoes_box,0,0,20);
	gtk_container_add(GTK_CONTAINER(janela_parametros),caixona);
	gtk_widget_show_all(janela_parametros);

	receber_personalizacao();
	ler_criticas();


	g_signal_connect(tema_combo_box,"changed",G_CALLBACK(temas),NULL);
	g_signal_connect(atualizar_button,"clicked",G_CALLBACK(atualizar_paramentros),NULL);
	g_signal_connect(janela_parametros,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_PARAM_WIN]);
	gtk_widget_show_all(janela_parametros);

	return 0;
}
