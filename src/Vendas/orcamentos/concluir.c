static int concluir_orc()
{
	int cont=0,erro=0;
	char *query;
	query = malloc(MAX_QUERY_LEN);
	if(alterando_orc==0)
	{
		sprintf(query,"select * from orcamentos where code = %s",codigo_orc_gchar);
		g_print("%s\n",query);
		vetor = consultar(query);
		if(vetor==NULL)
		{
			popup(NULL,"Erro na verificação da existencia do orcamento");
			g_print("Erro na verificação da existencia do orcamento\n");
			autologger("Erro na verificação da existencia do orcamento");
			autologger(query);
			return 1;
		}
		campos = mysql_fetch_row(vetor);
		if(campos!=NULL)
		{
			popup(NULL,"Orçamento já existente! verifique o código");
			g_print("Tentou usar código de orcamento já usado\n");
			autologger("Erro na query de codigo no orcamento\nTentou usar código de orcamento já usado\n");
			autologger(query);
			vet_erro[COD_ERR] = 0;
			gtk_widget_grab_focus(codigo_orc_entry);
			return 1;
		}
		sprintf(query,"insert into orcamentos(code,vendedor,cliente,dia,observacoes,total) values(%s,1,%s,'%s-%s-%s','%s',0.0);",codigo_orc_gchar,cliente_orc_gchar,ano_sys,mes_sys,dia_sys,observacoes_orc_gchar);
		erro = enviar_query(query);
		if(erro != 0 )
		{	
			popup(NULL,"Erro ao tentar concluir orçamento");
			return 1;
		}
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
			if(alterando_orc==0)
			{
				sprintf(query,"insert into Produto_Orcamento(code,item,produto,unidades,valor_unit,desconto,total) values(%s,%i,%i,%s,%s,%s,%s);",codigo_orc_gchar,cont,ativos[cont].produto, ativos[cont].qnt_c, ativos[cont].preco_c, ativos[cont].desconto_c ,ativos[cont].total_c);
				erro = enviar_query(query);
				if(erro != 0 )
				{
					popup(NULL,"Erro ao tentar gerar orçamento");
					return 1;
				}			
			}
			else
			{
				if(cont<rec_altera_qnt)
				{
					sprintf(query,"update orcamentos set total = (select sum(total) from Produto_Orcamento where code = %s) where code = %s",codigo_orc_gchar,codigo_orc_gchar);
					erro = enviar_query(query);
					if(erro != 0 )
					{
						popup(NULL,"Erro ao tentar gerar orçamento");
						return 1;
					}
				}
				else
				{
					sprintf(query,"insert into Produto_Orcamento(code,item,produto,unidades,valor_unit,desconto,total) values(%s,%i,%i,%s,%s,%s,%s);",codigo_orc_gchar,cont,ativos[cont].produto, ativos[cont].qnt_c, ativos[cont].preco_c, ativos[cont].desconto_c ,ativos[cont].total_c);
					erro = enviar_query(query);	
				}
			}
		}
	}
	popup(NULL,"Orcamento concluido");
	itens_qnt = 1;
	cont=1;
	ativos_qnt=1;
	rec_altera_qnt = 1;
	alterando_orc = 0;
	return 0;
}
