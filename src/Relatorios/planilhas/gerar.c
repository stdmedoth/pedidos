int planilhas_gerar(){
	gint module = gtk_combo_box_get_active(GTK_COMBO_BOX(planilha_export_module_combo));
	const gchar *dirname = gtk_entry_get_text(GTK_ENTRY(planilha_export_path_entry));
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	char filename[strlen(dirname) + 12];
	srand(time(NULL));
	int r = rand();
	int planilha_gerada=0;
	sprintf(filename, "%s/%i.csv", dirname, r);

	FILE *pathcache = fopen(EXP_PTH_CACHE, "w");
	if(pathcache){
		fprintf(pathcache,"%s",dirname);
		fclose(pathcache);
	}else{
		file_logger("Nâo foi possível salvar caminho no cache");
		file_logger(strerror(errno));
	}
	for(int cont=0; planilhas_gerar_querys[cont][0] != NULL ;cont++){
		if( planilhas_gerar_querys[cont][0] && ( atoi(planilhas_gerar_querys[cont][0]) == module ) ) {
			planilha_gerada = 1;
			strcpy(query, planilhas_gerar_querys[cont][1]);
		}
	}
	if(!planilha_gerada){
		popup(NULL,"Objeto da planilha não encontrado");
		return 1;
	}

	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível gerar planilha");
		return 1;
	}
	if(!mysql_num_rows(res)){
		popup(NULL,"Não há dados a gerar");
		return 1;
	}
	if(mysql_res_to_cvs_file(filename, res)){
		popup(NULL,"Não foi possível criar a planilha");
		return 1;
	}
	
	GError *error = NULL;
	char open_path[MAX_PATH_LEN];
	sprintf(open_path, "file://%s",filename);
	if (!g_app_info_launch_default_for_uri (open_path , NULL, &error)) {
	    popup(NULL, "Não foi possível abrir arquivo exportado");
	    file_logger(error->message);
	}

	return 0;
}