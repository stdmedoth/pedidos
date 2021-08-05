int download_changelog_files(){

	global_progress_bar_active = 1;
	char url[strlen(PEDIDOS_APP_URL_FILES) + 200];
	sprintf(url, "%s/data/files_changelog.txt", PEDIDOS_APP_URL_FILES);

	if(download_from_to(url, CHANGELOG_FILES)){
		popup(NULL,"Não foi possível receber arquivo com atualização");
		return 1;
	}
	char *from_to_string = malloc(MAX_PATH_LEN * 2);
	size_t line_buf_size = 0;
	FILE *changelog_file = fopen(CHANGELOG_FILES, "r");
	if(!changelog_file){
		popup(NULL, "Não foi possível abrir arquivo de changelogs");
		return 1;
	}
	file_logger("Iniciando download dos arquivos da versão:");
	while((getline(&from_to_string, &line_buf_size, changelog_file))>0){
		remover_barra_n(from_to_string);
		file_logger("Baixando...");
		file_logger(from_to_string);

		global_progress_bar_text = strdup(from_to_string);
		char *from = strtok(from_to_string, ":");
		if(!from){
			file_logger("Não foi possível dar parser na linha abaixo:");
			file_logger(from_to_string);
			continue;
		}
		char *to = strtok(NULL, ":");
		if(!to){
			file_logger("Não foi possível dar parser na linha abaixo:");
			file_logger(from_to_string);
			continue;
		}
		char path[MAX_PATH_LEN];

		sprintf(url, "%s/%s", PEDIDOS_APP_URL_FILES, from);
		sprintf(path,"%s/%s", APP_DIRNAME, to);
		if(download_from_to(url, path)){
			file_logger("Não foi possível baixar arquivo na atualização");
			file_logger(url);
			file_logger(path);
			popup(NULL,"Erro ao baixar arquivos da atualização");
			return 1;
		}
	}
	file_logger("Arquivos da atualização foram baixados");

	if(remove(ATUALIZA_VERTMP) == -1){
		file_logger("Erro ao tentar remover gatilho de atualização");
		file_logger(strerror(errno));
	}

	return 0;
}
int check_updated(){
	FILE *tmp_updt_fp = fopen(ATUALIZA_VERTMP,"r");
  if(!tmp_updt_fp){
    return 0;
  }
  fclose(tmp_updt_fp);
  return 1;
}
