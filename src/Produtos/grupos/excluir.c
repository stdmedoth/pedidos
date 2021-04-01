int exclui_grupo(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	char *foreign_keys[] = {"produtos"};
	int foreign_keys_qnt = 1;

	if(atoi(grpcode) == 1){
		popup(NULL,"Não é possivel excluir grupo RAIZ");
		return 1;
	}
	if(strlen(grpcode)<=0){
		popup(NULL,"Insira um código para o grupo");
		return 1;
	}
	if(strlen(grpcode)>MAX_GRP_LEN){
		popup(NULL,"Código muito grande para o grupo");
		return 1;
	}
	sprintf(query,"select * from grupos where pai = %s",grpcode);
	if(!(res = consultar(query))){
		popup(NULL, "Não foi possível consultar ramificações do grupo");
		return 1;
	}
	
	for(int cont=0; cont<foreign_keys_qnt; cont++ ){
		char msg[200];
		sprintf(query, "select code from %s where grupo = %s", foreign_keys[cont], grpcode);
		if(!(res = consultar(query))){
			popup(NULL,"Erro ao verificar vínculos");
			return 1;
		}
		if((row = mysql_fetch_row(res))){
			sprintf(msg, "Há vinculos com tabela %s, Deseja excluir?", foreign_keys[cont]);
			if(PopupBinario(msg, "Sim, Exclua as vinculos!", "Não, Cancele o procedimento")){
				sprintf(query,"delete from %s where grupo = %s", foreign_keys[cont], grpcode);
				if(enviar_query(query)!=0){
					char msg[300];
					sprintf(msg, "Não foi possivel excluir %s (Provavel vínculo em %s)", foreign_keys[cont], foreign_keys[cont]);
					popup(NULL, msg);
					return 1;
				}
			}	
		}
	}
	if((row = mysql_fetch_row(res))){
		if(PopupBinario("O grupo possui ramificações, Deseja excluir?", "Sim, Exclua as ramificações e o grupo!", "Não, Cancele o procedimento")){
			sprintf(query,"delete from grupos where pai = %s",grpcode);
			if(enviar_query(query)!=0){
				popup(NULL,"Não foi possivel excluir grupo (provavelmente possui ramificações de nivel 2)");
				return 1;
			}
		}else{
			return 1;
		}
	}

	//deleta o grupo e os filhos do grupo
	sprintf(query,"delete from grupos where code = %s",grpcode);
	if(enviar_query(query)!=0){
		popup(NULL,"Não foi possivel excluir grupo");
		return 1;
	}
	cancela_grupo();
	popup(NULL,"Grupo excluído com sucesso");
	return 0;
}
