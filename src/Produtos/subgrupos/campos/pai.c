int pai_subgrp()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *nomepai;
	subgrp_paicode = malloc(MAX_CODE_LEN);
	nomepai = malloc(MAX_GRP_LEN*2);
	subgrp_paicode = (gchar*) gtk_entry_get_text(GTK_ENTRY(cod_subgrp_pai_entry));
	char query[MAX_QUERY_LEN];
	if(stoi(subgrp_paicode)==-1)
	{
		popup(NULL,"O campo deve ser preenchido com um código");
		return 1;
	}
	if(strlen(subgrp_paicode)>MAX_CODE_LEN)
	{
		popup(NULL,"O código está muito extenso");
		return 1;
	}
	sprintf(query,"select a.nome,b.nome from grupos as a right join grupos as b on a.code = b.pai where b.code = %s",subgrp_paicode);
	res = consultar(query);
	if(!res){
		popup(NULL,"Erro ao procurar nome do grupo pai");
		return 1;
	}
	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"Grupo pai não encontrado");
		return 1;
	}

	if(!row[0])
		row[0] = strdup("Nulo");

	if(!row[1])
		row[1] = strdup("Nulo");

	if(strcmp(row[0],"RAIZ"))
		sprintf(nomepai,"%s %s",row[0],row[1]);
	else
		sprintf(nomepai,"%s",row[1]);
	gtk_entry_set_text(GTK_ENTRY(campo_nome_subgrg_pai),nomepai);
	return 0;
}
