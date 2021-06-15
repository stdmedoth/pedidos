int cep_terc()
{
	char query[MAX_QUERY_LEN];
	int cont=0,cont2=0;
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char ddd[10];

	gchar *cep_ter2 = (gchar *) gtk_entry_get_text(GTK_ENTRY(cep_ter_field));

	if(strlen(cep_ter2)<=0){
		popup(NULL,"Por favor insira um cep");
		gtk_widget_grab_focus(GTK_WIDGET(cep_ter_field));
		return 1;
	}

	if(concluindo_ter){
		return 0;
	}
	
	if(cep_ter && strlen(cep_ter)){
		if(strcmp(cep_ter,cep_ter2)){
			g_print("diferencao entre cep anterior e atual: %s, %s\n", cep_ter, cep_ter2);
			ter_cep_addr_alterado=0;
			ter_cep_cidade_alterado=0;
			ter_cep_uf_alterado=0;
			ter_cep_bairro_alterado=0;
		}
	}
	cep_ter = strdup(cep_ter2);

	if(strlen(cep_ter)!=CEP_LEN)
	{
		popup(NULL,"Insira o CEP com formato indicado");
		gtk_widget_grab_focus(GTK_WIDGET(cep_ter_field));
		return 1;
	}

	g_print("CEP: %s\n",cep_ter);
	autologger("CEP:");
	autologger(cep_ter);
	if((ter_cep_cidade_alterado) && (ter_cep_uf_alterado) && (ter_cep_bairro_alterado)){
		gtk_widget_grab_focus(address_ter_field);
		return 0;
	}
	sprintf(query,"select l.descricao,l.tipo, c.descricao, l.UF, l.descricao_bairro, c.ddd from logradouro as l inner join cidade as c on l.id_cidade = c.code where CEP = '%s'",cep_ter);
	if(!(vetor = consultar(query)))
	{
		popup(NULL,"Erro na query para CEP");
		gtk_widget_grab_focus(GTK_WIDGET(cep_ter_field));
		return 1;
	}
	if(!(campos = mysql_fetch_row(vetor))){
		if(!concluindo_ter)
			cep_nao_existente_fun(cep_ter);

		tipo_log = gtk_combo_box_get_active(GTK_COMBO_BOX(rua_combo));
		gtk_widget_grab_focus(address_ter_field);
		return 0;
	}

	g_print("cep_len: %li\n",strlen(cep_ter));
	if(campos[0] && !ter_cep_addr_alterado)
		gtk_entry_set_text(GTK_ENTRY(address_ter_field),campos[0]);

	for(cont=0;cont<=6;cont++){
		if(strcmp(campos[1],tip_logds[cont])==0){
			gtk_combo_box_set_active(GTK_COMBO_BOX(rua_combo),cont+1);
			tipo_log = cont+1;
			cont2 = 1;
 		}
	}

	if(cont2==0){
		gtk_combo_box_set_active(GTK_COMBO_BOX(rua_combo),7);
	}

	if(campos[2] && !ter_cep_cidade_alterado)
		gtk_entry_set_text(GTK_ENTRY(cidade_ter_field),campos[2]);

	if(campos[3] && !ter_cep_uf_alterado)
		gtk_entry_set_text(GTK_ENTRY(uf_ter_field),campos[3]);

	if(campos[4] && !ter_cep_bairro_alterado)
		gtk_entry_set_text(GTK_ENTRY(bairro_ter_field),campos[4]);

	if(campos[5])
		sprintf(ddd,"(%s)",campos[5]);

	gtk_widget_grab_focus(address_ter_field);
	g_print("cep: %s\n",cep_ter);
	return 0;
}
