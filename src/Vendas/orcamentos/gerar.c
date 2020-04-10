#include "impressao.c"
#define CLI_ROW_POS 2
#define DATE_QUERY "select DATE_FORMAT(dia,\"%d/%m/%y\") from orcamentos where code = "
#define ORC_PATH "/home/calistu/Desktop/orc.html"
int gerar_orc()
{
	int vnd_orc();

	g_print("gerando orçamento...\n");
	int cont;
	char *query;
	int erro;
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	MYSQL_RES *res;
	MYSQL_ROW *row;
	query = malloc(MAX_QUERY_LEN);
	if(codigo_orc()!=0)
		return 1;
	
	sprintf(query,"select * from orcamentos where code = %s",codigo_orc_gchar);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		g_print("Erro na query de codigo no orcamento\n");
		autologger("Erro na query de codigo no orcamento\n");
		autologger(query);
		vet_erro[COD_ERR] = 0;
		gtk_widget_grab_focus(codigo_orc_entry);
		fclose(orc);
		return 1;
	}
	campos = mysql_fetch_row(vetor);
	if(campos == NULL)
	{
		sprintf(query,"insert into orcamentos(code,vendedor,cliente,dia,total) values(%s,1,%s,'%s-%s-%s',0.0);",codigo_orc_gchar,cliente_orc_gchar,ano_sys,mes_sys,dia_sys);
		erro = enviar_query(query);
		if(erro != 0 )
		{
			popup(NULL,"Erro ao tentar gerar orçamento");
			fclose(orc);
			return 1;
		}
		for(cont=1;cont<itens_qnt-1;cont++)
		{
			if(ativos[cont].id == 1)
			{
				if(codigo_cli_orc()!=0)
					return 1;			
				if(qnt_prod_orc(qnt_prod_orc_entry[cont],cont)!=0)
					return 1;
				if(preco_prod_orc(preco_prod_orc_entry[cont],cont)!=0)
					return 1;
				if(total_prod_orc(total_prod_orc_entry[cont],cont)!=0)
					return 1;
				if(strlen(ativos[cont].desconto_c)<=0)
				{
					strcpy(ativos[cont].desconto_c,"0.0");
				}
				sprintf(query,"insert into Produto_Orcamento(code,produto,unidades,valor_unit,desconto,total) values(%s,%i,%s,%s,%s,%s);",codigo_orc_gchar,ativos[cont].produto, ativos[cont].qnt_c, ativos[cont].preco_c, ativos[cont].desconto_c ,ativos[cont].total_c);
				erro = enviar_query(query);
				if(erro != 0 )
				{
					popup(NULL,"Erro ao tentar gerar orçamento");
					fclose(orc);
					return 1;
				}				
			}
		}
		if(ativos_qnt==0)
		{
			popup(NULL,"Não há produtos no orçamento");
			fclose(orc);
			return 1;
		}
	}
	else
	{
		gtk_entry_set_text(GTK_ENTRY(cliente_orc_entry),campos[CLI_ROW_POS]);
		if(codigo_cli_orc()!=0)
			return 1;			
	}
	orc = fopen(ORC_PATH,"w+");
	
	sprintf(query,"select distinct (%s%s),o.total from orcamentos as o join terceiros as t where o.code = %s",DATE_QUERY,codigo_orc_gchar,codigo_orc_gchar);
	
	vetor = consultar(query);
	if(vetor==NULL)
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		g_print("Erro na query de codigo no orcamento\n");
		autologger("Erro na query de codigo no orcamento\n");
		autologger(query);
		fclose(orc);
		return 1;
	}	
	campos = mysql_fetch_row(vetor);
	if(campos == NULL)
	{
		popup(NULL,"Erro ao tentar receber orçamento");
		fclose(orc);
		return 1;
	}
	fprintf(orc,"<div id=\"caixa-imp\">\n");
	fprintf(orc,"<body>\n");
	if(imp_head()!=0)
		return 1;
	fprintf(orc,"<div id=\"orc-infos\" align=left>\n");
	fprintf(orc,"<table>\n");
	
	fprintf(orc,"<tr>\n");
	fprintf(orc,"<td id=\"info-row1\">Número Orcamento</td>\n");
	//fprintf(orc,"<td id=\"info-row1\">Cliente:</td>\n"); 
	fprintf(orc,"<td id=\"info-row1\">Data</td>\n");
	fprintf(orc,"</tr>\n");
	
	fprintf(orc,"<tr>\n");
	fprintf(orc,"<td>%s</td>\n",codigo_orc_gchar);
	fprintf(orc,"<td>%s</td>\n",campos[0]);
	fprintf(orc,"<tr>\n");
	
	fprintf(orc,"</table>\n");
	fprintf(orc,"</div>\n");
	
	if(imp_cli(cliente_orc_gchar)!=0)
		return 1;
	sprintf(query,"select p.nome,o.unidades,u.nome,o.valor_unit,o.desconto,o.total from Produto_Orcamento as o inner join produtos as p on p.code = o.produto join unidades as u on u.code = p.unidade where o.code = %s;",codigo_orc_gchar);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		g_print("Erro na query de codigo no orcamento\n");
		autologger("Erro na query de codigo no orcamento\n");
		autologger(query);
		vet_erro[COD_ERR] = 0;
		gtk_widget_grab_focus(codigo_orc_entry);
		fclose(orc);
		return 1;
	}
	cont=1;
	fprintf(orc,"<div id=\"separator\">\n");
	fprintf(orc,"</div>");
	fprintf(orc,"<div id=\"campo-itens\">\n");
	fprintf(orc,"<table>\n");
	fprintf(orc,"<tr>\n");
	fprintf(orc,"<td id=\"prod-row1\"></td>\n");
	fprintf(orc,"<td id=\"prod-row1\">Produto</td>\n");
	fprintf(orc,"<td id=\"prod-row1\">Quantidade</td>\n</td>");  
	fprintf(orc,"<td id=\"prod-row1\">Preco <img src=\"%s\" alt=\"\"></td>\n",IMG_MONEY);
	fprintf(orc,"<td id=\"prod-row1\">Desconto </td>\n");
	fprintf(orc,"<td id=\"prod-row1\">Total</td>\n");
	fprintf(orc,"</tr>\n");
	
	while((campos = mysql_fetch_row(vetor))!=NULL)
	{
		fprintf(orc,"<tr>\n");
		fprintf(orc,"<td>Item %i</td>\n",cont);
		fprintf(orc,"<td>%s</td>\n",campos[0]);
		fprintf(orc,"<td>%s %s</td>\n</td>",campos[1],campos[2]);  
		fprintf(orc,"<td>R$ %.2f</td>\n",atof(campos[3]));
		fprintf(orc,"<td>R$ %.2f</td>\n",atof(campos[4]));
		fprintf(orc,"<td>R$ %.2f</td>\n",atof(campos[5]));
		fprintf(orc,"</tr>\n");
		cont++;
	}
	if(cont == 0)
	{
		popup(NULL,"Sem itens no orçamento");
		fclose(orc);
		return 0;
	}
	fprintf(orc,"</table>\n");
	fprintf(orc,"</div>");
	fprintf(orc,"</div>\n");
	fprintf(orc,"</body>\n");
	fprintf(orc,"</div>\n");
	fclose(orc);
	popup(NULL,"Gerado!");
	return 0;
}
