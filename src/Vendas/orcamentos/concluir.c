static int concluir_orc()
{
	int cont=0,erro=0;
	char *query;
	query = malloc(MAX_QUERY_LEN);
	sprintf(query,"select * from orcamentos where code = %s",codigo_orc_gchar);
	vetor = consultar(query);
	if(alterando_orc==1)
	{
		popup(NULL,"Função Alterar ainda não desenvolvida");
		return 1;
	}
	if(vetor!=NULL)
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
			sprintf(query,"insert into Produto_Orcamento(code,item,produto,unidades,valor_unit,desconto,total) values(%s,%i,%i,%s,%s,%s,%s);",codigo_orc_gchar,cont,ativos[cont].produto, ativos[cont].qnt_c, ativos[cont].preco_c, ativos[cont].desconto_c ,ativos[cont].total_c);
			erro = enviar_query(query);
			if(erro != 0 )
			{
				popup(NULL,"Erro ao tentar gerar orçamento");
				return 1;
			}
			sprintf(query,"update orcamentos set total = (select sum(total) from Produto_Orcamento where code = %s) where code = %s",codigo_orc_gchar,codigo_orc_gchar);
			erro = enviar_query(query);
			if(erro != 0 )
			{
				popup(NULL,"Erro ao tentar gerar orçamento");
				return 1;
			}
		}
	}
	gtk_widget_destroy(janela_orcamento);
	vnd_orc();	
	popup(NULL,"Orcamento concluido");
	alterando_orc = 0;
	return 0;
}
