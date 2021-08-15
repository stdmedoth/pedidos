int import_tits_importar(){

	global_progress_bar_active = 1;
	imprt_tits_path_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(imprt_tits_entry));
	if(!strlen(imprt_tits_path_gchar)){
		global_progress_bar_active = 0;
		popup(NULL,"Insira o caminho do arquivo");
		return 1;
	}
	FILE *arquivo = fopen(imprt_tits_path_gchar,"r");
	if(!arquivo){
		popup(NULL,"Não foi possível abrir arquivo");
		return 1;
	}

	int pos = 0;
	char *linha = malloc(500);

	char *nome = NULL;
	char *data = NULL;
	char *valor = NULL;

	float total_recebido=0;
	float total_pago=0;
	float total_saldo=0;
	int result=0;

	imprt_tits_tipo_int = gtk_combo_box_get_active(GTK_COMBO_BOX(imprt_tits_tipo_combo));

	struct _titulo *titulo = malloc(sizeof(struct _titulo ));

	titulo->pedido = 0;
	titulo->status = STAT_QUITADO;
	titulo->qnt_parcelas = 1;
	titulo->qnt_baixas = 1;
	while(fgets(linha,500,arquivo)){
		char **vetor = get_csv_line(linha);

		if(pos >= MAX_IMP_TITS)
			break;

		if(vetor){

			if(vetor[0]){
				data = strdup(vetor[0]);
			}else{
				data = strdup("");
			}
			if(vetor[1]){
				nome = strdup(vetor[1]);
			}else{
				nome = strdup("");
			}
			if(vetor[2]){
				valor = strdup(vetor[2]);
			}else{
				valor = strdup("");
			}
			if(strlen(nome)>20)
				nome[20] = '\0';

			if(imprt_tits_tipo_int == TP_TIT_PAG){
				if(atof(valor)>=0){
					continue;
				}
			}

			if(imprt_tits_tipo_int == TP_TIT_REC){
				if(atof(valor)<0){
					continue;
				}
			}

			if(simp_critica_real(valor)){
				continue;
			}

			if(atof(valor)>=0){
				titulo->tipo_titulo = TP_TIT_REC;
				total_recebido += atof(valor);

			}else{
				titulo->tipo_titulo = TP_TIT_PAG;
				total_pago += atof(valor);
			}

			int terceiro_importador = 0;
			int titulo_exists = 0;
			char query[MAX_QUERY_LEN];
			MYSQL_RES *res;
			MYSQL_ROW row;
			float _valor = atof(valor);
			if(_valor < 0){
				_valor = - _valor;
			}
			sprintf(query,"SELECT * FROM parcelas_tab WHERE valor = %.2f and data_criacao = '%s' and data_vencimento = '%s'", _valor, set_db_formated_date(data), set_db_formated_date(data));

			if((res = consultar(query))){
				if((row = mysql_fetch_row(res) )){
					titulo_exists = 1;
					continue;
				}
			}

			int terceiro_exists = 0;

			sprintf(query,"SELECT code, razao FROM terceiros tc WHERE tc.razao like '%%%s%%'", nome);
			if(!(res = consultar(query))){
				popup(NULL,"Erro ao buscar existencia do terceiro");
				return 1;
			}
			if(!mysql_num_rows(res)){
				char *nome_copy = strdup(nome);
				char *fist_name = strtok(nome_copy, " ");
				char *second_name = NULL;

				if(fist_name){
					if( (second_name = strtok(NULL, " ")) && strlen(second_name) > 3 ){
						sprintf(query,"SELECT code, razao FROM terceiros tc WHERE tc.razao like '%%%s%%' or tc.razao like '%%%s%%' ", fist_name, second_name);
					}else{
						sprintf(query,"SELECT code, razao FROM terceiros tc WHERE tc.razao like '%%%s%%'", fist_name);
					}
					if((res = consultar(query))){
						if((row = mysql_fetch_row(res))){
							int max_len = strlen(nome) + strlen(row[1]) + 2048;
							char msg[max_len];
							sprintf(msg, "O título para %s\ncorresponde a %s?", row[1], nome);
							if(PopupBinario(msg, "Sim! importar neste cadastro", "Não! cadastrar uma nova pessoa para o título")){
								terceiro_exists = 1;
								titulo->cliente = atoi(row[0]);
							}
						}
					}
				}
			}else{
				if((row = mysql_fetch_row(res))){
					terceiro_exists = 1;
					titulo->cliente = atoi(row[0]);
				}
			}

			if(!terceiro_exists){
				terceiro_importador = criar_terceiro_importador(nome);
				if(terceiro_importador){
					titulo->cliente = terceiro_importador;
				}else{
					return 1;
				}
			}



			titulo->parcelas = malloc(sizeof(struct _titulo_parcela));
			titulo->parcelas[0].posicao = 0;
			titulo->parcelas[0].banco = get_banco(1);
			titulo->parcelas[0].data_criacao = set_db_formated_date(data);
			titulo->parcelas[0].data_vencimento = set_db_formated_date(data);
			titulo->parcelas[0].valor = atof(valor);
			if(titulo->parcelas[0].valor < 0){
				titulo->parcelas[0].valor = - titulo->parcelas[0].valor;
			}

			titulo->baixas = malloc(sizeof(struct _titulo_parcela));
			titulo->baixas[0].posicao = 0;
			titulo->baixas[0].data_criacao = set_db_formated_date(data);
			titulo->baixas[0].valor = atof(valor);
			if(titulo->baixas[0].valor < 0){
				titulo->baixas[0].valor = - titulo->baixas[0].valor;
			}

			if(!criar_titulo(titulo)){
				file_logger("Erro ao criar título de importação");
			}

			pos++;
		}

	}

	global_progress_bar_active = 0;
	popup(NULL,"Os títulos foram importados com sucesso!");
	fclose(arquivo);
	return 0;
}
