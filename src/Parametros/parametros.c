#include "orc_params.c"
#include "prod_params.c"
#include "ter_params.c"
#include "integr_params.c"
#include "param_dev.c"
#include "personalizacao.c"

int configurar_parametros()
{
	int cont;
	char query[MAX_QUERY_LEN];
	MYSQL_RES *res;
	MYSQL_ROW  row;

	receber_orc_params();
	receber_prod_params();
	receber_intgr_params();

	sprintf(query,"select * from confs where code = %i",sessao_oper->operador->code);

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
	strcpy(navegadores.navegador_path2,row[2]);
	navegadores.navegador_pdr = atoi(row[3]);

	strcpy(impressoras.imp_path1,row[4]);
	strcpy(impressoras.imp_path2,row[5]);
	strcpy(impressoras.imp_path3,row[6]);

	carregar_navimps();

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
	orc_params.est_orc_padrao = atoi(row[0]);
	return 0;
}

int atualizar_paramentros()
{
	if(atualizar_orc_params())
		return 1;
	if(atualizar_prod_params())
		return 1;
	if(atualizar_intgr_params())
		return 1;

	if(atualizar_personalizacao())
		return 1;

	popup(NULL,"Parametros Atualizados");
	return 0;
}

int parametrizar()
{

	if(!app_is_ativo())
		return 1;

	GtkWidget *janela_parametros;
	GtkWidget *notebook;
	GtkWidget *caixona,*caixa_superior;
	GtkWidget *geral_box, *terc_box, *prod_box, *orc_box, *integr_box, *gerencial_box, *tecnico_box, *outros_box;
	GtkWidget *geral_criticas_frame,*ter_criticas_frame,*prod_criticas_frame,*orc_criticas_frame;
	GtkWidget *geral_criticas_box,*ter_criticas_box,*prod_criticas_box,*orc_criticas_box;

	GtkWidget *personaliza_box,*personaliza_frame;
	char *wallpapers_nome[] = {"Grey","Cascate","Vulcon","Maré","Grin","Tripo"};
	GtkWidget *tema_combo_box_fixed;
	GtkWidget **caixa_wallpapers,**image_wallpapers,**label_wallpapers,**event_wallpapers,
	*wallpapers_box,*wallpapers_scroll,*wallpapers_frame;

	GtkWidget *prod_parametros_frame, *prod_parametros_box, *prod_parametros_fixed;

	GtkWidget *orc_parametros_frame, *orc_parametros_box, *orc_parametros_fixed;

	GtkWidget *est_orc_padrao_frame;

	GtkWidget *tecn_caminhos_box, *tecn_caminhos_frame, *tecn_caminhos_fixed;

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

	gpointer loading = carregando_wnd();
	while (g_main_context_pending(NULL))
		g_main_context_iteration(NULL,FALSE);

	janela_parametros = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(janela_parametros,600,400);
	gtk_window_set_default_size(GTK_WINDOW(janela_parametros),600,400);
	gtk_window_set_title(GTK_WINDOW(janela_parametros),"Parametros");
	gtk_window_set_transient_for(GTK_WINDOW(janela_parametros),GTK_WINDOW(janela_principal));
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
	integr_box = gtk_box_new(1,0);
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

	tecn_param_nav_path1_fchoose = gtk_file_chooser_button_new("Escolher Navegador 1",GTK_FILE_CHOOSER_ACTION_OPEN);
	tecn_param_nav_path2_fchoose = gtk_file_chooser_button_new("Escolher Navegador 2",GTK_FILE_CHOOSER_ACTION_OPEN);

	tecn_param_imp_path1_fchoose = gtk_file_chooser_button_new("Escolher Impressora. 1",GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	tecn_param_imp_path2_fchoose = gtk_file_chooser_button_new("Escolher Impressora. 2",GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	tecn_param_imp_path3_fchoose = gtk_file_chooser_button_new("Escolher Impressora 3",GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);

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

	prod_criticas_frame = gtk_frame_new("Produtos");
	prod_criticas_box = gtk_box_new(1,0);

	prod_parametros_fixed = gtk_fixed_new();
	prod_parametros_frame = gtk_frame_new("Parâmetros Produtos");
	prod_parametros_box = gtk_box_new(1,0);
	gtk_container_add(GTK_CONTAINER(prod_parametros_frame),prod_parametros_box);
	gtk_fixed_put(GTK_FIXED(prod_parametros_fixed),prod_parametros_frame,20,0);

	orc_parametros_fixed = gtk_fixed_new();
	est_orc_padrao = gtk_spin_button_new_with_range(1,5,1);
	est_orc_padrao_frame = gtk_frame_new("Estoque padrão");
	orc_parametros_frame = gtk_frame_new("Parâmetros Orçamentos");
	orc_parametros_box = gtk_box_new(1,0);
	gtk_container_add(GTK_CONTAINER(est_orc_padrao_frame),est_orc_padrao);
	gtk_box_pack_start(GTK_BOX(orc_parametros_box),est_orc_padrao_frame,0,0,0);
	gtk_container_add(GTK_CONTAINER(orc_parametros_frame),orc_parametros_box);
	gtk_fixed_put(GTK_FIXED(orc_parametros_fixed),orc_parametros_frame,20,0);

	orc_prod_mov_wdt = gtk_check_button_new_with_label("Bloqueia Produtos sem movimentos de estoque");
	orc_prod_sld_wdt = gtk_check_button_new_with_label("Produto deve ter saldo para criar orcamento");
	orc_prod_sld_lmt_wdt = gtk_check_button_new_with_label("Avisar saldo próximo ao limite ");
	orc_ped_canc_wdt = gtk_check_button_new_with_label("Pedidos cancelados são reaproveitados");

	gtk_box_pack_start(GTK_BOX(orc_criticas_box),orc_prod_mov_wdt,0,0,0);
	gtk_box_pack_start(GTK_BOX(orc_criticas_box),orc_prod_sld_wdt,0,0,0);
	gtk_box_pack_start(GTK_BOX(orc_criticas_box),orc_prod_sld_lmt_wdt,0,0,0);
	gtk_box_pack_start(GTK_BOX(orc_criticas_box),orc_ped_canc_wdt,0,0,0);

	//gtk_box_pack_start(GTK_BOX(prod_criticas_box),,0,0,0);

	GtkWidget *integr_opc_frame = gtk_frame_new("Integração");
	integr_opc_wdt = gtk_combo_box_text_new();
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(integr_opc_wdt),0,"Nenhum");
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(integr_opc_wdt),1,"Woocommerce");
	gtk_container_add(GTK_CONTAINER(integr_opc_frame),integr_opc_wdt);

	integr_usuario_wdt = gtk_entry_new();
	GtkWidget *integr_user_frame = gtk_frame_new("Usuário");
	gtk_container_add(GTK_CONTAINER(integr_user_frame),integr_usuario_wdt);

	integr_senha_wdt = gtk_entry_new();
	GtkWidget *integr_senha_frame = gtk_frame_new("Senha");
	gtk_container_add(GTK_CONTAINER(integr_senha_frame),integr_senha_wdt);

	integr_bd_wdt = gtk_entry_new();
	GtkWidget *integr_bd_frame = gtk_frame_new("Banco de Dados");
	gtk_container_add(GTK_CONTAINER(integr_bd_frame),integr_bd_wdt);

	integr_server_wdt = gtk_entry_new();
	GtkWidget *integr_server_frame = gtk_frame_new("Servidor");
	gtk_container_add(GTK_CONTAINER(integr_server_frame),integr_server_wdt);

	integr_tabprefix_wdt = gtk_entry_new();
	GtkWidget *integr_tabprefix_frame = gtk_frame_new("Prefixo Tabela");
	gtk_container_add(GTK_CONTAINER(integr_tabprefix_frame),integr_tabprefix_wdt);

	GtkWidget *integr_testeconn_button = gtk_button_new_with_label("Conectar");

	GtkWidget *integr_params_box = gtk_box_new(1,0);
	GtkWidget *integr_params_box1 = gtk_box_new(0,0);
	GtkWidget *integr_params_box2 = gtk_box_new(0,0);
	GtkWidget *integr_params_box3 = gtk_box_new(0,0);
	GtkWidget *integr_params_frame = gtk_frame_new("Parametros");
	gtk_box_pack_start(GTK_BOX(integr_params_box1),integr_opc_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(integr_params_box1),integr_server_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(integr_params_box2),integr_user_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(integr_params_box2),integr_senha_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(integr_params_box2),integr_bd_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(integr_params_box2),integr_tabprefix_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(integr_params_box3),integr_testeconn_button,0,0,5);

	gtk_box_pack_start(GTK_BOX(integr_params_box),integr_params_box1,0,0,5);
	gtk_box_pack_start(GTK_BOX(integr_params_box),integr_params_box2,0,0,5);
	gtk_box_pack_start(GTK_BOX(integr_params_box),integr_params_box3,0,0,5);

	gtk_container_add(GTK_CONTAINER(integr_params_frame),integr_params_box);
	GtkWidget *integr_params_fixed = gtk_fixed_new();
	gtk_fixed_put(GTK_FIXED(integr_params_fixed),integr_params_frame,5,5);

	gtk_box_pack_start(GTK_BOX(integr_box),integr_params_fixed,0,0,10);

	gtk_container_add(GTK_CONTAINER(ter_criticas_frame),ter_criticas_box);
	gtk_box_pack_start(GTK_BOX(terc_box),ter_criticas_frame,0,0,10);

	gtk_container_add(GTK_CONTAINER(orc_criticas_frame),orc_criticas_box);
	gtk_box_pack_start(GTK_BOX(orc_box),orc_criticas_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(orc_box),orc_parametros_fixed,0,0,10);

	gtk_container_add(GTK_CONTAINER(prod_criticas_frame),prod_criticas_box);
	gtk_box_pack_start(GTK_BOX(prod_box),prod_criticas_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(prod_box),prod_parametros_fixed,0,0,10);

	gtk_box_pack_start(GTK_BOX(tecnico_box),tecn_param_scroll,0,0,10);

	gtk_box_pack_start(GTK_BOX(gerencial_box),janela_init,0,0,5);

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),geral_box,gtk_label_new("Geral"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),terc_box,gtk_label_new("Terceiros"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),prod_box,gtk_label_new("Produtos"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),orc_box,gtk_label_new("Orçamentos"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),integr_box,gtk_label_new("Integrações"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),gerencial_box,gtk_label_new("Gerencial"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),tecnico_box,gtk_label_new("Técnico"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),outros_box,gtk_label_new("Outros"));

	if(sessao_oper->operador->nivel < NIVEL_GERENCIAL)
		gtk_widget_set_sensitive(outros_box,FALSE);

	gtk_box_pack_start(GTK_BOX(caixona),notebook,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixona),opcoes_box,0,0,20);
	gtk_container_add(GTK_CONTAINER(janela_parametros),caixona);
	gtk_widget_show_all(janela_parametros);

	receber_personalizacao();
	ler_orc_params();
	ler_prod_params();
	ler_intgr_params();

	g_signal_connect(tema_combo_box,"changed",G_CALLBACK(temas),NULL);
	g_signal_connect(atualizar_button,"clicked",G_CALLBACK(atualizar_paramentros),NULL);
	g_signal_connect(janela_parametros,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_PARAM_WIN]);
	g_signal_connect(integr_testeconn_button,"clicked",G_CALLBACK(intgr_params_testar),NULL);

	gtk_widget_show_all(janela_parametros);

	gtk_widget_destroy(loading);
	return 0;
}
