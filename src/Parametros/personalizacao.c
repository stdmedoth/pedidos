int personalizacao_copy_image_to_custom_desktop(){
	const char *image_orig_path = gtk_entry_get_text(GTK_ENTRY(custom_desktop_path_entry));
	if(!strlen(image_orig_path)){
		return 0;
	}

	FILE *custom_image_path_cache = fopen(CSTM_DSKTP_CACHE, "w");
	if(custom_image_path_cache){
		const char custom_image_path[MAX_PATH_LEN];
		fprintf(custom_image_path_cache, "%s", image_orig_path );
		fclose(custom_image_path_cache);
	}

	if(copy_file(image_orig_path, CUSTOM_DESKTOP)){
		return 1;
	}

	return 0;
}

static int ler_personalizacao()
{
	//*usar gtk_toggle_button_get_active aqui
	personalizacao.tema = gtk_combo_box_get_active(GTK_COMBO_BOX(tema_combo_box));
	if(personalizacao.tema<0)
		personalizacao.tema = -1;

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

	FILE *custom_image_path_cache = fopen(CSTM_DSKTP_CACHE, "r");
	if(custom_image_path_cache){
		char custom_image_path[MAX_PATH_LEN];
		fgets(custom_image_path, MAX_PATH_LEN, custom_image_path_cache);
		gtk_entry_set_text(GTK_ENTRY(custom_desktop_path_entry), custom_image_path);
	}

	char query[MAX_QUERY_LEN];
	sprintf(query,"select * from perfil_desktop where code = %i",sessao_oper->operador->code);

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
	char query[MAX_QUERY_LEN + MAX_PATH_LEN * 4];
	char navegador_path1[MAX_PATH_LEN],
		 navegador_path2[MAX_PATH_LEN],

		 imp_path1[MAX_PATH_LEN],
		 imp_path2[MAX_PATH_LEN],
		 imp_path3[MAX_PATH_LEN];

	if(ler_personalizacao())
		return 1;

	if(personalizacao_copy_image_to_custom_desktop()){
		return 1;
	}
	sprintf(query,"update perfil_desktop set janela_init = %i",personalizacao.janela_init);
	if((erro = enviar_query(query))!=0)
	{
		popup(NULL,"Erro ao configurar janela login");
	}
		sprintf(query,"update perfil_desktop set tema = %i,janelas_keep_above = %i where code = %i",personalizacao.tema, personalizacao.janela_keep_above, sessao_oper->operador->code);
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

	sprintf(query,"update confs set navegador_path1 = '%s',navegador_path2 = '%s', navegador_pdr = %i, imp_path1 = '%s', imp_path2 = '%s', imp_path3 = '%s'  where code = %i",navegador_path1,navegador_path2,navegadores.navegador_pdr,imp_path1,imp_path2,imp_path3,sessao_oper->operador->code);

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

int trocar_desktop(GtkWidget *widget,GtkWidget *event,int posicao)
{
	int numero = posicao;
	int erro;
	char *query;
	query = malloc(MAX_QUERY_LEN);

	if(inicializando == 0){
		sprintf(query,"update perfil_desktop set desktop_img = %i where code = %i",numero,sessao_oper->operador->code);
		erro = enviar_query(query);
		if(erro!=0)
		{
			popup(NULL,"Não foi possivel inserir imagem");
		}
	}

	switch(numero)
	{
		case 0:
			gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),DESKTOP1);
			break;
		case 1:
			gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),DESKTOP2);
			break;
		case 2:
			gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),DESKTOP3);
			break;
		case 3:
			gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),DESKTOP4);
			break;
		case 4:
			gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),DESKTOP5);
			break;
		case 5:
			gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),DESKTOP6);
			break;
		case 6:
				gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),CUSTOM_DESKTOP);
				break;
		default:
			gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),DESKTOP1);
	}
	return 0;
}
