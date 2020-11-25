enum{
	IMP_PATH1,
	IMP_PATH2,
	IMP_PATH3,
	PDF_IMP,
	HTML_IMP
};

static GtkWidget *imp_botao_radio1,*imp_botao_radio2,*imp_botao_radio3,*imp_botao_radio4, *imp_botao_radio5;
static int imps_qnt=0, navs_qnt=0;
static int imp_opc=0;

void carregar_navimps(void){
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
	char chamada[strlen(COPY_PROG)+strlen(gerado)+MAX_PATH_LEN*2];
	GSubprocess *processo=NULL;
	GError *erro=NULL;

	while (g_main_context_pending(NULL))
		g_main_context_iteration(NULL,FALSE);

	switch (imp_opc)
	{

		case IMP_PATH1:
			sprintf(chamada,"%s %s %s",COPY_PROG,gerado,impressoras.imp_path1);
			g_print(chamada);
			processo = g_subprocess_new(G_SUBPROCESS_FLAGS_NONE,&erro,COPY_PROG,gerado,impressoras.imp_path1,NULL);
			if(!processo)
			{
				popup(NULL,"Não foi possivel enviar documento");
				autologger(erro->message);
				return 1;
			}
			break;

		case IMP_PATH2:
			sprintf(chamada,"%s %s %s",COPY_PROG,gerado,impressoras.imp_path2);
			g_print(chamada);
			processo = g_subprocess_new(G_SUBPROCESS_FLAGS_NONE,&erro,COPY_PROG,gerado,impressoras.imp_path2,NULL);
			if(!processo)
			{
				popup(NULL,"Não foi possivel enviar documento");
				autologger(erro->message);
				return 1;
			}
			break;

		case IMP_PATH3:
			sprintf(chamada,"%s %s %s",COPY_PROG,gerado,impressoras.imp_path3);
			g_print(chamada);
			processo = g_subprocess_new(G_SUBPROCESS_FLAGS_NONE,&erro,COPY_PROG,gerado,impressoras.imp_path3,NULL);
			if(!processo)
			{
				popup(NULL,"Não foi possivel enviar documento");
				autologger(erro->message);
				return 1;
			}
			break;
	}

	if(imp_opc == PDF_IMP || imp_opc == HTML_IMP){

		processo=NULL;
		erro=NULL;

		while (g_main_context_pending(NULL))
			g_main_context_iteration(NULL,FALSE);

		if(navegadores.navegador_pdr == 1){
			sprintf(chamada,"%s %s",navegadores.navegador_path1,gerado);
			g_print(chamada);
			processo = g_subprocess_new(G_SUBPROCESS_FLAGS_NONE,&erro,navegadores.navegador_path1,gerado,NULL);
		}
		if(navegadores.navegador_pdr == 2){
			sprintf(chamada,"%s %s",navegadores.navegador_path2,gerado);
			g_print(chamada);
			processo = g_subprocess_new(G_SUBPROCESS_FLAGS_NONE,&erro,navegadores.navegador_path2,gerado,NULL);
		}

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
	GError *erro=NULL;

	gerado = malloc(strlen(gerando_file)+10);

	sprintf(gerado,"%s",gerando_file);

	if(strlen(gerado)>5)
		gerado[strlen(gerado)-5] = '\0';

	GSubprocess *processo = g_subprocess_new(G_SUBPROCESS_FLAGS_STDOUT_SILENCE,&erro,
		PDF_GEN,
		"--quiet",
		"--enable-local-file-access",
		"--print-media-type",
		"--page-size",
		"A4",
		gerando_file,strcat(gerado,".pdf"),NULL);

	if(!processo)
	{
		popup(NULL,"Não foi possivel gerar documento");
		autologger(erro->message);
		return 1;
	}
	else{
		g_usleep(G_USEC_PER_SEC*1);

		if(iniciar_impressao(gerado))
			return 1;
		//else
		//	popup(NULL,"Processo finalizado");
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

	carregar_navimps();

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
