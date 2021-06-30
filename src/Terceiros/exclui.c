int verifica_ter_chaves(){
	
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	gchar *cod_delel;
	char query[MAX_QUERY_LEN];
	cod_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(code_ter_field));

	int vinculos_pos = 0;
	char *vinculos[][2] = {
		{"itens_cotacoes", "participante_id"},
		{"PessoasDistribuicao", "pessoa"},
		{"produtos", "fornecedor"},
		{"pedidos", "cliente"},
		{"pedidos", "vendedor"},
		{"contatos", "terceiro"},
		{NULL, NULL}
	};

	while(vinculos[vinculos_pos][0] && vinculos[vinculos_pos][1]){
		sprintf(query,"select * from %s where %s = %s;",vinculos[vinculos_pos][0], vinculos[vinculos_pos][1], cod_delel);
		vetor = consultar(query);
		if(!vetor){
			int len = strlen(vinculos[vinculos_pos][0]) + strlen(vinculos[vinculos_pos][1] + 60);
			char msg[len];
			sprintf(msg, "Erro ao tentar verificar %s para o %s", vinculos[vinculos_pos][0], vinculos[vinculos_pos][1]);
			popup(NULL,msg);
			return 1;
		}
		if((campos = mysql_fetch_row(vetor))){
			int len = strlen(vinculos[vinculos_pos][0]) + strlen(vinculos[vinculos_pos][1] + 60);
			char msg[len];
			sprintf(msg, "Existem %s para esse %s", vinculos[vinculos_pos][0], vinculos[vinculos_pos][1]);
			popup(NULL,msg);
			return 1;
		}	
		vinculos_pos++;
	}
	return 0;
}
int exclui_ter(GtkWidget *botao,gpointer *ponteiro)
{
	char stringer[10];
	char query[100];
	gchar *cod_delel;
	GtkTextBuffer *buffer;
	GtkTextIter inicio,fim;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	cod_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(code_ter_field));
	sprintf(query,"select code from terceiros where code = '%s';",cod_delel);
	autologger(query);
	estado = consultar(query);
	campo = mysql_fetch_row(estado);
	if(campo==NULL)
	{
		popup(NULL,"Não existe para ser excluido");
		cancelar_ter();
		return 1;
	}

	if(verifica_ter_chaves()!=0)
		return 1;

	sprintf(query,"delete from terceiros where code = '%s';",cod_delel);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao tentar excluir terceiro");
		return 1;
	}

	sprintf(query,"select code from terceiros where code = '%s';",cod_delel);
	estado = consultar(query);
	campo = mysql_fetch_row(estado);

	if(campo==NULL)
	{
		popup(NULL,"Deletado com sucesso");
		cancelar_ter();
		return 0;
	}
	else
	{
		popup(NULL,"Não foi possivel deletar");
		return 1;
	}


	return 0;
}
