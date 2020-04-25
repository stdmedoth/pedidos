int uf_terc()
{
	uf_ter = (gchar *)gtk_entry_get_text(GTK_ENTRY(uf_ter_field));
	if(strlen(uf_ter)<=0)
	{
		if(terceiros.criticar.uf==0)
		{
			uf_ter = malloc(sizeof(char*)*MAX_CID_LEN);
			strcpy(uf_ter,"");
			vet_erro[UF_ERR] = 0;
			return 0;
		}
		popup(NULL,"Por favor insira a uf do terceiro");
		gtk_widget_grab_focus(GTK_WIDGET(uf_ter_field));
		vet_erro[UF_ERR] = 1;
		return 1;		
	}
	if(strlen(uf_ter)>MAX_CID_LEN)
	{
		popup(NULL,"Nome da Cidade muito grande\nPor favor use abreviações");
		gtk_widget_grab_focus(uf_ter_field);
		vet_erro[UF_ERR]=1;
		return 1;
	}
	vet_erro[UF_ERR]=0;
	gtk_widget_grab_focus(address_num_field);
	g_print("uf: %s\n",uf_ter);
	return 0;
}


