
#include <stdio.h>
#include <gtk/gtk.h>
#include <time.h>
GtkWidget  *fixed_razao, *fixed_endereco, *fixed_cnpj;
GtkWidget  *razao,*endereco,*cnpj, *caixa_infos;
GtkWidget *janela_inicializacao;

static void ativacao_app(){
	GCancellable *cancellable;
	GError *error;
	cancellable = g_cancellable_new ();

	aplicacao = gtk_application_new(NULL, G_APPLICATION_CAN_OVERRIDE_APP_ID);
	g_application_register(G_APPLICATION(aplicacao),NULL,NULL);
	janela_principal = gtk_application_window_new(aplicacao);

	gtk_window_set_title(GTK_WINDOW(janela_principal),"Petitto");
	//if(personalizacao.janela_keep_above==1)
		//gtk_window_set_keep_above(GTK_WINDOW(janela_principal), TRUE);
	gtk_window_set_icon_name(GTK_WINDOW(janela_principal),"accessories-dictionary");
	gtk_container_set_border_width(GTK_CONTAINER(janela_principal),0);
	gtk_window_set_resizable(GTK_WINDOW(janela_principal),TRUE);
	gtk_window_set_position(GTK_WINDOW(janela_principal),0);
	g_signal_connect(GTK_WIDGET(janela_principal),"key_press_event",G_CALLBACK(tecla_menu),NULL);
	gtk_window_set_default_size(GTK_WINDOW(janela_principal),1366,768);
	gtk_window_maximize(GTK_WINDOW(janela_principal));

	return ;
}


int desktop()
{
	int err=0;
	GtkWidget  *juncao;
	GtkWidget  *layout;
	GtkWidget *fixed_menu;
	GtkWidget *param_button,*param_image;
	GtkWidget *sair_button, *sair_image;

	GtkWidget *nome_usuario_label,*nome_usuario_fixed;
	gchar *nome_usuario_gchar;

	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	char markup[500];

	ativacao_app();

	fixed_menu = gtk_fixed_new();
	param_button = gtk_button_new();
	param_image = gtk_image_new_from_file(PRMT_IMG);
	gtk_button_set_image(GTK_BUTTON(param_button),param_image);

	sair_button = gtk_button_new();
	sair_image = gtk_image_new_from_file(EXIT_IMG);
	gtk_button_set_image(GTK_BUTTON(sair_button),sair_image);

	g_print("Fechando janela init\n");
	gtk_widget_destroy(janela_inicializacao);

	pegar_data();

	layout = gtk_layout_new(NULL,NULL);

	query = malloc(MAX_QUERY_LEN);

	sprintf(query,"select * from perfil_desktop where code = %i",sessao_oper.code);
	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro ao receber dados para personalizacao do sistema");
		gtk_main_quit();
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Sem dados para personalizar o sistema");
		gtk_main_quit();
		return 1;
	}

	personalizacao.tema = atoi(row[2]);
	personalizacao.janela_init = atoi(row[3]);
	personalizacao.janela_keep_above = atoi(row[4]);

	GtkSettings *settings;
	settings = gtk_settings_get_default();
	g_object_set(settings, "gtk-theme-name",nomes_temas[personalizacao.tema],NULL);

	if(sessao_oper.nivel>=5)
	{
		GtkSettings *settings;
		imagem_desktop = gtk_image_new_from_file(OPER_DESKTOP);
		settings = gtk_settings_get_default();
		nome_usuario_label = gtk_label_new("OPERADOR DE CORREÇÃO");
		g_object_set(settings, "gtk-theme-name","Adwaita-dark",NULL);
	}
	else
	{
		sprintf(query,"select a.nome,b.desktop_img from perfil_desktop as b join operadores as a on a.code = b.code where b.code = %i",sessao_oper.code);
		res = consultar(query);
		if(res==NULL)
		{
			popup(NULL,"Personalizacao com erro");
			gtk_main_quit();
			return 1;
		}

		nome_usuario_gchar = malloc(MAX_OPER_LEN+10);
		g_print("Recebendo escolha de wallpaper e nome usuario\n");
		row = mysql_fetch_row(res);
		if(row!=NULL)
		{
			g_print("Trocando wallpaper\n");
			imagem_desktop = gtk_image_new_from_file(DESKTOP);
			sprintf(nome_usuario_gchar,"Operador: %s",row[0]);
			nome_usuario_label = gtk_label_new(nome_usuario_gchar);
			gtk_widget_set_name(nome_usuario_label,"nome_operador");
			trocar_desktop(NULL,NULL,atoi(row[1]));
			g_print("Desktop com imagem personalizada\n");
			autologger("Desktop com imagem personalizada\n");
			autologger(row[1]);
		}
		else
		{
			popup(NULL,"Login indevido");
			gtk_main_quit();
			return 1;
		}
	}

	imagem_barra = gtk_box_new(1,0);
	gtk_widget_set_name(imagem_barra,"barra");
	layout_barra  = gtk_layout_new(NULL,NULL);
	botao_iniciar = gtk_button_new_with_label("Menu");
	gtk_widget_set_name(GTK_WIDGET(botao_iniciar),"botao");

	//criacao
	caixa_infos = gtk_box_new(1,0);

	superior = gtk_box_new(0,0);
	superior_1 = gtk_box_new(1,0);
	superior_2 = gtk_box_new(0,0);

	inferior = gtk_box_new(0,0);
	inferior_1 = gtk_box_new(1,0);
	inferior_2 = gtk_box_new(1,0);

	barra = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	gtk_widget_set_name(barra,"barra");
	gtk_widget_set_name(botao_iniciar,"botao_iniciar");

	juncao = gtk_box_new(1,0);
	area_de_trabalho = gtk_box_new(0,0);
	//fixed_sup_border = gtk_fixed_new();

	razao = gtk_label_new(infos(0));
	endereco = gtk_label_new(infos(1));
	cnpj = gtk_label_new(infos(2));

	fixed_razao = gtk_fixed_new();
	fixed_endereco = gtk_fixed_new();
	fixed_cnpj = gtk_fixed_new();

	gtk_fixed_put(GTK_FIXED(fixed_razao),razao,50,250);
	gtk_widget_set_name(razao,"infos");

	gtk_fixed_put(GTK_FIXED(fixed_endereco),endereco,50,5);
	gtk_widget_set_name(endereco,"infos");

	gtk_fixed_put(GTK_FIXED(fixed_cnpj),cnpj,50,5);
	gtk_widget_set_name(cnpj,"infos");


	nome_usuario_fixed = gtk_fixed_new();
	gtk_fixed_put(GTK_FIXED(nome_usuario_fixed),nome_usuario_label,100,200);

	gtk_box_pack_start(GTK_BOX(caixa_infos),fixed_razao,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_infos),fixed_endereco,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_infos),fixed_cnpj,0,0,0);

	gtk_box_pack_start(GTK_BOX(superior),superior_1,0,0,0);
	gtk_box_pack_end(GTK_BOX(superior),superior_2,0,0,0);

	gtk_box_pack_start(GTK_BOX(inferior),inferior_1,0,0,0);
	gtk_box_pack_end(GTK_BOX(inferior),inferior_2,0,0,0);

	gtk_widget_set_size_request(GTK_WIDGET(superior),1291,0);
	gtk_widget_set_size_request(GTK_WIDGET(inferior),1291,0);

	gtk_widget_set_size_request(GTK_WIDGET(juncao),1290,750);
	gtk_widget_set_size_request(GTK_WIDGET(area_de_trabalho),1290,750);
	gtk_box_pack_start(GTK_BOX(juncao),superior,0,0,0);
	gtk_box_pack_start(GTK_BOX(juncao),inferior,0,0,0);

	gtk_box_pack_start(GTK_BOX(area_de_trabalho),juncao,0,0,0);

	gtk_layout_put(GTK_LAYOUT(layout_barra),imagem_barra,0,0);
	gtk_layout_put(GTK_LAYOUT(layout_barra),botao_iniciar,0,1);
	gtk_layout_put(GTK_LAYOUT(layout_barra),param_button,0,550);
	gtk_layout_put(GTK_LAYOUT(layout_barra),sair_button,0,630);

	gtk_widget_set_size_request(GTK_WIDGET(botao_iniciar),75,60);
	gtk_widget_set_size_request(GTK_WIDGET(param_button),75,60);
	gtk_widget_set_size_request(GTK_WIDGET(sair_button),75,60);

	gtk_widget_set_size_request(barra,80,750);
	gtk_widget_set_size_request(layout_barra,80,750);

	gtk_container_add(GTK_CONTAINER(barra),layout_barra);

	gtk_box_pack_end(GTK_BOX(area_de_trabalho),barra,0,0,0);

	gtk_widget_set_size_request(imagem_desktop,1290,750);
	gtk_layout_put(GTK_LAYOUT(layout), imagem_desktop, 0, 0);
	gtk_layout_put(GTK_LAYOUT(layout),nome_usuario_fixed,0,0);
	gtk_layout_put(GTK_LAYOUT(layout),caixa_infos,0,0);
	gtk_layout_put(GTK_LAYOUT(layout),area_de_trabalho,0,0);


	gtk_container_add(GTK_CONTAINER(janela_principal),layout);

	menu();
	gtk_fixed_put(GTK_FIXED(fixed_menu),frame_lista_abas,0,0);
	gtk_box_pack_end(GTK_BOX(superior_2),fixed_menu,0,0,0);


	g_signal_connect(GTK_WIDGET(botao_iniciar),"clicked",G_CALLBACK(clique_menu),NULL);

	g_signal_connect(GTK_BUTTON(sair_button),"clicked",G_CALLBACK(encerrar),janela_principal);

	g_signal_connect(GTK_BUTTON(param_button),"clicked",G_CALLBACK(parametrizar),NULL);

	g_signal_connect(janela_principal,"destroy",G_CALLBACK(encerrando),NULL);
	gtk_widget_show_all(janela_principal);

	configurar_parametros();

	gtk_widget_hide(lista_abas);
	return 0;
}
int init()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	inicializando=1;
	GtkWidget *imagem_inicializacao;
	imagem_inicializacao = gtk_image_new_from_file(INIT_IMAGE);
	gtk_widget_set_size_request(GTK_WIDGET(imagem_inicializacao),1366,768);

	janela_inicializacao = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_set_resizable(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_set_icon_name(GTK_WINDOW(janela_inicializacao),"preferences-desktop-screensaver");
	gtk_container_add(GTK_CONTAINER(janela_inicializacao),imagem_inicializacao);
	gtk_window_set_decorated(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_set_deletable(GTK_WINDOW(janela_inicializacao),FALSE);
	query = malloc(MAX_QUERY_LEN);

	g_print("inicializacao...\n");

	sprintf(query,"select janela_init,tema from perfil_desktop");
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

	icone = gtk_icon_theme_get_default();
	gchar **path;
	int n_elements;

	//return 0;
	gtk_icon_theme_get_search_path(icone,&path,&n_elements);
	n_elements = n_elements+1;
	path[n_elements-1] = malloc(strlen(ICON_PATH));
	strcpy((char*)path[n_elements-1],ICON_PATH);

	gtk_icon_theme_set_search_path(icone, (const gchar**)path, n_elements);
	for(int cont=0;cont<n_elements;cont++)
		g_print("caminho tema %i : %s\n",cont,path[cont]);

	//return 1;
	gtk_widget_show_all(janela_inicializacao);

	personalizacao.tema = atoi(row[1]);
	ler_theme_dir();

	if(atoi(row[0])==0)
	{
		sessao_oper.code = 1;

		if(desktop()!=0)
		{
			popup(NULL,"Erro na inicializacao");
			inicializando=0;
			return 1;
		}
	}
	else
	{
		login();
		gtk_widget_show_all(janela_login);
	}

	g_print("abrindo janela de inicio...\n");
	inicializando=0;
	return 0;
}
