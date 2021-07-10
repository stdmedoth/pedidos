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

			int terceiro_importador = criar_terceiro_importador(nome);
			if(terceiro_importador){
				titulo->cliente = terceiro_importador;
			}else{
				return 1;
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