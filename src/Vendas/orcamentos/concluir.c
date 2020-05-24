static int concluir_orc()
{
	int cont=0,erro=0;
	char *query;
	char code[MAX_CODE_LEN];
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
		
		sprintf(query,"insert into orcamentos( code, vendedor, cliente, dia, observacoes, total) values(%s,1,%s,'%s-%s-%s','%s',0.0);",
		codigo_orc_gchar,cliente_orc_gchar,ano_sys,mes_sys,dia_sys,observacoes_orc_gchar);
		
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
			if(codigo_prod_orc(codigo_prod_orc_entry[cont],cont)!=0)
				return 1;		
			if(subgrp_prod_orc(subgrp_prod_orc_cod_entry[cont],cont)!=0)
			if(qnt_prod_orc(qnt_prod_orc_entry[cont],cont)!=0)
				return 1;
			if(preco_prod_orc(preco_prod_orc_entry[cont],cont)!=0)
				return 1;
			if(desconto_prod_orc(desconto_prod_orc_entry[cont],cont)!=0)
					return 1;
			if(total_prod_orc(total_prod_orc_entry[cont],cont)!=0)
				return 1;
			
			if(strlen(ativos[cont].desconto_c)<=0)
			{
				strcpy(ativos[cont].desconto_c,"0.0");
			}
			
			if(alterando_orc==0)
			{
				sprintf(query,"insert into Produto_Orcamento(code,item,produto,subgrupo,unidades,valor_unit,valor_orig,tipodesc,desconto,total) values(%s,%i,%i,%i,%s,%s,%i,%i,%s,%s);",codigo_orc_gchar, cont,ativos[cont].produto, ativos[cont].subgrupo, ativos[cont].qnt_c, ativos[cont].preco_c, preco_alterado[cont], ativos[cont].tipodesc, ativos[cont].desconto_c ,ativos[cont].total_c);
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
					sprintf(query,"update Produto_Orcamento set produto = %i, subgrupo = %i, unidades = %s, valor_unit = %s, valor_orig = %i, tipodesc = %i , desconto = %s, total = %s where code = %s and item = %i",ativos[cont].produto, ativos[cont].subgrupo, ativos[cont].qnt_c, ativos[cont].preco_c, preco_alterado[cont], ativos[cont].tipodesc, ativos[cont].desconto_c ,ativos[cont].total_c,codigo_orc_gchar,cont);
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
						popup(NULL,"Erro ao tentar calcular total");
						return 1;
					}
				}
				else
				{
					sprintf(query,"insert into Produto_Orcamento(code,item,produto,subgrupo,unidades,valor_unit,valor_orig,desconto,total) values(%s,%i,%i,%i,%s,%s,%i,%s,%s);",codigo_orc_gchar,cont,ativos[cont].produto, ativos[cont].subgrupo, ativos[cont].qnt_c, ativos[cont].preco_c, preco_alterado[cont], ativos[cont].desconto_c ,ativos[cont].total_c);
					erro = enviar_query(query);	
				}
			}
			
		}
		sprintf(query,"update orcamentos set total = (select sum(total) from Produto_Orcamento where code = %s) where code = %s",codigo_orc_gchar,codigo_orc_gchar);
		erro = enviar_query(query);
		if(erro != 0 )
		{
			popup(NULL,"Erro ao tentar calcular total");
			return 1;
		}
	}
	popup(NULL,"Orcamento concluido");
	cont=1;
	
	while(cont<MAX_PROD_ORC)
	{
		if(ativos[cont].id==1)
		{
			ativos[cont].id = 0;
			excluidos[cont].id = 1;
			tirar_linha(cont);			
		}
		cont++;
	}
	
	itens_qnt = 1;
	ativos_qnt = 1;
	rec_altera_qnt = 1;

	cont=1;
	
	alterando_orc = 0;

	sprintf(code,"%i",tasker("orcamentos"));
	gtk_entry_set_text(GTK_ENTRY(codigo_orc_entry),code);
	gtk_widget_set_sensitive(cliente_orc_entry,TRUE);
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_name_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_end_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_tel_entry),"");
	
	adicionar_linha_orc();
	
	return 0;
}
