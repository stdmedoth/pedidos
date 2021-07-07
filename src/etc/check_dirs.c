int check_directorys(){
	for(int cont=0; check_directorys_list[cont] != NULL; cont++){
		GDir *directory;
		if(!(directory = g_dir_open(check_directorys_list[cont],0,NULL))){
			if( g_mkdir_with_parents(check_directorys_list[cont], 777 ) == -1){
				popup(NULL, "Não foi possível validar diretórios necessários para o funcionamento");
				file_logger("Erro ao criar diretório");
				file_logger((gchar*)check_directorys_list[cont]);
				return 1;
			}
		}
	}
	return 0;
}