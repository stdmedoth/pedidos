int conclui_grupo(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	gchar *nome;
	concluindo_grp=1;
	char query[MAX_QUERY_LEN];
	char mensagem[30];

	if(cod_grp())
		return 1;

	if(nome_grp())
		return 1;

	if(codpai_grp()){
		return 1;
	}

	
	sprintf(query,"select * from grupos where code = 1 and nome = 'RAIZ'");
	if(!(res = consultar(query))){
		popup(NULL,"Erro ao consultar RAIZ");
		return 1;
	}
	if(!(row = mysql_fetch_row(res))){
		sprintf(query,"insert into grupos(code, nome, pai, nivel) values(1, 'RAIZ', 1, 0)");
		if(enviar_query(query)){
			popup(NULL,"Não foi possível criar grupo RAIZ");
			return 1;
		}
	}

	if(alterando_grp==0){
		strcpy(mensagem,"Grupo criado com sucesso");
		sprintf(query,"insert into grupos(code,nome,pai,nivel) values('%s','%s','%s',%i)",grpcode, grpnome, paigrpcode, grpnivel);
	}
	else{
		strcpy(mensagem,"Grupo alterado com sucesso");
		sprintf(query,"update grupos set nome = '%s', pai = %s, nivel = %i where code = %s",grpnome,paigrpcode, grpnivel, grpcode);
	}
	if(enviar_query(query)!=0){
		return 1;
	}
	cancela_grupo();

	popup(NULL,mensagem);

	return 0;
}
