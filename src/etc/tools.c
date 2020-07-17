#define QUERY_LEN 1000
#define RANDOM_STRING_SIZE 10
static int logging = 0;

#define IMP_PATH1 1
#define IMP_PATH2 2
#define IMP_PATH3 3

#define PDF_IMP 3
#define HTML_IMP 4

GtkWidget *print_janela;
int enviar_query(char *query);
int autologger(char *string);
GtkWidget *msg_abrir_orc_window;
static GtkWidget *imp_botao_radio1,*imp_botao_radio2,*imp_botao_radio3,*imp_botao_radio4, *imp_botao_radio5;
static int imps_qnt=0, navs_qnt=0;
static int imp_opc=0;

static MYSQL conectar;
MYSQL_RES *vetor;
static int primeira_conexao=0;

void receber_psq_code_space(GtkTreeView *treeview, GtkTreePath *path,  GtkTreeViewColumn *column, GtkWidget *window)
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	char *codigo;
	codigo = malloc(MAX_CODE_LEN);

	/*if(GTK_TREE_VIEW(button))
	{
		treeview = GTK_TREE_VIEW(button);
	}*/

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));
	if(!gtk_tree_selection_get_selected(selection, &model, &iter))
		return ;
	gtk_tree_model_get (model, &iter, 0, &codigo, -1);

	if(pesquisa_global_alvo){
		gtk_entry_set_text(GTK_ENTRY(pesquisa_global_alvo),codigo);
		gtk_widget_activate(GTK_WIDGET(pesquisa_global_alvo));
	}

	gtk_widget_destroy(window);
}


void mover_scroll(GtkWidget *widget, GtkWidget *scroll_window){

	GtkAdjustment *ajuste = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scroll_window));
	gtk_adjustment_set_value(ajuste, gtk_adjustment_get_upper(ajuste));
	return ;

}

char *get_elem_from_path(char *path){
	char *new_path;
	new_path = malloc(strlen(path));
	int cont1=0;
	for(int cont2=0;cont2<=strlen(path);cont2++){
		new_path[cont1] = path[cont2];

		cont1++;

		if(path[cont2] == '\\'||path[cont2] == '/')
			cont1 = 0;
	}
	return new_path;

}

void get_filename_to_entry(GtkFileChooserButton *fchooser, GtkEntry *entry){
		gtk_entry_set_text(entry,gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fchooser)));
}

void encerrando()
{
	char *enc_infos;
	enc_infos = malloc(MAX_LOG_DESC);
	//enviar aqui todas informacoes importantes para o banco

	//sprintf(enc_infos,"Finalizando aplicacao");

	//autologger(enc_infos);

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

void carregar_navimps(){
	imps_qnt=0;
	navs_qnt=0;

	if(strlen(impressoras.imp_path1))
		imps_qnt++;

	if(strlen(impressoras.imp_path2))
		imps_qnt++;

	if(strlen(impressoras.imp_path3))
		imps_qnt++;

	if(strlen(navegadores.navegador_path1))
		navs_qnt++;

	if(strlen(navegadores.navegador_path1))
		navs_qnt++;
}

int iniciar_impressao(char *gerado)
{

	GError *erro=NULL;
	GSubprocess *processo=NULL;

	switch (imp_opc)
	{

		case IMP_PATH1:

			processo = g_subprocess_new(G_SUBPROCESS_FLAGS_STDOUT_SILENCE,&erro,COPY_PROG,gerado,impressoras.imp_path1,NULL);

			if(!processo)
			{
				popup(NULL,"Não foi possivel enviar documento");
				autologger(erro->message);
				return 1;
			}
			break;

		case IMP_PATH2:

			processo = g_subprocess_new(G_SUBPROCESS_FLAGS_STDOUT_SILENCE,&erro,COPY_PROG,gerado,impressoras.imp_path2,NULL);

			if(!processo)
			{
				popup(NULL,"Não foi possivel enviar documento");
				autologger(erro->message);
				return 1;
			}
			break;

		case IMP_PATH3:

			processo = g_subprocess_new(G_SUBPROCESS_FLAGS_STDOUT_SILENCE,&erro,COPY_PROG,gerado,impressoras.imp_path3,NULL);

			if(!processo)
			{
				popup(NULL,"Não foi possivel enviar documento");
				autologger(erro->message);
				return 1;
			}
			break;
	}

	if(imp_opc == PDF_IMP || imp_opc == HTML_IMP){

		GError *erro=NULL;
		GSubprocess *processo=NULL;

		if(navegadores.navegador_pdr == 1)
			processo = g_subprocess_new(G_SUBPROCESS_FLAGS_STDOUT_SILENCE,&erro,navegadores.navegador_path1,gerado,NULL);

		if(navegadores.navegador_pdr == 2)
			processo = g_subprocess_new(G_SUBPROCESS_FLAGS_STDOUT_SILENCE,&erro,navegadores.navegador_path2,gerado,NULL);

		if(!processo)
		{
			popup(NULL,"Não foi possivel abrir documento");
			autologger(erro->message);
			return 1;
		}
	}

	return 0;
}

int desenhar_pdf(char *gerando_file)
{
	char *gerado;

	gerado = malloc(strlen(gerando_file)+10);

	sprintf(gerado,"%s",gerando_file);

	if(strlen(gerado)>5)
		gerado[strlen(gerado)-5] = '\0';

	GError *erro=NULL;
	GSubprocess *processo = g_subprocess_new(G_SUBPROCESS_FLAGS_STDOUT_SILENCE,&erro,PDF_GEN,gerando_file,strcat(gerado,".pdf"),NULL);

	if(!processo)
	{
		popup(NULL,"Não foi possivel gerar documento");
		autologger(erro->message);
		return 1;
	}
	else{
		iniciar_impressao(gerado);
	}

	return 0;
}

int iniciar_escolha(GtkWidget *widget , char *gerando_file)
{
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(imp_botao_radio1)))
	{
		imp_opc = IMP_PATH1;
		if(desenhar_pdf(gerando_file))
			return 1;
	}

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(imp_botao_radio2)))
	{
		imp_opc = IMP_PATH2;
		if(desenhar_pdf(gerando_file))
			return 1;
	}

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(imp_botao_radio3)))
	{
		imp_opc = IMP_PATH3;
		if(desenhar_pdf(gerando_file))
			return 1;
	}

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(imp_botao_radio4)))
	{
		imp_opc = PDF_IMP;
		if(desenhar_pdf(gerando_file))
			return 1;
	}
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(imp_botao_radio5)))
	{
		imp_opc = HTML_IMP;
		if(iniciar_impressao(gerando_file))
			return 1;
	}

	close_window_callback(NULL,(gpointer)print_janela);
	return 0;
}

int escolher_finalizacao(char *gerando_file)
{
	GtkWidget *botoes_frame,*botoes_caixa;

	GtkWidget *botao_confirma,*botao_cancela;
	GtkWidget *caixa_opcoes;

	GtkWidget *caixa_grande;
	char *imp1_name, *imp2_name, *imp3_name;
	imp1_name = malloc(MAX_PATH_LEN+20);
	imp2_name = malloc(MAX_PATH_LEN+20);
	imp3_name = malloc(MAX_PATH_LEN+20);

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

	if(!imps_qnt && !navs_qnt){
		popup(NULL,"Não há impressoras ou navegadores configurados!");
		return 1;
	}


	sprintf(imp1_name,"Enviar para %s",get_elem_from_path(impressoras.imp_path1));
	imp_botao_radio1 = gtk_radio_button_new_with_label(NULL,imp1_name);
	gtk_box_pack_start(GTK_BOX(botoes_caixa),imp_botao_radio1,0,0,5);
	sprintf(imp2_name,"Enviar para %s",get_elem_from_path(impressoras.imp_path2));
	imp_botao_radio2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(imp_botao_radio1),imp2_name);
	gtk_box_pack_start(GTK_BOX(botoes_caixa),imp_botao_radio2,0,0,5);
	sprintf(imp3_name,"Enviar para %s",get_elem_from_path(impressoras.imp_path3));
	imp_botao_radio3 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(imp_botao_radio2),imp3_name);
	gtk_box_pack_start(GTK_BOX(botoes_caixa),imp_botao_radio3,0,0,5);
	imp_botao_radio4 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(imp_botao_radio3),"Abrir PDF");
	imp_botao_radio5 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(imp_botao_radio4),"Abrir HTML");
	gtk_box_pack_start(GTK_BOX(botoes_caixa),imp_botao_radio4,0,0,5);
	gtk_box_pack_start(GTK_BOX(botoes_caixa),imp_botao_radio5,0,0,5);

	if(strlen(impressoras.imp_path1))
		gtk_widget_set_sensitive(imp_botao_radio1,TRUE);
		else
		gtk_widget_set_sensitive(imp_botao_radio1,FALSE);

	if(strlen(impressoras.imp_path2))
		gtk_widget_set_sensitive(imp_botao_radio2,TRUE);
		else
		gtk_widget_set_sensitive(imp_botao_radio2,FALSE);

	if(strlen(impressoras.imp_path3))
		gtk_widget_set_sensitive(imp_botao_radio3,TRUE);
		else
		gtk_widget_set_sensitive(imp_botao_radio3,FALSE);

	if(navs_qnt){
		gtk_widget_set_sensitive(imp_botao_radio4,TRUE);
		gtk_widget_set_sensitive(imp_botao_radio5,TRUE);
	}else{
		gtk_widget_set_sensitive(imp_botao_radio4,FALSE);
		gtk_widget_set_sensitive(imp_botao_radio5,FALSE);
	}

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

	sprintf(string1,"%s",string);

	for(int cont=0;cont<strlen(string1);cont++){
		if(string1[cont] == '\n')
			string1[cont] = ' ';
		if(string1[cont] == '\0' || string1[cont] == -1)
			break;
	}
	unvulned_query = malloc(strlen(string1)*2);

	if(primeira_conexao!=0)
		mysql_real_escape_string(&conectar,unvulned_query,string1,strlen(string1));

	sprintf(string2,"insert into logs(descricao,data) values('%s',CURRENT_TIMESTAMP());",unvulned_query);

	if(strlen(string2)>MAX_LOG_DESC)
		string2[MAX_LOG_DESC] = '\0';

	if(enviar_query(string2)!=0)
		g_print("Log não pode ser enviado\n%s\n",string2);

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
	#ifdef QUERY_DEBUG
	g_print("%s\n",query);
	#endif
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

	#ifdef QUERY_DEBUG
	g_print("%s\n",query);
	#endif
	err = mysql_query(&conectar,query);
	if(err!=0)
	{
		popup(NULL,"Erro de formato\n");
		if(logging == 0){
			autologger(query);
			autologger((char*)mysql_error(&conectar));
		}
		return err;
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

int configurar_parametros()
{
	int cont;
	char *query;
	query = malloc(MAX_QUERY_LEN);
	MYSQL_RES *res;
	MYSQL_ROW  row;
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
				}
			}
		}
	}

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
	strcpy(navegadores.navegador_path2,row[2]);
	navegadores.navegador_pdr = atoi(row[3]);

	strcpy(impressoras.imp_path1,row[4]);
	strcpy(impressoras.imp_path2,row[5]);
	strcpy(impressoras.imp_path3,row[6]);

	carregar_navimps();
	return 0;
}
