int emitir_ped()
{	
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	char formato_preco[MAX_PRECO_LEN];
	int cont=0;
	
	if(strlen(gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)))<=0)
	{
		gtk_widget_grab_focus(ped_cod_entry);
		popup(NULL,"Insira o código do orcamento");
		return 1;
	}
	
	//verificando status do pedido
	sprintf(query,"select status from pedidos where code = %s",
	gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)));
	
	res = consultar(query);	
	if(res==NULL)
	{
		popup(NULL,"Erro ao buscar valor total nos dados");
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Pedido não criado");
		return 1;
	}
	
	if(atoi(row[0])==1)
	{
		popup(NULL,"Pedido já emitido");
		return 1;
	}
	if(atoi(row[0])==2)
	{
		popup(NULL,"Pedido cancelado");
		return 1;
	}
	
	if(gtk_combo_box_get_active(GTK_COMBO_BOX(ped_est_combo))<0)
	{
		popup(NULL,"Selecione um estoque");
		gtk_widget_grab_focus(ped_est_combo);
		return 1;
	}
	
	//calculando financeiro
	sprintf(query,"select SUM(p.total),o.total,cliente,dia from Produto_Orcamento as p inner join orcamentos as o on p.code = o.code where o.code = %s",
	gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)));

	res = consultar(query);	
	if(res==NULL)
	{
		popup(NULL,"Erro ao buscar valor total nos dados");
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Sem valor para faturamento");
		return 1;
	}
	
	if(atoi(row[0])!=atoi(row[1]))
	{
		popup(NULL,"Valor total dos produtos diferindo valor total do orcamento");
		return 1;
	}

	//tipo_mov
	//0 = manual
	//1 = venda
	//2 = compra
	//3 = devolucao venda
	//4 = devolucao compra
			
	sprintf(query,"insert into faturamento(pedido,entrada,cliente,data_mov,tipo_mov) values(%s,%s,%s,'%s',2)",
	gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)),row[0],row[2],row[3]);

	
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao inserir valor total");
		return 1;
	}
		
	//calculando estoques
	
	sprintf(query,"select p.produto, p.subgrupo, p.unidades, o.cliente, o.dia from Produto_Orcamento as p inner join orcamentos as o on p.code = o.code where o.code = %s",
	gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)));

	res = consultar(query);

	if(res==NULL)
	{
		popup(NULL,"Erro ao buscar estoque para produto nos dados");
		return 1;
	}
	
	while((row = mysql_fetch_row(res))!=NULL)
	{
		//tipo_mov
		//1 = manual
		//2 = venda
		//3 = compra
		//4 = devolucao venda
		//5 = devolucao compra
		
		sprintf(query,"insert into movimento_estoque(estoque,pedido, produto, subgrupo, saidas, cliente, data_mov, tipo_mov) values(%i,%s,%s,%s,%s,%s,'%s', 2)",
		gtk_combo_box_get_active(GTK_COMBO_BOX(ped_est_combo)),
		gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)),
		row[0], row[1], row[2],row[3],row[4]);
		if(enviar_query(query)!=0) 	
		{
			popup(NULL,"Erro ao dar entrada no estoque");
			return 1;
		}
		cont++;
	}
	if(cont==0)
	{
		popup(NULL,"Estoque sem nenhuma movimentação");
	}
	
	sprintf(query,"select cliente,dia,total from orcamentos where code = %s",gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)));
	res = consultar(query);
	if(res==NULL)
	{
		popup(NULL,"Erro ao buscar dados para fechar o pedido");
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Pedido não encontrado");
		return 1;
	}
		
	
	sprintf(query,"update pedidos set cliente = %s, data_mov = '%s', total = %s, status = 1 where code = %s",
	row[0],row[1],row[2],gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)));
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao inserir dados para fechar o pedido");
		return 1;
	}
	
	
	popup(NULL,"Pedido emitido com sucesso!");
	return 0;
}
