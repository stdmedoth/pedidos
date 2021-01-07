int conclui_subgrupo(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	char mensagem[30];
	int nivel=0;
	concluindo_subgrp=1;

	if(cod_subgrp()){
		gtk_widget_grab_focus(cod_subgrp_entry);
		return 1;
	}

	if(nome_subgrp()){
		gtk_widget_grab_focus(nome_subgrp_entry);
		return 1;
	}

	if(pai_subgrp()){
		gtk_widget_grab_focus(cod_subgrp_pai_entry);
		return 1;
	}

	sprintf(query,"select nivel from grupos where code = %s",subgrp_paicode);
	if(!(res = consultar(query))){
		popup(NULL,"Erro ao procurar nivel do grupo pai");
		return 1;
	}
	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"Erro ao procurar nivel do grupo pai");
		return 1;
	}

	nivel = atoi(row[0])+1;
	if(alterando_subgrp==0){
		strcpy(mensagem,"Subgrupo criado com sucesso");
		sprintf(query,"insert into grupos(code,nome,pai,nivel) values('%s','%s',%s,%i)",subgrpcode,subgrpnome,subgrp_paicode,nivel);
	}
	else
	{
		strcpy(mensagem,"Subgrupo alterado com sucesso");
		sprintf(query,"update grupos set nome = '%s', pai = %s, nivel = %i where code = %s",subgrpnome,subgrp_paicode,nivel,subgrpcode);
	}
	if(enviar_query(query)!=0){
    popup(NULL,"Não foi possível criar subgrupo");
		return 1;
	}
	cancela_subgrupo();
	popup(NULL,mensagem);
	gtk_widget_grab_focus(cod_subgrp_entry);
	return 0;
}
