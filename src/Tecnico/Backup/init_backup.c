int backup_iniciar_exportacao(){

	int dados_gerados = 0;
	const char *dir_filename = gtk_entry_get_text(GTK_ENTRY(backup_file_chooser_entry));
	if(!strlen(dir_filename)){
		popup(NULL,"Insira o caminho para o Backup");
		return 1;
	}
	FILE *pathcache = fopen(BKP_PTH_CACHE, "w");
	if(pathcache){
		fprintf(pathcache,"%s",dir_filename);
		fclose(pathcache);
	}

	MYSQL_RES *res;
	backup_clientes_gint = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backup_clientes_check));
	backup_produtos_gint = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backup_produtos_check));
	backup_orcamentos_gint = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backup_orcamentos_check));
	backup_pedidos_gint = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backup_pedidos_check));
	backup_estoques_gint = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backup_estoques_check));
	backup_movimentacoes_gint = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backup_movimentacoes_check));
	backup_bancos_gint = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backup_bancos_check));
	backup_titulos_rec_gint = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backup_titulos_rec_check));
	backup_baixas_rec_gint = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backup_baixas_rec_check));
	backup_titulos_pag_gint = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backup_titulos_pag_check));
	backup_baixas_pag_gint = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backup_baixas_pag_check));

	global_progress_bar_active = 1;
	for (int i = 0; backup_objs[i][BACKUP_OBJ_MODULE]; ++i)
	{
		if(!backup_clientes_gint && !strcmp("clientes", backup_objs[i][BACKUP_OBJ_MODULE])) {
			continue;
		}
		if(!backup_produtos_gint && !strcmp("produtos", backup_objs[i][BACKUP_OBJ_MODULE])) {
			continue;
		}
		if(!backup_orcamentos_gint && !strcmp("orcamentos", backup_objs[i][BACKUP_OBJ_MODULE])) {
			continue;
		}
		if(!backup_pedidos_gint && !strcmp("pedidos", backup_objs[i][BACKUP_OBJ_MODULE])) {
			continue;
		}
		if(!backup_estoques_gint && !strcmp("estoques", backup_objs[i][BACKUP_OBJ_MODULE])) {
			continue;
		}
		if(!backup_movimentacoes_gint && !strcmp("movimentacoes", backup_objs[i][BACKUP_OBJ_MODULE])) {
			continue;
		}
		if(!backup_bancos_gint && !strcmp("bancos", backup_objs[i][BACKUP_OBJ_MODULE])) {
			continue;
		}
		if(!backup_titulos_rec_gint && !strcmp("titulos_rec", backup_objs[i][BACKUP_OBJ_MODULE])) {
			continue;
		}
		if(!backup_baixas_rec_gint && !strcmp("baixas_rec", backup_objs[i][BACKUP_OBJ_MODULE])) {
			continue;
		}
		if(!backup_titulos_pag_gint && !strcmp("titulos_pag", backup_objs[i][BACKUP_OBJ_MODULE])) {
			continue;
		}
		if(!backup_baixas_pag_gint && !strcmp("baixas_pag", backup_objs[i][BACKUP_OBJ_MODULE])) {
			continue;
		}


		char *msg_prefix = "Criando backup para tabela ";
		char msg[ strlen(msg_prefix) + strlen(backup_objs[i][BACKUP_OBJ_MODULE]) ];
		sprintf(msg, "%s%s", msg_prefix, backup_objs[i][BACKUP_OBJ_MODULE]);
		global_progress_bar_text = strdup(msg);

		int file_path_len =
													strlen(dir_filename) + 2 +
													strlen(backup_objs[i][BACKUP_OBJ_TABLE]) +
													strlen(db_version) +
													strlen(set_db_formated_date(data_sys));

		char file_path[ file_path_len ];
		sprintf(file_path,"%s/%s_db-%s-%s.csv", dir_filename, backup_objs[i][BACKUP_OBJ_TABLE], db_version, set_db_formated_date(data_sys));

		char *msg_erro1 = "Não foi possível criar backup para ";
		char *msg_erro2 = "Não há dados para tabela ";

		if(!(res = consultar(backup_objs[i][BACKUP_OBJ_QUERY]))){
			int msglen = strlen(msg_erro1) + strlen(backup_objs[i][BACKUP_OBJ_TABLE]);
			char msg[ msglen ];
			sprintf(msg,"%s%s", msg_erro1, backup_objs[i][BACKUP_OBJ_TABLE]);
			popup(NULL, msg);
			global_progress_bar_active = 0;
			return 1;
		}
		if(!mysql_num_rows(res)){
			int msglen = strlen(msg_erro2) + strlen(backup_objs[i][BACKUP_OBJ_TABLE]);
			char msg[ msglen ];
			sprintf(msg,"%s%s", msg_erro2, backup_objs[i][BACKUP_OBJ_TABLE]);
			file_logger(msg);
			continue;
		}
		if(mysql_res_to_cvs_file(file_path, res)){
			int msglen = strlen(msg_erro1) + strlen(backup_objs[i][BACKUP_OBJ_TABLE]);
			char msg[ msglen ];
			sprintf(msg,"%s%s", msg_erro1, backup_objs[i][BACKUP_OBJ_TABLE]);
			popup(NULL, msg);
			global_progress_bar_active = 0;
			return 1;
		}
		dados_gerados = 1;
	}

	if(!dados_gerados){
		popup(NULL,"Não houve dados a gerar!");
		global_progress_bar_active = 0;
		return 0;
	}

	global_progress_bar_active = 0;
	popup(NULL,"Backup feito com sucesso!");
	if(PopupBinario("Deseja abrir diretório do backup?", "Sim", "Mais tarde eu vejo")){
		global_progress_bar_active = 1;
		GError *error = NULL;
		char open_path[MAX_PATH_LEN];

		#ifdef WIN32
			sprintf(open_path, "%s",dir_filename);
			HINSTANCE result = ShellExecuteA(NULL, "explore", open_path, NULL, NULL, SW_SHOWMAXIMIZED);
			if(result <= 32){
				popup(NULL, "Não foi possível abrir diretório do backup");
				file_logger(open_path);
			}
		#endif
		#ifdef __linux__
		sprintf(open_path, "file://%s",dir_filename);
		if (!g_app_info_launch_default_for_uri (open_path , NULL, &error)) {
		    popup(NULL, "Não foi possível abrir diretório do backup");
		    file_logger(error->message);
		}
		#endif
	}
	global_progress_bar_active = 0;

	return 0;
}
