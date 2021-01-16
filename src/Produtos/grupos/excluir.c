int exclui_grupo(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	if(strlen(grpcode)<=0)
	{
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

	sprintf(query,"select * from produtos where grupo = %s",grpcode);
	if(!(res = consultar(query))){
		popup(NULL, "Não foi possível consultar produtos vinculados ao grupo");
		return 1;
	}
	if((row = mysql_fetch_row(res))){
		if(PopupBinario("O grupo possui produtos vinculados, Deseja excluir?", "Sim, Exclua os produtos e o grupo!", "Não, Cancele o procedimento agora")){
			sprintf(query,"delete from grupos where pai = %s",grpcode);
			if(enviar_query(query)!=0){
				popup(NULL,"Não foi possivel excluir produto (provavelmente possui vínculos com outros componentes)");
				return 1;
			}
		}else{
			return 1;
		}
	}

	//deleta o grupo e os filhos do grupo
	sprintf(query,"delete from grupos where code = %s and pai = %s",grpcode,grpcode);
	if(enviar_query(query)!=0){
		popup(NULL,"Não foi possivel excluir grupo");
		return 1;
	}
	cancela_grupo();
	popup(NULL,"Grupo excluído com sucesso");
	return 0;
}
