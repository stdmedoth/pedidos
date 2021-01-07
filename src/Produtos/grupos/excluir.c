int exclui_grupo(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	if(strlen(grpcode)<=0)
	{
		popup(NULL,"Insira um código para o grupo");
		return 1;
	}
	if(strlen(grpcode)>MAX_GRP_LEN)
	{
		popup(NULL,"Código muito grande para o grupo");
		return 1;
	}

	//deleta o grupo e os filhos do grupo
	sprintf(query,"delete from grupos where code = %s and pai = %s",grpcode,grpcode);

	if(enviar_query(query)!=0)
	{
		popup(NULL,"Não foi possivel excluir grupo");
		return 1;
	}
	cancela_grupo();
	popup(NULL,"Grupo excluído com sucesso");
	return 0;
}
