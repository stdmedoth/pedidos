/* cria data para o sistema*/

GtkWidget *pedidos_get_calendario(){
	GtkWidget *calendario = gtk_calendar_new();
	GtkWidget *calendario_box = gtk_box_new(0,0);
	GtkWidget *calendario_frame = gtk_frame_new("Calendário");

	GtkWidget *box = gtk_box_new(1,0);

	GtkWidget *setar_data = gtk_button_new_with_label("Configurar");
	GtkWidget *cancelar = gtk_button_new_with_label("Cancelar");
	GtkWidget *opcoes_frame = gtk_frame_new("Ações");
	GtkWidget *opcoes_box = gtk_box_new(0,0);

	gtk_container_add(GTK_CONTAINER(calendario_frame), calendario);
	gtk_box_pack_start(GTK_BOX(box), calendario_frame,0,0,5);

	gtk_box_pack_start(GTK_BOX(opcoes_box), setar_data,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_box), cancelar,0,0,5);
	gtk_container_add(GTK_CONTAINER(opcoes_frame), opcoes_box);
	gtk_box_pack_start(GTK_BOX(box), opcoes_frame,0,0,5);

	gtk_calendar_mark_day(GTK_CALENDAR(calendario), atoi(dia_sys));
	gtk_calendar_select_month(GTK_CALENDAR(calendario), atoi(mes_sys)-1, atoi(ano_sys)-1990);
	gtk_calendar_select_day(GTK_CALENDAR(calendario), atoi(dia_sys));
	return box;
}

int pegar_data()
{
	struct tm *tempo_struct;
	time_t tempo;
	time(&tempo);
	tempo_struct = localtime(&tempo);

	strcpy(dia_sys,"");
	strcpy(mes_sys,"");
	strcpy(ano_sys,"");
	strcpy(data_sys,"");

	if(tempo_struct->tm_mday < 10)
	{
		sprintf(dia_sys,"0%i",tempo_struct->tm_mday);
	}
	else
	{
		sprintf(dia_sys,"%i",tempo_struct->tm_mday);
	}

	if(tempo_struct->tm_mon < 9)
	{
		sprintf(mes_sys,"0%i",tempo_struct->tm_mon+1);
	}
	else
	{
		sprintf(mes_sys,"%i",tempo_struct->tm_mon+1);
	}

	sprintf(ano_sys,"%i",tempo_struct->tm_year+1900);

	sprintf(data_sys,"%s/%s/%s",dia_sys,mes_sys,ano_sys);
	return 0;
}
