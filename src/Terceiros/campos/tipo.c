#define MAX_TIPO_LEN 20

int terci_tipo=0;

int set_cliente()
{
	gtk_entry_set_text(GTK_ENTRY(type_ter_field),"Cliente");
	tipo_ter = (gchar *) gtk_entry_get_text(GTK_ENTRY(type_ter_field));
	
	if(strlen(tipo_ter)<=0)
	{
		if(terceiros.criticar.tipo==0)
		{
			strcpy(tipo_ter,"");
			gtk_widget_grab_focus(prazo_ter_field);
			return 0;
		}
		popup(NULL,"Tipo Terceiro deve ser inserido");
		return 1;
	}
	if(strlen(tipo_ter)>=MAX_TIPO_LEN)
	{
		popup(NULL,"Tipo de terceiro muito grande\nPor favor use poucos caracteres");
		gtk_widget_grab_focus(type_ter_field);
		vet_erro[TIP_ERR]=1;
		return 1;
	}
	else
	{
		vet_erro[TIP_ERR]=0;
		terci_tipo=1;
		gtk_widget_grab_focus(prazo_ter_field);
	}
	g_print("tipo: %s\n",tipo_ter);
	gtk_widget_destroy(GTK_WIDGET(win_tipo_ter));
	return 0;
}

int set_fornecedor()
{
	gtk_entry_set_text(GTK_ENTRY(type_ter_field),"Fornecedor");
	tipo_ter = (gchar *) gtk_entry_get_text(GTK_ENTRY(type_ter_field));
	if(strlen(tipo_ter)>MAX_TIPO_LEN)
	{
		popup(NULL,"Tipo de terceiro muito grande\nPor favor use poucos caracteres");
		gtk_widget_grab_focus(type_ter_field);
		vet_erro[TIP_ERR]=1;
		return 1;
	}
	else
	{
		vet_erro[TIP_ERR]=0;
		terci_tipo=2;
		gtk_widget_grab_focus(prazo_ter_field);
	}
	g_print("tipo: %s\n",tipo_ter);
	gtk_widget_destroy(GTK_WIDGET(win_tipo_ter));
	return 0;
}

int janela_tipo_ter()
{
	GtkWidget *cliente,*fornecedor,*div;
	win_tipo_ter = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(win_tipo_ter), TRUE);
	gtk_window_set_position(GTK_WINDOW(win_tipo_ter),3);
	cliente = gtk_button_new_with_label("Cliente");
	fornecedor = gtk_button_new_with_label("Fornecedor");
	div = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(div),cliente,0,0,0);
	gtk_widget_set_size_request(cliente,200,50);
	gtk_widget_set_size_request(fornecedor,200,50);
	gtk_box_pack_start(GTK_BOX(div),fornecedor,0,0,0);
	gtk_container_add(GTK_CONTAINER(win_tipo_ter),div);
	gtk_widget_set_size_request(win_tipo_ter,200,100);

	g_signal_connect(GTK_BUTTON(cliente),"clicked",G_CALLBACK(set_cliente),NULL);
	g_signal_connect(GTK_BUTTON(fornecedor),"clicked",G_CALLBACK(set_fornecedor),NULL);
	gtk_widget_show_all(win_tipo_ter);
	return 0;
}
