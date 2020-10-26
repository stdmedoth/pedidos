int subgrp_prod_orc(GtkWidget *widget,int posicao)
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	if(produto_inserido[posicao] == 0){
		popup(NULL,"Insira o produto!");
		gtk_widget_grab_focus(codigo_prod_orc_entry[posicao]);
		return 1;
	}

	if(!strlen(codigo_prod_orc_gchar)){
		codigo_prod_orc(codigo_prod_orc_entry[posicao] , posicao);
	}

	if(!produtos.parametros.prod_varios_grupos){
		sprintf(query,"select grupo from produtos where code = %s",codigo_prod_orc_gchar);
		res = consultar(query);
		if(!res){
			popup(NULL,"Erro ao consulta subgrupo");
			return 1;
		}
		if(!(row = mysql_fetch_row(res))){
			popup(NULL,"O produto não possui grupos");
			return 1;
		}
		if(row[0]){
			subgrp_prod_orc_cod_gchar = malloc(strlen(row[0]));
			strcpy(subgrp_prod_orc_cod_gchar,row[0]);
			ativos[posicao].subgrupo = atoi(subgrp_prod_orc_cod_gchar);
			gtk_entry_set_text(GTK_ENTRY(subgrp_prod_orc_cod_entry[posicao]),subgrp_prod_orc_cod_gchar);
		}else{
			popup(NULL,"O grupo do produto não pode ser encontrado");
			return 1;
		}
		return 0;
	}

	int grupo_len=0;
	int familia[MAX_SUBGRUPO],mesma_familia=0;
	char *source_grp_name,*dest_grp_name;
	char grupo_pai[MAX_CODE_LEN+1];
	char **familia_char;
	ativos[posicao].subgrupo = 0;
	source_grp_name = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO+1);
	dest_grp_name = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO+1);
	familia_char = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO+1);

	subgrp_prod_orc_cod_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(subgrp_prod_orc_cod_entry[posicao]));

	for(int cont=0;cont<MAX_SUBGRUPO;cont++)
		familia[cont] = 0;

	if(strlen(subgrp_prod_orc_cod_gchar)>MAX_CODE_LEN)
	{
		popup(NULL,"Código do subgrupo é muito grande");
		gtk_widget_grab_focus(subgrp_prod_orc_cod_entry[posicao]);
		return 1;
	}
	if(strlen(subgrp_prod_orc_cod_gchar)<=0)
	{
		popup(NULL,"Falta código do subgrupo");
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

	if(rec_familia_vet(familia, atoi(subgrp_prod_orc_cod_gchar) )!=0){
		popup(NULL,"Erro ao calcular niveis do grupo");
		return 1;
	}


	if((grupo_len = rec_familia_nome(familia_char, atoi(subgrp_prod_orc_cod_gchar) ))<0){
		popup(NULL,"Erro ao juntar nomes de grupos");
		return 1;
	}


	if(grupo_len == -1){
		popup(NULL,"Erro ao percorrer grupo");
		return 1;
	}

	if(!row[0]){
		popup(NULL,"Produto com grupo nulo");
		return 1;
	}

	g_print("Verificando grupo até o pai\n");
	for(int cont=0;cont<grupo_len;cont++)
	{
		g_print("%i : %i para pai %i\n",cont, familia[cont], atoi(row[0]));

		if(familia[cont]==atoi(row[0]))
		{
			mesma_familia=1;
			break;
		}
	}

	if(mesma_familia==0)
	{
		popup(NULL,"Subgrupo não pertence à mesma familia do produto");
		return 1;
	}

	strcpy(dest_grp_name,"");
	strcpy(source_grp_name,"");


	for(int cont=grupo_len;cont>0;cont--){

		if(!familia_char[cont]){
			popup(NULL,"Elemento do grupo com ponteiro nulo");
			break;
		}

		if(cont==grupo_len){
			strcpy(familia_char[cont],ativos[posicao].produto_nome);
		}

		sprintf(dest_grp_name,"%s %s",source_grp_name,familia_char[cont]);
		if(strlen(dest_grp_name)>MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO){
			popup(NULL,"Nome grupo excedeu memoria");
		}

		strcpy(source_grp_name,dest_grp_name);
		if(strlen(source_grp_name)>MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO){
			popup(NULL,"Nome grupo excedeu memoria");
			break;
		}
	}

	ativos[posicao].subgrupo = atoi(subgrp_prod_orc_cod_gchar);
	gtk_entry_set_text(GTK_ENTRY(subgrp_prod_orc_entry[posicao]),source_grp_name);
	gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
	return 0;
}
