void pega_data(GtkWidget *widget, GtkEntry *entry)
{
	guint dia,mes,ano;
	char data[15];
	gtk_calendar_get_date(GTK_CALENDAR(calendario_data),&ano,&mes,&dia);
	sprintf(data,"%i-%i-%i", ano, mes+1, dia);
	gtk_entry_set_text(pesquisa_global_alvo,data);
	gtk_widget_activate(GTK_WIDGET(pesquisa_global_alvo));
	gtk_widget_destroy(psq_datas_window);
}

void psq_data(GtkWidget *widget, GtkWidget *cod_grp_entry)
{
	GtkWidget *caixa_grande;
	GtkWidget *botao_seleciona, *botao_cancela, *botao_fixed;
	psq_datas_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(psq_datas_window),3);
	gtk_window_set_title(GTK_WINDOW(psq_datas_window),"Datas");
	if(personalizacao.janela_keep_above == 1)
		gtk_window_set_keep_above(GTK_WINDOW(psq_datas_window),TRUE);


	calendario_data = gtk_calendar_new();
	botao_fixed = gtk_fixed_new();
	botao_seleciona = gtk_button_new();
	botao_cancela = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(botao_seleciona),gtk_image_new_from_file(IMG_OK));
	gtk_button_set_image(GTK_BUTTON(botao_cancela),gtk_image_new_from_file(IMG_CANCEL));
	caixa_grande = gtk_box_new(1,0);

	pesquisa_global_alvo = GTK_ENTRY(cod_grp_entry);

	gtk_fixed_put(GTK_FIXED(botao_fixed),botao_seleciona,50,0);
	gtk_fixed_put(GTK_FIXED(botao_fixed),botao_cancela,100,0);

	gtk_box_pack_start(GTK_BOX(caixa_grande),calendario_data,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),botao_fixed,0,0,5);
	gtk_container_add(GTK_CONTAINER(psq_datas_window),caixa_grande);

	g_signal_connect(botao_seleciona,"clicked",G_CALLBACK(pega_data),pesquisa_global_alvo);
	gtk_widget_grab_focus(botao_seleciona);

	gtk_widget_show_all(psq_datas_window);
}
