static int ler_personalizacao()
{
	//*usar gtk_toggle_button_get_active aqui
	personalizacao.tema = gtk_combo_box_get_active(GTK_COMBO_BOX(tema_combo_box));		
	personalizacao.janela_init = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(janela_init));
	personalizacao.janela_keep_above = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(janela_keep_above));		
	return 0;
}

static int receber_personalizacao()
{
	MYSQL_RES *res;
	MYSQL_ROW row;

	char *query;
	query = malloc(MAX_QUERY_LEN);
	sprintf(query,"select * from perfil_desktop where code = %s",oper_code);

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

	return 0;
}

int atualizar_personalizacao()
{
	int erro;
	char *query;
	query = malloc(MAX_QUERY_LEN);
	ler_personalizacao();
	sprintf(query,"update perfil_desktop set janela_init = %i",personalizacao.janela_init);
	if((erro = enviar_query(query))!=0)
	{
		popup(NULL,"Erro ao configurar janela login");
	}
	sprintf(query,"update perfil_desktop set tema = %i,janelas_keep_above = %i where code = %s",personalizacao.tema,personalizacao.janela_keep_above,oper_code);
	if((erro = enviar_query(query))!=0)
	{
		popup(NULL,"Erro ao enviar dados para personalizacao do sistema");
		return 1;
	}
	
	receber_personalizacao();
	return 0;
}

int configurar_parametros()
{
	int cont;
	char *query;
	query = malloc(MAX_QUERY_LEN);
	MYSQL_RES *res;
	MYSQL_ROW  row;
	for(cont=0;cont<=orc_critic_campos_qnt;cont++)
	{
		sprintf(query,"select critica from criticas where opcao_nome = 'terceiros' and campo_nome = '%s'",critica_campos[cont]);
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
						
					}
				}
			}
		}
	}
	return 0;
}

int ler_criticas()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	int cont=0;
	g_print("Lendo Parametros\n");
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
			sprintf(query,"update criticas set critica = 1 where opcao_nome = 'terceiros' and campo_nome = '%s'",critica_campos[cont]);
			erro = enviar_query(query);
			if(erro != 0)
			{
				popup(NULL,"Erro ao tentar atualizar parametros");
				return 1;
			}
		}
		else
		{
			sprintf(query,"update criticas set critica = 0 where opcao_nome = 'terceiros' and campo_nome = '%s'",critica_campos[cont]);
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
	char *wallpapers_nome[] = {"Grey","Cascate","Vulcon","Maré","Wallpaper 5","Wallpaper 6"};
	GtkWidget **caixa_wallpapers,**image_wallpapers,**label_wallpapers,**event_wallpapers,
	*wallpapers_box,*wallpapers_scroll,*wallpapers_frame;

	GtkWidget *geral_box,*terc_box,*prod_box,*orc_box;
	
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
	gtk_window_set_title(GTK_WINDOW(janela_parametros),"Parametros");
	gtk_window_set_keep_above(GTK_WINDOW(janela_parametros),TRUE);
	gtk_window_set_position(GTK_WINDOW(janela_parametros),GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_icon_name(GTK_WINDOW(janela_parametros),"preferences-system");
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

	gtk_box_pack_start(GTK_BOX(personaliza_box),janela_init,0,0,5);
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
		
	gtk_container_add(GTK_CONTAINER(ter_criticas_frame),ter_criticas_box);

	gtk_box_pack_start(GTK_BOX(terc_box),ter_criticas_frame,0,0,10);
	
	gtk_container_add(GTK_CONTAINER(orc_criticas_frame),orc_criticas_box);
	
	gtk_box_pack_start(GTK_BOX(orc_box),orc_criticas_frame,0,0,10);
	
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),geral_box,gtk_label_new("Geral"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),terc_box,gtk_label_new("Terceiros"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),prod_box,gtk_label_new("Produtos"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),orc_box,gtk_label_new("Orçamentos")); /* atualizar mais tarde*/
	
	receber_personalizacao();
	ler_criticas();

	gtk_box_pack_start(GTK_BOX(caixona),notebook,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixona),opcoes_box,0,0,20);
	gtk_container_add(GTK_CONTAINER(janela_parametros),caixona);

	g_signal_connect(tema_combo_box,"changed",G_CALLBACK(temas),NULL);
	g_signal_connect(atualizar_button,"clicked",G_CALLBACK(atualizar_paramentros),NULL);

	gtk_widget_show_all(janela_parametros);
	return 0;
}
