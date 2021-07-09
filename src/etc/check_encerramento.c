int check_encerramento_file(){
	FILE *fp = fopen(ENCER_FINE_PATH, "r");
	if(!fp){
		encerramento_brusco = 0;
		return 0;
	}
	char msg[200];
	file_logger("Sistema teve um encerramento brusco");
	file_logger(strerror(errno));
	encerramento_brusco = 1;
	fclose(fp);
	return 1;
}

int create_encerramento_file(){
	FILE *fp = fopen(ENCER_FINE_PATH, "w");
	if(!fp){
		char msg[200];
		sprintf(msg, "Erro ao tentar criar arquivo de verificação runtime");
		popup(NULL,msg);
		file_logger(msg);
		file_logger(strerror(errno));
		return 1;
	}
	fprintf(fp,"rodando...");
	fclose(fp);
	return 0;
}

int remove_encerramento_file(){
	
	if(remove(ENCER_FINE_PATH) == -1){
		char msg[200];
		sprintf(msg, "Erro ao tentar remover arquivo de encerramento");
		popup(NULL,msg);
		file_logger(msg);
		file_logger(strerror(errno));
		return 1;
	}
	
	return 0;
}