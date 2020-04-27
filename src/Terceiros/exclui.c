int verifica_chaves()
{
	char *query;
	query = malloc(MAX_QUERY_LEN);
	gchar *cod_delel;
	cod_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(code_ter_field));
	//cliente - precos
	sprintf(query,"select * from precos where terceiro = %s;",cod_delel);
	vetor = consultar(query);
	if(vetor ==NULL)
	{
		popup(NULL,"Erro ao tentar verificar pedidos para o terceiro");
		return 1;
	}	
	if((campos = mysql_fetch_row(vetor))!=NULL)
	{
		popup(NULL,"Existem Precos para esse Cliente");
		return 1;
	}
	
	//fornecedor - produtos
	sprintf(query,"select * from produtos where fornecedor = %s",cod_delel);
	vetor = consultar(query);
	if(vetor ==NULL)
	{
		popup(NULL,"Erro ao tentar verificar pedidos para o terceiro");
		return 1;
	}	
	if((campos = mysql_fetch_row(vetor))!=NULL)
	{
		popup(NULL,"Existem Produtos para esse Fornecedor");
		return 1;
	}
	
	//cliente - pedidos
	sprintf(query,"select * from pedidos where cliente = %s",cod_delel);
	vetor = consultar(query);
	if(vetor ==NULL)
	{
		popup(NULL,"Erro ao tentar verificar pedidos para o terceiro");
		return 1;
	}	
	if((campos = mysql_fetch_row(vetor))!=NULL)
	{
		popup(NULL,"Existem Pedidos para esse cliente");
		return 1;
	}
	
	//pedidos - vendedor
	sprintf(query,"select * from pedidos where vendedor = %s",cod_delel);
	vetor = consultar(query);
	if(vetor ==NULL)
	{
		popup(NULL,"Erro ao tentar verificar pedidos para o terceiro");
		return 1;
	}	
	if((campos = mysql_fetch_row(vetor))!=NULL)
	{
		popup(NULL,"Existem Pedidos para esse vendedor");
		return 1;
	}
	
	return 0;
}
int exclui_ter(GtkWidget *botao,gpointer *ponteiro)
{
	char stringer[10];
	char query[100];
	gchar *cod_delel;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	cod_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(code_ter_field));
	sprintf(query,"select code from terceiros where code = '%s';",cod_delel);
	autologger(query);
	estado = consultar(query);
	campo = mysql_fetch_row(estado);
	if(campo==NULL)
	{
		popup(NULL,"Terceiro já não existe");
		sprintf(stringer,"%i",tasker("terceiros"));
		gtk_entry_set_text(GTK_ENTRY(code_ter_field),stringer);
		gtk_entry_set_text(GTK_ENTRY(name_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(doc_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(address_ter_field),"");
		gtk_combo_box_set_active(GTK_COMBO_BOX(type_ter_field),0);
		gtk_entry_set_text(GTK_ENTRY(telefone_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(contatot_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(celular_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(contatoc_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(email_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(contatoe_ter_field),"");
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_ter_field));
		gtk_text_buffer_get_start_iter (buffer,&inicio);
		gtk_text_buffer_get_end_iter (buffer,&fim);
		gtk_text_buffer_delete (buffer,&inicio,&fim);	
		gtk_widget_set_sensitive(GTK_WIDGET(botao_mais),FALSE);		
		gtk_widget_grab_focus(GTK_WIDGET(listar_ter_buttom));
		return 1;
	}
	
	if(verifica_chaves()!=0)
		return 1;
	sprintf(query,"delete from terceiros where code = '%s';",cod_delel);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao tentar excluir terceiro");
		return 1;
	}
	query[0] = '\0';
	sprintf(query,"select code from terceiros where code = '%s';",cod_delel);
	estado = consultar(query);
	campo = mysql_fetch_row(estado);
	if(campo==NULL)
	{
		popup(NULL,"Deletado com sucesso");
		sprintf(stringer,"%i",tasker("terceiros"));
		gtk_entry_set_text(GTK_ENTRY(code_ter_field),stringer);
		gtk_entry_set_text(GTK_ENTRY(name_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(doc_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(address_ter_field),"");
		gtk_combo_box_set_active(GTK_COMBO_BOX(type_ter_field),0);
		gtk_entry_set_text(GTK_ENTRY(telefone_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(contatot_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(celular_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(contatoc_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(email_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(contatoe_ter_field),"");
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_ter_field));
		gtk_text_buffer_get_start_iter (buffer,&inicio);
		gtk_text_buffer_get_end_iter (buffer,&fim);
		gtk_text_buffer_delete (buffer,&inicio,&fim);	
		gtk_widget_set_sensitive(GTK_WIDGET(botao_mais),FALSE);		
		gtk_widget_grab_focus(GTK_WIDGET(code_ter_field));
		alterando_ter=0;
		return 0;

	}
	else
	{
		popup(NULL,"Não foi possivel deletar");
	}
	return 0;
}
