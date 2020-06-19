void gera_orc_ped()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	char msg[MAX_QUERY_LEN];
	
	if(codigo_orc()!=0)
	{
		return ;
	}
	
	sprintf(query,"select code from pedidos where code = %s",codigo_orc_gchar);
	res = consultar(query);	
	if(res==NULL)
	{
		popup(NULL,"Erro ao buscar existencia do pedido");
		return ;
	}
	if((row = mysql_fetch_row(res))!=NULL)
	{
		popup(NULL,"Orcamento já virou pedido");
		gtk_widget_grab_focus(codigo_orc_entry);
		return ;
	}
		
	sprintf(query,"select code,cliente,dia,total from orcamentos where code = %s",codigo_orc_gchar);
	res = consultar(query);	
	if(res==NULL)
	{
		popup(NULL,"Erro ao buscar valores do orçamento nos dados");
		return ;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Orçamento não existe para ser transformado em pedido");
		gtk_widget_grab_focus(codigo_orc_entry);
		return ;
	}
	
	sprintf(query,"insert into pedidos(code,cliente,data_mov,total,status) values(%s,%s,'%s',%s,0)",row[0],row[1],row[2],row[3]);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Não foi possível inserir os dados no pedido");
		return ;
	}
	sprintf(msg,"Orcamento gerou o pedido %s",row[0]);
	popup(NULL,msg);
}
