#define QUERY_LEN 1000
#define RANDOM_STRING_SIZE 10
int NAVEGATOR_SELECT = 1;
static int logging = 0;
#define BROTHER_IMP 1
#define SAMSUNG_IMP 2
#define PDF_IMP 3
#define HTML_IMP 4

GtkWidget *print_janela;
int enviar_query(char *query);
int autologger(char *string);
GtkWidget *msg_abrir_orc_window;
static GtkWidget *imp_botao_radio1,*imp_botao_radio2,*imp_botao_radio3,*imp_botao_radio4;

static int imp_opc=0;

static MYSQL conectar;
MYSQL_RES *vetor;
static int primeira_conexao=0;

void encerrando()
{
	char *enc_infos;
	enc_infos = malloc(MAX_LOG_DESC);
	//enviar aqui todas informacoes importantes para o banco
	sprintf(enc_infos,"Finalizando aplicacao");
	autologger(enc_infos);


	gtk_main_quit();
	return ;
}


int close_window_callback(GtkWidget *widget,gpointer *ponteiro)
{
	if(ponteiro)
		if(GTK_IS_WIDGET(ponteiro))
			gtk_widget_destroy(GTK_WIDGET(ponteiro));
	return 0;
}

static void popup(GtkWidget *widget,gchar *string);

int iniciar_impressao(char *gerado)
{
	char *chamada;

	chamada = malloc(strlen(gerado)+strlen(COPY_PROG)+strlen(IMP_PORT1)+10);

	if(imp_opc==BROTHER_IMP){
		sprintf(chamada,"%s %s %s",COPY_PROG,gerado,IMP_PORT1);
	}

	if(imp_opc==SAMSUNG_IMP){
		sprintf(chamada,"%s %s %s",COPY_PROG,gerado,IMP_PORT2);
	}

	if(imp_opc==PDF_IMP){
		if(NAVEGATOR_SELECT == 1)
			sprintf(chamada,"%s %s",CHROME_PATH,gerado);
		if(NAVEGATOR_SELECT == 2)
			sprintf(chamada,"%s %s",FIREFOX_PATH,gerado);
	}

	if(imp_opc==HTML_IMP){
		if(NAVEGATOR_SELECT == 1)
			sprintf(chamada,"%s %s.html",CHROME_PATH,gerado);
		if(NAVEGATOR_SELECT == 2)
			sprintf(chamada,"%s %s.html",FIREFOX_PATH,gerado);
	}

	#ifdef WIN32
	STARTUPINFO infoBina={sizeof(infoBina)};
	PROCESS_INFORMATION processInfoBina;
	infoBina.dwFlags = STARTF_USESHOWWINDOW;
	infoBina.wShowWindow = SW_HIDE;
	if (CreateProcess(NULL, chamada, NULL, NULL, FALSE, 0, NULL, NULL, &infoBina, &processInfoBina))
    {
		popup(NULL,"Documento enviado para impressão");
		WaitForSingleObject(processInfoBina.hProcess, INFINITE);
		CloseHandle(processInfoBina.hProcess);
		CloseHandle(processInfoBina.hThread);
	}else{
		popup(NULL,"Algum erro ocorreu ao enviar o arquivo");
	}
	#endif

	#ifdef __linux__
	GError *erro=NULL;
	GSubprocess *processo=NULL;

	if(PDF_IMP||HTML_IMP){
		if(NAVEGATOR_SELECT == 1)
			processo = g_subprocess_new(G_SUBPROCESS_FLAGS_STDOUT_SILENCE,&erro,CHROME_PATH,gerado,NULL);
		if(NAVEGATOR_SELECT == 2)
			processo = g_subprocess_new(G_SUBPROCESS_FLAGS_STDOUT_SILENCE,&erro,FIREFOX_PATH,gerado,NULL);
	}

	if(processo==NULL)
	{
		if(erro)
			autologger((char*)erro->message);
		popup(NULL,"Não foi possivel gerar documento");
		return 1;
	}

	#endif
	close_window_callback(NULL,(gpointer)print_janela);

	return 0;
}

int desenhar_pdf(char *gerando_file)
{
	char *gerado, *chamada;

	chamada = malloc(strlen(PDF_GEN)+strlen(gerando_file)*2+10);

	gerado = malloc(strlen(gerando_file)+1);

	sprintf(gerado,"%s",gerando_file);

	if(strlen(gerado)>5)
		gerado[strlen(gerado)-5] = '\0';

	sprintf(chamada,"%s %s %s.pdf",PDF_GEN,gerando_file,gerado);

	#ifdef WIN32
	STARTUPINFO infoBina={sizeof(infoBina)};
	PROCESS_INFORMATION processInfoBina;
	infoBina.dwFlags = STARTF_USESHOWWINDOW;
	infoBina.wShowWindow = SW_HIDE;
	if (CreateProcess(NULL, chamada, NULL, NULL, FALSE, 0, NULL, NULL, &infoBina, &processInfoBina))
    {
		WaitForSingleObject(processInfoBina.hProcess, INFINITE);
		CloseHandle(processInfoBina.hProcess);
		CloseHandle(processInfoBina.hThread);
		sprintf(gerado,"%s.pdf",gerado);
		iniciar_impressao(gerado);
	}
	else
	{
		popup(NULL,"Não foi possivel gerar documento");
		return 1;
	}
	#endif
	#ifdef __linux__

	GError *erro;
	GSubprocess *processo = g_subprocess_new(G_SUBPROCESS_FLAGS_STDOUT_SILENCE,&erro,PDF_GEN,gerando_file,strcat(gerado,".pdf"),NULL);
	if(processo == NULL)
	{
		popup(NULL,"Não foi possivel gerar documento");
		autologger((char*)erro->message);
		return 1;
	}
	else{
		iniciar_impressao(gerado);
	}

	#endif
	return 0;
}

int iniciar_escolha(GtkWidget *widget , char *gerando_file)
{
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(imp_botao_radio1)))
	{
		imp_opc = BROTHER_IMP;
		desenhar_pdf(gerando_file);
	}
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(imp_botao_radio2)))
	{
		imp_opc = SAMSUNG_IMP;
		desenhar_pdf(gerando_file);
	}
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(imp_botao_radio3)))
	{
		imp_opc = PDF_IMP;
		desenhar_pdf(gerando_file);
	}
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(imp_botao_radio4)))
	{
		imp_opc = HTML_IMP;
		iniciar_impressao(gerando_file);
	}
	return 0;
}

int escolher_finalizacao(char *gerando_file)
{
	GtkWidget *botoes_frame,*botoes_caixa;

	GtkWidget *botao_confirma,*botao_cancela;
	GtkWidget *caixa_opcoes;

	GtkWidget *caixa_grande;

	print_janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(print_janela,400,400);
	gtk_window_set_position(GTK_WINDOW(print_janela),3);
	gtk_window_set_keep_above(GTK_WINDOW(print_janela),TRUE);

	botoes_caixa = gtk_box_new(1,0);
	botoes_frame = gtk_frame_new("Escolha como finalizar:");

	caixa_grande = gtk_box_new(1,0);

	botao_confirma = gtk_button_new_with_label("Concluir");
	botao_cancela = gtk_button_new_with_label("Cancelar");
	caixa_opcoes = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),botao_confirma,0,0,50);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),botao_cancela,0,0,5);

	imp_botao_radio1 = gtk_radio_button_new_with_label(NULL,"Enviar para Impressora BROTHER");
	imp_botao_radio2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(imp_botao_radio1),"Enviar para Impressora SAMSUNG");

	imp_botao_radio3 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(imp_botao_radio2),"Abrir PDF");
	imp_botao_radio4 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(imp_botao_radio3),"Abrir HTML");

	gtk_box_pack_start(GTK_BOX(botoes_caixa),imp_botao_radio1,0,0,5);
	gtk_box_pack_start(GTK_BOX(botoes_caixa),imp_botao_radio2,0,0,5);
	gtk_box_pack_start(GTK_BOX(botoes_caixa),imp_botao_radio3,0,0,5);
	gtk_box_pack_start(GTK_BOX(botoes_caixa),imp_botao_radio4,0,0,5);

	gtk_container_add(GTK_CONTAINER(botoes_frame),botoes_caixa);

	gtk_box_pack_start(GTK_BOX(caixa_grande),botoes_frame,0,0,50);
	gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_opcoes,0,0,10);

	gtk_container_add(GTK_CONTAINER(print_janela),caixa_grande);
	g_signal_connect (botao_confirma,"clicked",G_CALLBACK(iniciar_escolha),gerando_file);
	g_signal_connect (botao_cancela,"clicked",G_CALLBACK(close_window_callback),print_janela);
	gtk_widget_show_all(print_janela);
	return 0;
}

char *randomizar_string()
{
    int i;
    char *res = malloc(RANDOM_STRING_SIZE + 1);
    srand(time( NULL ));
    for(i = 0; i < RANDOM_STRING_SIZE; i++) {
        res[i] = (char) (rand()%(122-97))+97;
    }
    res[i] = '\0';
    return res;
}


int autologger(char *string)
{
	char *string1, *string2,*unvulned_query;
	logging = 1;
	string1 = malloc(MAX_QUERY_LEN+strlen(string));
	string2 = malloc(MAX_QUERY_LEN+strlen(string));

	sprintf(string1,"%s\n",string);

	for(int cont=0;cont<strlen(string1);cont++)
		if(string1[cont] == '\n')
			string1[cont] = ' ';

	unvulned_query = malloc(strlen(string1));

	if(primeira_conexao!=0)
		mysql_real_escape_string(&conectar,unvulned_query,string1,strlen(string1));

	sprintf(string2,"insert into logs(descricao,data) values('%s',CURRENT_TIMESTAMP());",unvulned_query);

	if(strlen(string2)>MAX_LOG_DESC)
		string2[MAX_LOG_DESC] = '\0';

	if(enviar_query(string2)!=0)
		g_print("Log não pode ser enviado");

	logging = 0;
	return 0;
}

GtkWidget *popup_fechar;
static void popup(GtkWidget *widget,gchar *string)
{
	int len;
	GtkWidget *popup, *fields, *fixed, *box;
	int resultado;

	popup = gtk_dialog_new_with_buttons("Mensagem",NULL,4,"Ok",GTK_RESPONSE_ACCEPT,NULL);

	gtk_window_set_title(GTK_WINDOW(popup),"Mensagem");
	gtk_window_set_icon_name(GTK_WINDOW(popup),"user-availables");
	gtk_window_set_keep_above(GTK_WINDOW(popup),TRUE);

	if(logging == 0)
		autologger(string);

	gtk_window_set_position(GTK_WINDOW(popup),3);

	fields = gtk_bin_get_child(GTK_BIN(popup));
	fixed = gtk_fixed_new();
	box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(box),gtk_label_new(string),0,0,10);
	gtk_fixed_put(GTK_FIXED(fixed),box,30,0);

	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);

	gtk_widget_grab_focus(gtk_dialog_get_widget_for_response(GTK_DIALOG(popup),GTK_RESPONSE_ACCEPT));
	gtk_dialog_set_default_response(GTK_DIALOG(popup),GTK_RESPONSE_ACCEPT);
	gtk_widget_show_all(popup);

	resultado = gtk_dialog_run(GTK_DIALOG(popup));

	gtk_widget_destroy(popup);
	return ;
}

MYSQL_RES *consultar(char *query)
{
	int err=1;
	if(primeira_conexao==0)
	{
		if(!mysql_init(&conectar))
		{
			popup(NULL,"Não foi possivel conectar ao servidor");
			autologger((char*)mysql_error(&conectar));
			return NULL;
		}
		if(!mysql_real_connect(&conectar,SERVER,USER,PASS,DATABASE,0,NULL,0))
		{
			autologger((char*)mysql_error(&conectar));
			return NULL;
		}

		if (mysql_set_character_set(&conectar, "utf8"))
		{
			autologger("Erro ao setar caracter");
		}
		primeira_conexao=1;
	}

	err = mysql_query(&conectar,query);
	if(err!=0)
	{
		autologger((char*)mysql_error(&conectar));
		popup(NULL,"Erro de formato\n");
		primeira_conexao=0;
		return NULL;
	}

	vetor = mysql_store_result(&conectar);
	if(vetor==NULL)
	{
		autologger((char*)mysql_error(&conectar));
		popup(NULL,"Erro de formato\n");
		primeira_conexao=0;
		return NULL;
	}
	//mysql_close(&conectar);
	return vetor;
}

int enviar_query(char *query)
{
	int err=1;
	if(primeira_conexao==0)
	{
		if(!mysql_init(&conectar))
		{
			popup(NULL,"Não foi possivel conectar ao servidor");
			if(logging == 0){
				autologger("Não foi possivel conectar ao servidor");
				autologger((char*)mysql_error(&conectar));
			}
			primeira_conexao=0;
			return 1;
		}
		if(!mysql_real_connect(&conectar,SERVER,USER,PASS,DATABASE,0,NULL,0))
		{

			popup(NULL,"Não foi possivel conectar ao servidor");

			if(logging == 0){
				autologger("Não foi possivel conectar ao servidor");
				autologger((char*)mysql_error(&conectar));
			}
			primeira_conexao=0;
			return 1;
		}

		if (mysql_set_character_set(&conectar, "utf8"))
		{
			autologger("Não foi possivel setar novo caracter");
		}
	}

	err = mysql_query(&conectar,query);
	if(err!=0)
	{
		popup(NULL,"Erro de formato\n");
		if(logging == 0){
			autologger(query);
			autologger((char*)mysql_error(&conectar));
		}
		return 1;
	}
	return 0;
}

int tasker(char *table)
{
	char task[8];
	MYSQL connect;

	MYSQL_RES *result_vetor;
	MYSQL_ROW campos;

	int err=0,task_num=0;
	char query[QUERY_LEN];

	sprintf(query,"select MAX(code) from %s;",table);
	result_vetor = consultar(query);

	if(result_vetor == NULL)
	{
		popup(NULL,"Não foi possivel receber o id do servidor");
		return 1;
	}

	campos = mysql_fetch_row(result_vetor);
	if(campos==NULL)
	{
		return 1;
	}

	#ifdef __linux__
	sprintf(task,"%s",campos[0]);
	task_num = stoi(task);
	#endif
	#ifdef WIN32
	task_num = stoi(campos[0]);
	#endif

	if(task_num==-1)
	{
		return 1;
	}
	return (task_num+1);
}

char *infos(int pos)
{
	char *info[] = {"Razao","Endereco","CNPJ"};
	char *retorno;
	char *requisicao;
	requisicao = malloc(strlen("select razao,endereco,cnpj from empresa;"));
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	requisicao = "select razao,endereco,cnpj from empresa;";

	vetor = consultar(requisicao);

	if(vetor==NULL)
	{
		popup(NULL,"Erro ao receber dados da empresa");
		return "";
	}

	if((campos = mysql_fetch_row(vetor))==NULL)
	{
		autologger("Informacao de desktop não encontrada\n");
		return "";
	}

	retorno = malloc(62);

	if(strlen(campos[pos])>=60)
	{
		campos[pos][60] = '.';
		campos[pos][61] = '\0';
	}

	sprintf(retorno,"%s",campos[pos]);

	return retorno;
}
