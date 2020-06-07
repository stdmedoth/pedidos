int cancela_orc()
{
	char code[MAX_CODE_LEN];
	
	cont=0;

	while(cont<MAX_PROD_ORC)
	{
		if(ativos[cont].id==1)
		{
			preco_alterado[cont] = 0;
			valor_orig[cont] = 0;
			tirar_linha(cont);			
		}
		cont++;
	}
	
	cont=0;
	while(cont<MAX_PROD_ORC)
	{
		ativos[cont].id = 0;
		excluidos[cont].id = 1;
		preco_alterado[cont] = 0;
		valor_orig[cont] = 0;
		cont++;
	}	
	
	sprintf(code,"%i",tasker("orcamentos"));
	gtk_entry_set_text(GTK_ENTRY(codigo_orc_entry),code);
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_name_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_end_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_tel_entry),"");
	
	alerta_obs = 0;
	tipo_pag = 0;
	itens_qnt = 1;
	cont=1;
	ativos_qnt=1;
	rec_altera_qnt=1;
	alterando_orc = 0;
	concluindo_orc=0;
	aviso_estoque = 0;
	
	adicionar_linha_orc();
	gtk_widget_set_sensitive(alterar_orc_button,TRUE);
	
	return 0;
}
