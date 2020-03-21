#include <stdio.h>
#include <gtk/gtk.h>
#include <time.h>
GtkWidget  *fixed_razao, *fixed_endereco, *fixed_cnpj;
GtkWidget  *razao,*endereco,*cnpj, *caixa_infos;
GtkWidget *janela_inicializacao;
int tecla_close_window(GtkWidget *widget,GdkEventKey *evento)
{
	if(evento->keyval)
		gtk_widget_destroy(GTK_WIDGET(janela_inicializacao));
	return 0;
}

int clique_close_window(GtkWidget *widget,GdkEventButton *evento)
{
	gtk_widget_destroy(GTK_WIDGET(janela_inicializacao));
	return 0;
}

int conexao()
{
	char *infos(int), *string;
	int conectado=0,tentativas=0;
	while(conectado==0)
	{
		string = infos(0);
		if(string==NULL)
		{
			razao = gtk_button_new_with_label("offline");
			autologger("A razao social veio vazia");
			conectado = 0;
		}
		else
		{
			razao = gtk_label_new(infos(0));
			conectado = 1;
		}
		string = infos(1);
		if(string == NULL)
		{
			endereco = gtk_button_new_with_label("offline");
			autologger("o endereco veio vazio");
			conectado = 0;
		}	
		else
		{
			endereco = gtk_label_new(string);
			conectado = 1;
		}
		string = infos(2);
		if(string == NULL)
		{
			cnpj = gtk_button_new_with_label("offline");
			autologger("O cnpj esta vazio");
			conectado = 0;
		}
		else
		{
			cnpj = gtk_label_new(string);
			conectado = 1;
		}
		if(tentativas>CONECT_QNT)
		{
			return 1;
		}
		tentativas++;
	}
	return 0;
}

int desktop()
{
	int err=0;
	GtkWidget  *juncao;
	GtkWidget  *layout, *imagem_fundo;
		
	g_print("Fechando janela init\n");
	gtk_widget_destroy(janela_inicializacao);
	layout = gtk_layout_new(NULL,NULL);
	imagem_fundo = gtk_image_new_from_file(DESKTOP);

//	imagem_barra  = gtk_image_new_from_file(BARRA_IMG);
	imagem_barra = gtk_box_new(1,0);
	gtk_widget_set_name(imagem_barra,"barra");
	layout_barra  = gtk_layout_new(NULL,NULL);	
	botao_iniciar = gtk_button_new_with_label("Menu");	
	gtk_widget_set_name(GTK_WIDGET(botao_iniciar),"botao");

	janela_principal = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(janela_principal),"Calisto");
	gtk_container_set_border_width(GTK_CONTAINER(janela_principal),1);	
	gtk_window_set_resizable(GTK_WINDOW(janela_principal),TRUE);
	
	g_signal_connect(GTK_WINDOW(janela_principal),"delete-event",G_CALLBACK(gtk_main_quit),NULL);
		
	err = conexao();
	if(err!=0)
	{
			popup(NULL,"Não foi posivel conectar");
	}
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
	
	juncao = gtk_box_new(1,0);
	area_de_trabalho = gtk_box_new(0,0);
	//fixed_sup_border = gtk_fixed_new();
	fixed_razao = gtk_fixed_new();	
	fixed_endereco = gtk_fixed_new();	
	fixed_cnpj = gtk_fixed_new();

	gtk_fixed_put(GTK_FIXED(fixed_razao),razao,60,250);
	gtk_widget_set_name(razao,"infos");
	gtk_fixed_put(GTK_FIXED(fixed_endereco),endereco,60,5);
	gtk_widget_set_name(endereco,"infos");
	gtk_fixed_put(GTK_FIXED(fixed_cnpj),cnpj,60,5);
	gtk_widget_set_name(cnpj,"infos");
	
	gtk_box_pack_start(GTK_BOX(caixa_infos),fixed_razao,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_infos),fixed_endereco,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_infos),fixed_cnpj,0,0,0);	
	
    gtk_box_pack_start(GTK_BOX(superior_1),caixa_infos,0,0,0);
		
	gtk_box_pack_start(GTK_BOX(superior),superior_1,0,0,0);
	gtk_box_pack_end(GTK_BOX(superior),superior_2,0,0,0);	
	
	gtk_box_pack_start(GTK_BOX(inferior),inferior_1,0,0,0);
	gtk_box_pack_end(GTK_BOX(inferior),inferior_2,0,0,0);	
	
	gtk_widget_set_size_request(GTK_WIDGET(superior),1291,0);
	gtk_widget_set_size_request(GTK_WIDGET(inferior),1291,0);

	gtk_widget_set_size_request(GTK_WIDGET(juncao),1291,750);
	gtk_widget_set_size_request(GTK_WIDGET(area_de_trabalho),1291,750);
	gtk_box_pack_start(GTK_BOX(juncao),superior,0,0,0);
	gtk_box_pack_start(GTK_BOX(juncao),inferior,0,0,0);


	gtk_box_pack_start(GTK_BOX(area_de_trabalho),juncao,0,0,0);
	
	gtk_layout_put(GTK_LAYOUT(layout_barra),imagem_barra,0,0);
	gtk_layout_put(GTK_LAYOUT(layout_barra),botao_iniciar,0,10);
	
	gtk_widget_set_size_request(GTK_WIDGET(botao_iniciar),75,60);
	
	
	
	gtk_widget_set_size_request(barra,75,765);
	gtk_widget_set_size_request(layout_barra,75,765);

	gtk_container_add(GTK_CONTAINER(barra),layout_barra);

	gtk_box_pack_end(GTK_BOX(area_de_trabalho),barra,0,0,0);
	
	gtk_widget_set_size_request(imagem_fundo,1291,750);
	gtk_layout_put(GTK_LAYOUT(layout), imagem_fundo, 0, 0);
	gtk_layout_put(GTK_LAYOUT(layout),area_de_trabalho,0,0);
		
	gtk_window_set_position(GTK_WINDOW(janela_principal),0);
       	
	gtk_container_add(GTK_CONTAINER(janela_principal),layout);
	menu();	
	gtk_box_pack_end(GTK_BOX(superior_2),lista_abas,0,0,0);

	g_signal_connect(GTK_WIDGET(janela_principal),"key_press_event",G_CALLBACK(tecla_menu),NULL);
	g_signal_connect(GTK_WIDGET(botao_iniciar),"clicked",G_CALLBACK(clique_menu),NULL);
	

	gtk_window_set_default_size(GTK_WINDOW(janela_principal),600,300);
	gtk_window_maximize(GTK_WINDOW(janela_principal));
	gtk_widget_show_all(janela_principal);
	gtk_widget_hide(lista_abas);	
	return 0;
}
int init()
{
	char *msg;
	msg = malloc(100);
	g_print("inicializacao...\n");
	struct tm *estrutura_tempo;
	time_t tempo;
	time(&tempo);
	estrutura_tempo = localtime(&tempo);
	sprintf(msg,"inicializando as %i:%i do dia %i/%i\n",estrutura_tempo->tm_hour,estrutura_tempo->tm_min,estrutura_tempo->tm_mday,estrutura_tempo->tm_mon);
	autologger(msg);
	GtkWidget *imagem_inicializacao;
	GtkWidget *event;
	event = gtk_event_box_new();
	janela_inicializacao = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_set_resizable(GTK_WINDOW(janela_inicializacao),FALSE);
	imagem_inicializacao = gtk_image_new_from_file(INIT_IMAGE);
	gtk_widget_set_size_request(GTK_WIDGET(imagem_inicializacao),1366,768);
	gtk_container_add(GTK_CONTAINER(event),imagem_inicializacao);
	gtk_container_add(GTK_CONTAINER(janela_inicializacao),event);
	
	g_signal_connect(janela_inicializacao,"key_press_event",G_CALLBACK(desktop),NULL);
	g_signal_connect(janela_inicializacao,"button_press_event",G_CALLBACK(desktop),NULL);
	
	g_print("abrindo janela de inicio...\n");
	gtk_widget_show_all(janela_inicializacao);
	
	return 0;
}
