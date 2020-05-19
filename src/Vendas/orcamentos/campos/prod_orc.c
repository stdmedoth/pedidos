int codigo_prod_orc(GtkWidget *widget,int posicao)
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	codigo_prod_orc_gchar = malloc(MAX_CODE_LEN);
	codigo_prod_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(codigo_prod_orc_entry[posicao]));
	if(strlen(codigo_prod_orc_gchar)<=0)
	{
		popup(NULL,"O código do produto deve ser inserido");
		gtk_widget_grab_focus(codigo_prod_orc_entry[posicao]);
		
		return 1;
	}
	if(stoi(codigo_prod_orc_gchar)==-1)
	{
		popup(NULL,"O código do produto deve ser numérico");
		gtk_widget_grab_focus(codigo_prod_orc_entry[posicao]);
		
		return 1;
	}
	sprintf(query,"select p.nome, u.nome from produtos as p inner join unidades as u on p.unidades= u.code where p.code = %s",codigo_prod_orc_gchar);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		g_print("Erro na query de produtos no orcamento\n");
		autologger("Erro na query de produtos no orcamento\n");
		autologger(query);
		
		gtk_widget_grab_focus(codigo_prod_orc_entry[posicao]);
		return 1;
	}
	campos = mysql_fetch_row(vetor);
	if(campos == NULL)
	{
		popup(NULL,"Produto não existente");
		gtk_widget_grab_focus(codigo_prod_orc_entry[posicao]);
		
		gtk_widget_grab_focus(codigo_prod_orc_entry[posicao]);
		return 1;
	}
	ativos[posicao].produto = atoi(codigo_prod_orc_gchar);
	
	gtk_entry_set_text(GTK_ENTRY(descricao_prod_orc_entry[posicao]),campos[0]);
	if(strlen(campos[1])>15)
	{
		campos[1][15] = '.';
		campos[1][15] = '\0';
	}
	gtk_label_set_text(GTK_LABEL(qnt_prod_orc_label[posicao]),campos[1]);
	gtk_widget_grab_focus(subgrp_prod_orc_cod_entry[posicao]);
	return 0;
}
