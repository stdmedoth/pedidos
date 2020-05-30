//arrumar mensagem na segunda tentativa de erro 

int subgrp_prod_orc(GtkWidget *widget,int posicao)
{
	MYSQL_RES *res;
	MYSQL_ROW row;

	int grupo_len=0;
	int familia[MAX_SUBGRUPO],mesma_familia=0;
	char query[MAX_QUERY_LEN];
	char grupo_pai[MAX_CODE_LEN];
	char *source,*dest;
	char **familia_char;
	
	char mensagem[] = "O código deve ser de nível            ";
	
	source = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO);
	dest = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO);

	subgrp_prod_orc_cod_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(subgrp_prod_orc_cod_entry[posicao]));
	
	if(GTK_IS_WIDGET(codigo_prod_orc_entry[posicao]))
		if(codigo_prod_orc(codigo_prod_orc_entry[posicao],posicao)!=0)
			return 1;
	
	if(strlen(subgrp_prod_orc_cod_gchar)>MAX_CODE_LEN)
	{
		popup(NULL,"Código do subgrupo é muito grande");
		gtk_widget_grab_focus(subgrp_prod_orc_cod_entry[posicao]);
		return 1;
	}
	
	sprintf(query,"select grupo from produtos where code = %s",codigo_prod_orc_gchar);
	res = consultar(query);
	if(res == NULL)
	{
		popup(NULL,"Erro ao consulta subgrupo");
		return 1;
	}
	
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"O produto inserido não existe");
		return 1;
	}
	
	familia_char = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO-1);
	
	if(rec_familia_vet(familia, atoi(subgrp_prod_orc_cod_gchar) )!=0)
		return 1;
		
	if((grupo_len = rec_familia_nome(familia_char, atoi(subgrp_prod_orc_cod_gchar) ))<0)
		return 1;
	
	for(int cont=0;familia[cont]!=-1;cont++)
	{
		if(familia[cont]==atoi(row[0]))
		{
			mesma_familia=1;
			break;
		}
	}
	g_print("grupo do produto %s, grupo inserido %s",row[0],subgrp_prod_orc_cod_gchar);
	if(mesma_familia==0)
	{
		popup(NULL,"Subgrupo não pertence à mesma familia do produto");
		return 1;
	}

	memset(dest,0x0,strlen(dest));
	memset(source,0x0,strlen(source));
	for(int cont=grupo_len-1;cont>=0;cont--)
	{
		sprintf(dest,"%s %s",source,familia_char[cont]);
		
		strcpy(source,dest);
	}
	
	ativos[posicao].subgrupo = atoi(subgrp_prod_orc_cod_gchar);
	gtk_entry_set_text(GTK_ENTRY(subgrp_prod_orc_entry[posicao]),dest);
	gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
	return 0;
}
