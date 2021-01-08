int address_terc()
{
	endereco_ter = (gchar *)gtk_entry_get_text(GTK_ENTRY(address_ter_field));
	if(strlen(endereco_ter)<=0){
		popup(NULL,"Por favor insira o endereco do terceiro");
		gtk_widget_grab_focus(GTK_WIDGET(address_ter_field));
		return 1;
	}

	int num=analisa_ender(endereco_ter);
	if( num ){
		char *num_txt = (gchar*) gtk_entry_get_text(GTK_ENTRY(address_num_field));
		if(!atoi(num_txt)){

			char *num_txt2 = malloc(12);
			sprintf(num_txt2,"%i",num);
			gtk_entry_set_text(GTK_ENTRY(address_num_field),num_txt2);

			int pos_virgula;
			for(int cont=0;cont<strlen(endereco_ter);cont++){
				if(endereco_ter[cont] == ','){
					pos_virgula = cont;
				}
			}
			if(pos_virgula && pos_virgula < strlen(endereco_ter)){
				char *novo_endereco = strdup(endereco_ter);
				novo_endereco[pos_virgula] = '\0';
				gtk_entry_set_text(GTK_ENTRY(address_ter_field),novo_endereco);
			}
		}
	}

	if(strlen(endereco_ter)>MAX_ADR_LEN)
	{
		popup(NULL,"Endereco muito grande\nPor favor use abreviações");
		gtk_widget_grab_focus(address_ter_field);
		return 1;
	}

	gtk_widget_grab_focus(address_num_field);

	g_print("endereco: %s\n",endereco_ter);
	return 0;
}
