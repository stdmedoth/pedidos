int rec_familia_vet(int *familia_char,int grupo)
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	int max_nivel=0;
	char query[MAX_QUERY_LEN];
	sprintf(query,"select * from grupos where code = %i",grupo);
	res = consultar(query);
	if(res == NULL)
	{
		popup(NULL,"Erro ao consulta subgrupo");
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"O subgrupo indicado não existe");
		return 1;
	}
	
	max_nivel = atoi(row[3]);
	familia_char[0] = grupo;
	
	for(int cont=1;cont<=max_nivel;cont++)
	{
		familia_char[cont] = atoi(row[1]);
		sprintf(query,"select * from grupos where code = %i",familia_char[cont]);
		res = consultar(query);
		if(res == NULL)
		{
			popup(NULL,"Erro ao consulta subgrupo");
			return 1;
		}
		if((row = mysql_fetch_row(res))==NULL)
		{
			
			popup(NULL,"O subgrupo indicado não existe");
			return 1;
		}			
	}
	cont++;
	familia_char[cont] = -1;
	return 0;
}

int rec_familia_nome(char **familia_char,int grupo)
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	int max_nivel=0,grupo_code=0;
	int qnt=1;
	char query[MAX_QUERY_LEN];
	
	if(grupo == 1)
	{
		popup(NULL,"O grupo raiz não deve ser utilizado");
		return 0;
	}
	
	sprintf(query,"select code,nome,nivel from grupos where code = %i",grupo);
	res = consultar(query);
	if(res == NULL)
	{
		popup(NULL,"Erro ao consulta subgrupo");
		return -1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"O subgrupo indicado não existe");
		return -1;
	}
	
	max_nivel = atoi(row[2]);
	grupo_code = grupo;
	
	familia_char[0] = malloc(MAX_GRP_LEN);
	strcpy(familia_char[0],row[1]);
		
	for(int cont=1;cont<=max_nivel;cont++)
	{
		grupo_code = atoi(row[0]);
		sprintf(query,"select pai,nome from grupos where code = %i",grupo_code);
		res = consultar(query);
		
		if(res == NULL)
		{
			popup(NULL,"Erro ao consulta subgrupo");
			return -1;
		}
		
		if((row = mysql_fetch_row(res))==NULL)
		{
			
			popup(NULL,"O subgrupo indicado não existe");
			return -1;
		}
		
		familia_char[cont] = malloc(MAX_GRP_LEN);
		strcpy(familia_char[cont],row[1]);
		qnt++;
	}
	
	return qnt-1;
}
