int produto_ter()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[MAX_QUERY_LEN];
	if(code_terc())
		return 1;

	prods_ter = (gchar*) gtk_entry_get_text(GTK_ENTRY(prod_ter_field));

	if(strlen(prods_ter)<=0){
		popup(NULL,"Por favor, Insira produto que deseja vincular");
		gtk_widget_grab_focus(prod_ter_field);
		return 1;
	}
	else
	if(strlen(prods_ter)>=MAX_GRP_LEN){
		popup(NULL,"Código do produto é muito grande");
		return 1;
	}

	sprintf(query,"select nome from produtos where code = '%s'",prods_ter);

	if(!(vetor = consultar(query))){
		popup(NULL,"Não foi possível consultar produtos");
		return 1;
	}
	if(!(campos = mysql_fetch_row(vetor))){
		popup(NULL,"Este código para produto não existe");
		g_print("Esta código para produto não existe:%s",prods_ter);
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(campo_nome_prod_ter),campos[0]);
	if(!atualizando_ter_precos){
		sprintf(query,"select valor_fat, valor_vist from preco_cliente where produto = '%s' and cliente = '%s'",prods_ter,codigos_ter);
		if((vetor = consultar(query)))
		{
			campos = mysql_fetch_row(vetor);
			if(campos)
			{
				gtk_entry_set_text(GTK_ENTRY(entry_preco_ter_prcfat),campos[0]);
				gtk_entry_set_text(GTK_ENTRY(entry_preco_ter_prcvist),campos[1]);
			}
		}

	}
	gtk_widget_grab_focus(entry_preco_ter_prcfat);
	return 0;
}
