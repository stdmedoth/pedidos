int subgrp_prod_orc(GtkWidget *widget,int posicao)
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	MYSQL_RES *res2;
	MYSQL_ROW row2;
	char query[MAX_QUERY_LEN];
	char mensagem[] = "O código deve ser de nível            ";
	subgrp_prod_orc_cod_gchar = malloc(MAX_CODE_LEN);
	subgrp_prod_orc_cod_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(subgrp_prod_orc_cod_entry[posicao]));
	if(strlen(subgrp_prod_orc_cod_gchar)>MAX_CODE_LEN)
	{
		popup(NULL,"Código do subgrupo é muito grande");
		gtk_widget_grab_focus(subgrp_prod_orc_cod_entry[posicao]);
		return 1;
	}
	//query para verificar nivel
	sprintf(query,"select g.nome, g.nivel, p.grupo, p.grupo_nivel from grupos as g inner join produtos as p where g.code = %s",subgrp_prod_orc_cod_gchar);
	res = consultar(query);
	if(res == NULL)
	{
		popup(NULL,"Erro ao consulta subgrupo");
		gtk_widget_grab_focus(subgrp_prod_orc_cod_entry[posicao]);
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"O subgrupo indicado não existe");
		gtk_widget_grab_focus(subgrp_prod_orc_cod_entry[posicao]);
		return 1;
	}
	row2 = malloc(strlen(subgrp_prod_orc_cod_gchar));
	row2[1] = malloc(strlen(subgrp_prod_orc_cod_gchar));
	strcpy(row2[1],subgrp_prod_orc_cod_gchar);

	if(atoi(row[1])!=atoi(row[3]))
	{
		sprintf(mensagem,"O grupo deve ser de nivel %s",row[3]);
		popup(NULL,mensagem);
		gtk_widget_grab_focus(subgrp_prod_orc_cod_entry[posicao]);
		return 1;
	}
	
	while(atoi(row[1])!=0)
	{
		sprintf(query,"select code,pai from grupos where code = %s",row2[1]);
		g_print("%s\nGrupo pai %s\n",query,row[2]);
		res2 = consultar(query);
		if(res2 == NULL)
		{
			popup(NULL,"Erro ao consulta subgrupo");
			gtk_widget_grab_focus(subgrp_prod_orc_cod_entry[posicao]);
			return 1;
		}
		if((row2 = mysql_fetch_row(res2))==NULL)
		{
			popup(NULL,"O subgrupo indicado não existe");
			gtk_widget_grab_focus(subgrp_prod_orc_cod_entry[posicao]);
			return 1;
		}
		if(atoi(row2[1])==atoi(row[2]))
			break;
		strcpy(row2[0],row2[1]);
		if(cont>5)
		{
			popup(NULL,"O subgrupo não condiz com grupo cadastrado no produto");
			gtk_widget_grab_focus(subgrp_prod_orc_cod_entry[posicao]);
			return 1;
		}
		cont++;
	}

	ativos[posicao].subgrupo = atoi(subgrp_prod_orc_cod_gchar);
	gtk_entry_set_text(GTK_ENTRY(subgrp_prod_orc_entry[posicao]),row[0]);
	gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
	return 0;
}
