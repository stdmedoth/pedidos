gboolean progress_bar_check(){
	if(!global_progress_bar_active){
		if(global_progress_bar_active_changed){
			carregar_interface();
		}
		global_progress_bar_active_changed = global_progress_bar_active;
		gtk_widget_hide(global_progress_bar_window);
		return G_SOURCE_CONTINUE;
	}

	if(global_progress_bar_text){
			gtk_progress_bar_set_text(GTK_PROGRESS_BAR(global_progress_bar_widget), global_progress_bar_text);
	}else{
		gtk_progress_bar_set_text(GTK_PROGRESS_BAR(global_progress_bar_widget), GLOBAL_PROGRESS_BAR_DEFAULT_TXT);
	}

	double progress = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(global_progress_bar_widget));
	if( progress >= 1){
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(global_progress_bar_widget), 0);
	}else{
		progress += 0.3;
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(global_progress_bar_widget), progress);
	}

	if(!global_progress_bar_active_changed){
		carregar_interface();
	}

	global_progress_bar_active_changed = global_progress_bar_active;
	gtk_widget_show_all(global_progress_bar_window);

	return G_SOURCE_CONTINUE;
}

void progress_bar_init(){
	GtkWidget *box, *frame;
	global_progress_bar_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_deletable(GTK_WINDOW(global_progress_bar_window),FALSE);
	gtk_window_set_keep_above(GTK_WINDOW(global_progress_bar_window),TRUE);
	gtk_window_set_decorated(GTK_WINDOW(global_progress_bar_window),FALSE);
	gtk_window_set_position(GTK_WINDOW(global_progress_bar_window),3);
	gtk_widget_set_size_request(global_progress_bar_window, 50, 50);

	global_progress_bar_widget = gtk_progress_bar_new ();
	box = gtk_box_new(0,0);
	frame = gtk_frame_new("Carregando! aguarde");

	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(global_progress_bar_widget), GLOBAL_PROGRESS_BAR_DEFAULT_TXT);
	gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(global_progress_bar_widget), TRUE);

	g_timeout_add (350, progress_bar_check, NULL);

	gtk_box_pack_start(GTK_BOX(box),global_progress_bar_widget,0,0,0);
	gtk_container_add(GTK_CONTAINER(frame), box);
	gtk_container_add(GTK_CONTAINER(global_progress_bar_window), frame);
	gtk_widget_show_all(global_progress_bar_window);
}

void popup(GtkWidget *widget,gchar *string){
	int len;
	GtkWidget *popup, *fields, *fixed, *box;
	int resultado;

	popup = gtk_dialog_new_with_buttons("Mensagem",NULL,4,"Ok",GTK_RESPONSE_ACCEPT,NULL);

	gtk_window_set_title(GTK_WINDOW(popup),"Mensagem");
	gtk_window_set_icon_name(GTK_WINDOW(popup),"user-availables");

	if(widget)
		gtk_window_set_transient_for(GTK_WINDOW(popup),GTK_WINDOW(widget));
	gtk_window_set_keep_above(GTK_WINDOW(popup),TRUE);
	gtk_window_set_position(GTK_WINDOW(popup),3);

	if(logging == 0)
		autologger(string);

	fields = gtk_bin_get_child(GTK_BIN(popup));
	fixed = gtk_fixed_new();
	box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(box),gtk_label_new(string),0,0,30);
	gtk_fixed_put(GTK_FIXED(fixed),box,30,0);

	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);

	gtk_widget_grab_focus(gtk_dialog_get_widget_for_response(GTK_DIALOG(popup),GTK_RESPONSE_ACCEPT));
	gtk_dialog_set_default_response(GTK_DIALOG(popup),GTK_RESPONSE_ACCEPT);
	gtk_widget_show_all(popup);

	resultado = gtk_dialog_run(GTK_DIALOG(popup));

	if(popup)
		gtk_widget_destroy(popup);
	return ;
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
	gtk_window_set_modal(GTK_WINDOW(popup),TRUE);
	gtk_window_set_position(GTK_WINDOW(popup),3);
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
      email_copia = malloc(strlen(SEM_EMAIL)+1);
      strcpy(email_copia, SEM_EMAIL);
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

char *get_text_from_input(char *text, GtkWidget *parent_wnd){
	GtkWidget *janela, *fields, *fixed, *box;
	gchar *answer1, *answer2;
	int resultado;
	GtkWidget *answer_entry = gtk_entry_new();
	GtkWidget *answer_frame = gtk_frame_new("Preencha");

	janela = gtk_dialog_new_with_buttons(text,NULL,4,"Confirmar",GTK_RESPONSE_ACCEPT,NULL);
	if(parent_wnd)
		gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(parent_wnd));
	else
		gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janelas_gerenciadas.principal.janela_pointer));
	gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
	gtk_window_set_position(GTK_WINDOW(janela),3);

	GtkWidget *confirma_button = gtk_dialog_get_widget_for_response(GTK_DIALOG(janela),GTK_RESPONSE_ACCEPT);

	fields = gtk_bin_get_child(GTK_BIN(janela));
	fixed = gtk_fixed_new();
	box = gtk_box_new(0,0);

	gtk_container_add(GTK_CONTAINER(answer_frame), answer_entry);
	gtk_box_pack_start(GTK_BOX(box),answer_frame,0,0,10);
	gtk_fixed_put(GTK_FIXED(fixed),box,30,0);
	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);

	gtk_dialog_set_default_response(GTK_DIALOG(janela),GTK_RESPONSE_ACCEPT);
	gtk_widget_show_all(janela);

	g_signal_connect(answer_entry, "activate", G_CALLBACK(click_button_callback), confirma_button );

	resultado = gtk_dialog_run(GTK_DIALOG(janela));
	switch (resultado) {
		case GTK_RESPONSE_ACCEPT:
			answer1 = (gchar *)gtk_entry_get_text(GTK_ENTRY(answer_entry));
			if(!strlen(answer1)){
				gtk_widget_destroy(janela);
				return NULL;
			}
			answer2 = strdup(answer1);
	}
	gtk_widget_destroy(janela);
	return answer2;
}

gboolean get_gestor_perm(GtkWidget *button, GtkWidget *parent_wnd){

	int len;
	GtkWidget *janela, *fields, *fixed, *box;
	int resultado;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	gchar *user;
	gchar *pass;

	janela = gtk_dialog_new_with_buttons("Insira a senha para confirmar permissões",NULL,4,"Confirmar Usuário",GTK_RESPONSE_ACCEPT,NULL);

	gtk_window_set_title(GTK_WINDOW(janela),"Permissão Gerência");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"user-availables");

	if(parent_wnd)
		gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(parent_wnd));
	else
		gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
	gtk_window_set_position(GTK_WINDOW(janela),3);

	GtkWidget *user_entry = gtk_entry_new();
	GtkWidget *user_frame = gtk_frame_new("Usuário");
	gtk_container_add(GTK_CONTAINER(user_frame), user_entry);
	GtkWidget *pass_entry = gtk_entry_new();
	GtkWidget *pass_frame = gtk_frame_new("Senha");
	gtk_container_add(GTK_CONTAINER(pass_frame), pass_entry);

	GtkWidget *confirma_button = gtk_dialog_get_widget_for_response(GTK_DIALOG(janela),GTK_RESPONSE_ACCEPT);
	g_signal_connect(user_entry, "activate", G_CALLBACK(passar_campo), pass_entry );
	g_signal_connect(pass_entry, "activate", G_CALLBACK(passar_campo), confirma_button );

	fields = gtk_bin_get_child(GTK_BIN(janela));
	fixed = gtk_fixed_new();
	box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(box),user_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(box),pass_frame,0,0,10);

	gtk_fixed_put(GTK_FIXED(fixed),box,30,0);

	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);

	gtk_dialog_set_default_response(GTK_DIALOG(janela),GTK_RESPONSE_ACCEPT);
	gtk_widget_show_all(janela);

	resultado = gtk_dialog_run(GTK_DIALOG(janela));
	switch (resultado) {
		case GTK_RESPONSE_ACCEPT:
			user = (gchar *)gtk_entry_get_text(GTK_ENTRY(user_entry));
			if(!strlen(user)){
				popup(NULL,"Usuário não inserido");
				break;
			}
			pass = (gchar *)gtk_entry_get_text(GTK_ENTRY(pass_entry));
			if(!strlen(pass)){
				pass = strdup("");
			}
			char unvulned_nome[MAX_OPER_LEN];
			char unvulned_senha[MAX_SEN_LEN];
			mysql_real_escape_string(&conectar,unvulned_nome, user,strlen(user));
			mysql_real_escape_string(&conectar,unvulned_senha, pass,strlen(pass));


			enum{
				CODE,
				NOME,
				NIVEL
			};
			sprintf(query,"select code,nome,nivel from operadores where nome = '%s' and senha = MD5('%s');",unvulned_nome,unvulned_senha);
			if(!(res = consultar(query))){
				popup(janela_login,"Erro de comunicacao com banco");
				return 1;
			}

			if((row = mysql_fetch_row(res))){
				gtk_widget_destroy(janela);
				if(atoi(row[NIVEL]) < NIVEL_GERENCIAL){
					popup(NULL,"Sem permissão");
					return 0;
				}
				return 1;
			}else{
				popup(janela,"Usuário ou Senha incorretos");
			}
	}

	gtk_widget_destroy(janela);
	return 0;
}
