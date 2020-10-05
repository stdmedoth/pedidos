#define QUERY_LEN 1000
#define RANDOM_STRING_SIZE 10
static int logging = 0;
static int erro_logger=0;

GtkWidget *print_janela;

GtkWidget *msg_abrir_orc_window;

static MYSQL conectar;
MYSQL_RES *vetor;
static int primeira_conexao=0;

void doc_gerar_header(FILE *file, char *title){
  if(!file)
    return ;
  fprintf(file,"<!DOCTYPE html>\n");
  fprintf(file,"<html>\n");
  fprintf(file,"<head>\n");
  fprintf(file,"<meta charset=\"utf-8\"/>");
  fprintf(file,"<link href=\"%s\" rel=\"stylesheet\">\n",CSS_ORC);
  fprintf(file,"<title>%s</title>\n",title);

  fprintf(file,"<div id=\"div-titulo\">\n");
  fprintf(file,"<img id=\"logo-img\" src=\"%s\" \n",IMG_IMP_LOGO);
  fprintf(file,"</div>\n");
  fprintf(file,"</head>\n");
  fprintf(file,"<div id=\"caixa-imp\">\n");
  return ;
}



char  *string_to_int(char *string){
  int cont2=0;
  char *formated_string = malloc(strlen(string));
  strcpy(formated_string,"");

  for(int cont=0;cont<strlen(string);cont++){
    if(isdigit(string[cont])){
      formated_string[cont2] = string[cont];
      cont2++;
    }
  }
  formated_string[cont2] = '\0';
  return formated_string;
}

char *status_tit_str(int status){

  switch (status) {
    case STAT_QUITADO:
      return "Baixado";
    case STAT_PARC_BAIXA:
      return "Baixado Parcialmente";
    case STAT_PENDENTE:
      return "Pendente";
  }

  return "Sem Status Definido";
}

char *formatar_data(char *data){
	int dia=0,mes=0,ano=0;
	int formats_qnt=4;
	//160820

	char *format = string_to_int(data);

	//provaveis formatos de data

	char *formats[] = {"%2d%2d%4d",
                    "%2d%2d%2d",
                    "%1d%1d%4d",
                    "%1d%1d%2d",
                    "%d/%d/%d"};
	if(!data)
		return NULL;

	for(int cont=0;cont<formats_qnt;cont++){
			if(sscanf(format,formats[cont],&dia,&mes,&ano)==3){
        if(ano<2000)
          ano += 2000;
				GTimeZone *tz = g_time_zone_new(NULL);
				GDateTime *gdatetime = g_date_time_new(tz,ano,mes,dia,0,0,0);
				if(!gdatetime){
					if(cont>=formats_qnt){
						popup(NULL,"Data incorreta");
						return NULL;
					}
				}
				else
					return g_date_time_format(gdatetime,"%d/%m/%Y");
			}
	}
	popup(NULL,"Formato não encontrado");
	return NULL;
}

gpointer carregando_wnd(){
	GtkWidget *janela = gtk_window_new(GTK_WINDOW_POPUP);
	GtkWidget *loading_gif = gtk_image_new_from_file(LOADING_GIF);
	GtkWidget *fixed = gtk_fixed_new();

  gtk_window_set_deletable(GTK_WINDOW(janela),TRUE);
  gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_modal(GTK_WINDOW(janela),TRUE);
	gtk_widget_set_size_request(janela,50,50);
	gtk_widget_set_size_request(loading_gif,50,50);
	gtk_fixed_put(GTK_FIXED(fixed),loading_gif,0,0);
	gtk_container_add(GTK_CONTAINER(janela),fixed);

	while (g_main_context_pending(NULL))
		g_main_context_iteration(NULL,FALSE);

	gtk_widget_show_all(janela);
	return janela;
}

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
	int err;
	char query[MAX_QUERY_LEN];
	char *enc_infos;
	enc_infos = malloc(MAX_LOG_DESC);

	//enviar aqui todas informacoes importantes para o banco
	sprintf(query,"insert into wnd_logger(id_janela,nome_janela,estado,qnt_aberta,operador,tempo) values(%i,'%s',%i,%i,%i,NOW())",
  REG_CORRECT_FINAL,
  "Encerrando...",
  0,
  0,
  sessao_oper.code);
	err = mysql_query(&conectar,query);
	if(err!=0)
	{
		popup(NULL,"Não foi possivel salvar status da sessão\n");
		file_logger(query);
		file_logger((char*)mysql_error(&conectar));
	}

	//sprintf(enc_infos,"Finalizando aplicacao");

	//autologger(enc_infos);

	gtk_main_quit();
	return ;
}


int close_window_callback(GtkWidget *widget,gpointer *ponteiro){
	if(ponteiro)
		if(GTK_IS_WIDGET(ponteiro))
			gtk_widget_destroy(GTK_WIDGET(ponteiro));
	return 0;
}

char *randomizar_string(){

		int i;
    char *res = malloc(RANDOM_STRING_SIZE + 1);

    srand(time( NULL ));
    for(i = 0; i < RANDOM_STRING_SIZE; i++) {
        res[i] = (char) (rand()%(122-97))+97;
    }

    res[i] = '\0';
    return res;
}


int file_logger(char *string){
	FILE *logger;

	logger = fopen(LOGGER,"a+");

	if(logger)
		fprintf(logger,"%s\n",string);
	else{
    if(erro_logger>=2)
      exit(1);

    erro_logger++;
		popup(NULL,"Não foi possivel atualizar logs, verifique com suporte");
		return 1;
	}
  erro_logger=0;
	fclose(logger);
	return 0;
}

int autologger(char *string)
{
	char *string1, *string2,*unvulned_query;
	logging = 1;
	string1 = malloc(MAX_QUERY_LEN+strlen(string));
	string2 = malloc(MAX_QUERY_LEN+strlen(string));

	sprintf(string1,"%s",string);
/*
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
*/
  file_logger(string1);
//	file_logger(string2);

	logging = 0;
	return 0;
}

static void popup(GtkWidget *widget,gchar *string){
	int len;
	GtkWidget *popup, *fields, *fixed, *box;
	int resultado;

	popup = gtk_dialog_new_with_buttons("Mensagem",NULL,4,"Ok",GTK_RESPONSE_ACCEPT,NULL);

	gtk_window_set_title(GTK_WINDOW(popup),"Mensagem");
	gtk_window_set_icon_name(GTK_WINDOW(popup),"user-availables");

  if((widget && GTK_IS_WIDGET(widget)))
    gtk_window_set_transient_for(GTK_WINDOW(widget),GTK_WINDOW(popup));
  else
    gtk_window_set_keep_above(GTK_WINDOW(popup),TRUE);

  gtk_window_set_position(GTK_WINDOW(popup),GTK_WIN_POS_CENTER_ALWAYS);
  //gtk_window_set_modal(GTK_WINDOW(popup),TRUE);

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

MYSQL_RES *consultar(char *query){
	int err=1;
	FILE *backup_query;
	backup_query = fopen(BACKUP_QUERY_FILE,"+a");

	if(primeira_conexao==0)
	{
		if(!mysql_init(&conectar))
		{
			popup(NULL,"Não foi possivel conectar ao servidor");
			autologger((char*)mysql_error(&conectar));
			return NULL;
		}

		if(!mysql_real_connect(&conectar,server_confs.server_endereco,server_confs.server_user,server_confs.server_senha,server_confs.server_database,0,NULL,0))
		{
      popup(NULL,"Não foi possível conectar ao servidor");
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
		file_logger((char*)mysql_error(&conectar));
		file_logger(query);
		autologger((char*)mysql_error(&conectar));
		autologger(query);
		popup(NULL,"Erro de formato\n");
		primeira_conexao=0;
		return NULL;
	}

	vetor = mysql_store_result(&conectar);
	if(vetor==NULL)
	{
		file_logger((char*)mysql_error(&conectar));
		file_logger(query);
		autologger((char*)mysql_error(&conectar));
		autologger(query);
		popup(NULL,"Erro de formato\n");
		primeira_conexao=0;
		return NULL;
	}

	if(backup_query){
		fprintf(backup_query,"%s\n",query);
		fclose(backup_query);
	}
	return vetor;
}

int enviar_query(char *query){
	FILE *backup_query;
	backup_query = fopen(BACKUP_QUERY_FILE,"a+");

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
		if(!mysql_real_connect(&conectar,server_confs.server_endereco,server_confs.server_user,server_confs.server_senha,server_confs.server_database,0,NULL,0))
		{
			popup(NULL,"Não foi possivel conectar ao servidor");
      file_logger((char*)mysql_error(&conectar));
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
		primeira_conexao=1;
	}

	#ifdef QUERY_DEBUG
	g_print("%s\n",query);
	#endif

	err = mysql_query(&conectar,query);
	if(err!=0)
	{
    //popup(NULL,(char*)mysql_error(&conectar));
    file_logger((char*)mysql_error(&conectar));
		popup(NULL,"Erro de formato\n");
		if(logging == 0){
      autologger(query);
			autologger((char*)mysql_error(&conectar));
		}
		return err;
	}

	if(backup_query){
		fprintf(backup_query,"%s\n",query);
		fclose(backup_query);
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

	if(campos[0])
		task_num = atoi(campos[0]);

	if(task_num==-1)
	{
		return 1;
	}
	return (task_num+1);
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
							orcamentos.criticar.prod_movimento = 1;
							break;
						case 1:
							orcamentos.criticar.prod_saldo = 1;
							break;
						case 2:
							orcamentos.criticar.prod_saldo_limite = 1;
							break;
						case 3:
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
static char **tipo_ter_list;

char *tipo_ter_num_to_str(int num){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	int cont=1;
	tipo_ter_list = malloc(MAX_TIPOS_TER*MAX_TIPO_TER);

	if(!tipo_ter_load){
			sprintf(query,"select nome from tipo_terceiros order by code");
			if(!(res = consultar(query))){
				popup(NULL,"Erro ao consultar tipo de terceiro");
				tipo_ter_load = 0;
				return NULL;
			}
			while((row = mysql_fetch_row(res))){
				tipo_ter_list[cont] = malloc(MAX_TIPO_TER);
				strcpy(tipo_ter_list[cont],row[0]);
				if(cont>=MAX_TIPOS_TER){
					popup(NULL,"Tipos de terceiros excedeu limite");
					return NULL;
				}
				cont++;
			}
			tipo_ter_load=1;
	}

	g_print("valor numerico '%i' '%s'\n",num, tipo_ter_list[num]);
	return tipo_ter_list[num];
}

void reportar_encerramento_brusco(){

	int len;
	GtkWidget *popup, *fields, *fixed, *box;
	int resultado;

	popup = gtk_dialog_new_with_buttons("Mensagem",NULL,GTK_DIALOG_MODAL,"Ok, Eu gostaria",GTK_RESPONSE_ACCEPT,"Talvez, mais tarde",GTK_RESPONSE_REJECT,NULL);

	gtk_window_set_title(GTK_WINDOW(popup),"Mensagem");
	gtk_window_set_icon_name(GTK_WINDOW(popup),"user-availables");
	gtk_window_set_keep_above(GTK_WINDOW(popup),TRUE);

	gtk_window_set_position(GTK_WINDOW(popup),3);

	fields = gtk_bin_get_child(GTK_BIN(popup));
	fixed = gtk_fixed_new();
	box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(box),gtk_label_new("O sistema teve um encerramento brusco, gostaria de reportar?\nAssim a solução do problema será mais rápida"),0,0,10);
	gtk_fixed_put(GTK_FIXED(fixed),box,30,0);

	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);

	gtk_widget_grab_focus(gtk_dialog_get_widget_for_response(GTK_DIALOG(popup),GTK_RESPONSE_ACCEPT));
	gtk_dialog_set_default_response(GTK_DIALOG(popup),GTK_RESPONSE_ACCEPT);
	gtk_widget_show_all(popup);

	resultado = gtk_dialog_run(GTK_DIALOG(popup));
	if(resultado == GTK_RESPONSE_ACCEPT){
		suporte_princ_wnd();
	}

	gtk_widget_destroy(popup);
}

int cep_nao_existente_fun(gchar *cep){

	int len;
	GtkWidget *popup, *fields, *fixed, *box;
	int resultado;

	popup = gtk_dialog_new_with_buttons("Mensagem",NULL,GTK_DIALOG_MODAL,"Desejo cadastrar",GTK_RESPONSE_ACCEPT,"Apenas preencher os campos",GTK_RESPONSE_REJECT,NULL);

	gtk_window_set_title(GTK_WINDOW(popup),"Mensagem");
	gtk_window_set_icon_name(GTK_WINDOW(popup),"user-availables");
	gtk_window_set_keep_above(GTK_WINDOW(popup),TRUE);

	gtk_window_set_position(GTK_WINDOW(popup),3);

	fields = gtk_bin_get_child(GTK_BIN(popup));
	fixed = gtk_fixed_new();
	box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(box),gtk_label_new("O Cep não foi cadastrado deseja cadastrar?\n"),0,0,10);
	gtk_fixed_put(GTK_FIXED(fixed),box,30,0);

	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);

	gtk_widget_grab_focus(gtk_dialog_get_widget_for_response(GTK_DIALOG(popup),GTK_RESPONSE_ACCEPT));
	gtk_dialog_set_default_response(GTK_DIALOG(popup),GTK_RESPONSE_ACCEPT);
	gtk_widget_show_all(popup);

	resultado = gtk_dialog_run(GTK_DIALOG(popup));
	if(resultado == GTK_RESPONSE_ACCEPT){
		if(cad_cep())
      return 1;
    gtk_entry_set_text(GTK_ENTRY(cad_ceps_cep_entry),cep);
    gtk_widget_grab_focus(cad_ceps_descr_entry);
	}

	gtk_widget_destroy(popup);
  return 0;
}

int aviso_de_baixa_fin(){

	int len;
	GtkWidget *popup, *fields, *fixed, *box;
	int resultado;

	popup = gtk_dialog_new_with_buttons("Mensagem",NULL,GTK_DIALOG_MODAL,"Apagar baixas e cancelar pedido",GTK_RESPONSE_ACCEPT,"Manter baixas e pedido emitido",GTK_RESPONSE_REJECT,NULL);

	gtk_window_set_title(GTK_WINDOW(popup),"Mensagem");
	gtk_window_set_icon_name(GTK_WINDOW(popup),"user-availables");
	gtk_window_set_keep_above(GTK_WINDOW(popup),TRUE);

	gtk_window_set_position(GTK_WINDOW(popup),3);

	fields = gtk_bin_get_child(GTK_BIN(popup));
	fixed = gtk_fixed_new();
	box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(box),gtk_label_new("Parcelas do pedido possui baixas, deseja continuar?\n"),0,0,10);
	gtk_fixed_put(GTK_FIXED(fixed),box,20,20);

	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);

	gtk_widget_grab_focus(gtk_dialog_get_widget_for_response(GTK_DIALOG(popup),GTK_RESPONSE_ACCEPT));
	gtk_dialog_set_default_response(GTK_DIALOG(popup),GTK_RESPONSE_ACCEPT);
	gtk_widget_show_all(popup);

	resultado = gtk_dialog_run(GTK_DIALOG(popup));
	if(resultado == GTK_RESPONSE_ACCEPT){
    gtk_widget_destroy(popup);
    return 0;
	}
  gtk_widget_destroy(popup);
  return 1;
}


int PopupBinario(char *mensagem, char *positivo, char *negativo){

	int len;
	GtkWidget *popup, *fields, *fixed, *box;
	int resultado;

	popup = gtk_dialog_new_with_buttons("Mensagem",NULL,GTK_DIALOG_MODAL,positivo,GTK_RESPONSE_ACCEPT,negativo,GTK_RESPONSE_REJECT,NULL);

	gtk_window_set_title(GTK_WINDOW(popup),"Mensagem");
	gtk_window_set_icon_name(GTK_WINDOW(popup),"user-availables");
	gtk_window_set_keep_above(GTK_WINDOW(popup),TRUE);

	gtk_window_set_position(GTK_WINDOW(popup),3);

	fields = gtk_bin_get_child(GTK_BIN(popup));
	fixed = gtk_fixed_new();
	box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(box),gtk_label_new(mensagem),0,0,10);
	gtk_fixed_put(GTK_FIXED(fixed),box,20,20);

	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);

	gtk_widget_grab_focus(gtk_dialog_get_widget_for_response(GTK_DIALOG(popup),GTK_RESPONSE_ACCEPT));
	gtk_dialog_set_default_response(GTK_DIALOG(popup),GTK_RESPONSE_ACCEPT);
	gtk_widget_show_all(popup);

	resultado = gtk_dialog_run(GTK_DIALOG(popup));
	if(resultado == GTK_RESPONSE_ACCEPT){
    gtk_widget_destroy(popup);
    return 1;
	}else{
    gtk_widget_destroy(popup);
    return 0;

  }
  return 0;
}


char *ped_status_from_int(int code){
	switch (code) {
		case 0:
			return "Pendente";

		case STATUS_PED_EMIT:
			return "Emitido";

		case STATUS_PED_CAN:
			return "Cancelado";
	}
	return "";
}

xmlNodePtr confirmar_envio_email(gchar *destino, gchar *conteudo){

	int len;
  GtkTextIter inicio,fim;
  GtkTextBuffer *buffer;
  gchar *infos_email, *corpo_email, *email_cli, *email_copia;
  GtkWidget *cli_entry, *copia_entry, *emailsbox;
	GtkWidget *janela, *fields, *fixed, *box;
	int resultado;

	janela = gtk_dialog_new_with_buttons("Mensagem",NULL,GTK_DIALOG_MODAL,"Enviar o email",GTK_RESPONSE_ACCEPT,"Não enviar",GTK_RESPONSE_REJECT,NULL);

	gtk_window_set_title(GTK_WINDOW(janela),"Mensagem");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"user-availables");
	gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
  gtk_widget_set_size_request(janela,100,100);
	gtk_window_set_position(GTK_WINDOW(janela),3);

  cli_entry = gtk_entry_new();
  copia_entry = gtk_entry_new();
	fields = gtk_bin_get_child(GTK_BIN(janela));
	fixed = gtk_fixed_new();
	box = gtk_box_new(1,0);
  emailsbox = gtk_box_new(0,0);

  gtk_box_pack_start(GTK_BOX(emailsbox),cli_entry,0,0,10);
  gtk_box_pack_start(GTK_BOX(emailsbox),copia_entry,0,0,10);

  GtkWidget *textview = gtk_text_view_new();
  buffer = GTK_TEXT_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview)));
  gtk_widget_set_size_request(textview,100,100);
  gtk_text_buffer_set_text(buffer,conteudo,strlen(conteudo));
  gtk_box_pack_start(GTK_BOX(box),emailsbox,0,0,10);
  gtk_box_pack_start(GTK_BOX(box),textview,0,0,10);
	gtk_fixed_put(GTK_FIXED(fixed),box,30,0);

	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);

	gtk_widget_grab_focus(gtk_dialog_get_widget_for_response(GTK_DIALOG(janela),GTK_RESPONSE_ACCEPT));
	gtk_dialog_set_default_response(GTK_DIALOG(janela),GTK_RESPONSE_ACCEPT);

  gtk_entry_set_text(GTK_ENTRY(cli_entry),destino);

	gtk_widget_show_all(janela);

	resultado = gtk_dialog_run(GTK_DIALOG(janela));
	if(resultado == GTK_RESPONSE_ACCEPT){

    email_cli =(gchar*) gtk_entry_get_text(GTK_ENTRY(cli_entry));
    if(!strlen(email_cli)){
      popup(NULL,"Insira o email do cliente");
      return NULL;
    }else
    if(strlen(email_cli)>MAX_EMAIL_LEN){
      popup(NULL,"Email muito grande");
      return NULL;
    }

    email_copia = (gchar*)  gtk_entry_get_text(GTK_ENTRY(copia_entry));
    if(!strlen(email_copia)){
      email_copia = malloc(strlen(SEM_EMAIL));
      strcpy(email_copia,SEM_EMAIL);
    }else
    if(strlen(email_copia)>MAX_EMAIL_LEN){
      popup(NULL,"Email muito grande");
      return NULL;
    }

    gtk_text_buffer_get_bounds(buffer,&inicio,&fim);
    corpo_email = gtk_text_buffer_get_text(buffer,&inicio,&fim,TRUE);

    xmlNodePtr root = xmlNewNode(NULL,(const xmlChar *)"Email");
    xmlNodePtr email_cli_nd = xmlNewNode(NULL,(const xmlChar *)"cliente");
    xmlNodePtr email_copia_nd = xmlNewNode(NULL,(const xmlChar *)"copia");
    xmlNodePtr corpo_email_nd = xmlNewNode(NULL,(const xmlChar *)"corpo_email");

    if(email_cli)
      xmlNodeAddContent(email_cli_nd,(const xmlChar *)email_cli);
    if(email_copia)
      xmlNodeAddContent(email_copia_nd,(const xmlChar *)email_copia);
    if(corpo_email)
      xmlNodeAddContent(corpo_email_nd,(const xmlChar *)corpo_email);

    xmlAddChild(root,email_cli_nd);
    xmlAddChild(root,email_copia_nd);
    xmlAddChild(root,corpo_email_nd);

    gtk_widget_destroy(janela);
    return root;
	}else
  if(resultado == GTK_RESPONSE_REJECT){
    gtk_widget_destroy(janela);
    return NULL;
  }
	gtk_widget_destroy(janela);
  return NULL;
}
