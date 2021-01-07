void get_sysdata_from_calendar(GtkCalendar *calendar, gpointer user_data){

	guint dia=0, mes=0, ano=0;
	gtk_calendar_get_date(calendar, &ano, &mes, &dia);
	if(dia < 10){
		sprintf(dia_sys,"0%i",dia);
	}
	else{
		sprintf(dia_sys,"%i",dia);
	}

	if(mes < 10){
		sprintf(mes_sys,"0%i",mes+1);
	}
	else{
		sprintf(mes_sys,"%i",mes+1);
	}

	sprintf(ano_sys,"%i",ano);

	sprintf(data_sys,"%s/%s/%s",dia_sys,mes_sys,ano_sys);
	gtk_entry_set_text(GTK_ENTRY(desktop_calendar_entry), data_sys);
}

void set_sysdata_from_calendar_entry(GtkWidget *entry, GtkCalendar *calendar){

	gchar *data_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(entry));
	if(!strlen(data_gchar)){
		data_gchar = strdup(data_sys);
	}
	gchar *format = formatar_data(data_gchar);
	if(!format){
		return ;
	}
	gtk_entry_set_text(GTK_ENTRY(entry), format);
	int dia=0, mes=0, ano=0;
	if(sscanf(format,"%d/%d/%d", &dia, &mes, &ano)==EOF){
		popup(NULL,"Não foi possível interpretar data");
		return ;
	}
	gtk_calendar_select_month(GTK_CALENDAR(calendar), mes-1, ano);
	gtk_calendar_select_day(GTK_CALENDAR(calendar), dia);
	gtk_calendar_mark_day(GTK_CALENDAR(calendar), dia);

	return ;
}

void desktop_calendar_reset(GtkWidget *button, gpointer calendar){

	pegar_data();
	gtk_calendar_select_month(GTK_CALENDAR(calendar), atoi(mes_sys)-1, atoi(ano_sys));
	gtk_calendar_select_day(GTK_CALENDAR(calendar), atoi(dia_sys));
	gtk_calendar_mark_day(GTK_CALENDAR(calendar), atoi(dia_sys));

	get_sysdata_from_calendar(GTK_CALENDAR(calendar), desktop_calendar_entry);

}

GtkWidget *get_desktop_calendario(){

	desktop_calendar = gtk_calendar_new();
	GtkWidget *calendario_box = gtk_box_new(0,0);
	GtkWidget *calendario_frame = gtk_frame_new("Calendário");

	GtkWidget *box = gtk_box_new(1,0);

	desktop_calendar_entry = gtk_entry_new();
	GtkWidget *resetar_button = gtk_button_new_with_label("Resetar");
	GtkWidget *opcoes_frame = gtk_frame_new("Ações");
	GtkWidget *opcoes_box = gtk_box_new(0,0);

	gtk_widget_set_name(calendario_frame, "calendario_frames");
	gtk_widget_set_name(opcoes_frame, "calendario_frames");

	gtk_container_add(GTK_CONTAINER(calendario_frame), desktop_calendar);
	gtk_box_pack_start(GTK_BOX(box), calendario_frame,0,0,10);
	gtk_widget_set_size_request(box, 200, 300);
	gtk_widget_set_size_request(calendario_frame, 200, 200);

	gtk_box_pack_start(GTK_BOX(opcoes_box), resetar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_box), desktop_calendar_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(opcoes_frame), opcoes_box);

	gtk_box_pack_start(GTK_BOX(box), opcoes_frame,0,0,0);

	g_signal_connect(resetar_button, "clicked", G_CALLBACK(desktop_calendar_reset), desktop_calendar);
	g_signal_connect(desktop_calendar, "day-selected", G_CALLBACK(get_sysdata_from_calendar), desktop_calendar_entry);
	g_signal_connect(desktop_calendar_entry, "activate", G_CALLBACK(set_sysdata_from_calendar_entry), desktop_calendar);

	gtk_calendar_select_month(GTK_CALENDAR(desktop_calendar), atoi(mes_sys)-1, atoi(ano_sys));
	gtk_calendar_select_day(GTK_CALENDAR(desktop_calendar), atoi(dia_sys));
	gtk_calendar_mark_day(GTK_CALENDAR(desktop_calendar), atoi(dia_sys));
	gtk_entry_set_text(GTK_ENTRY(desktop_calendar_entry), data_sys);
	return box;
}


/* cria data para o sistema*/
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

	if(tempo_struct->tm_mday < 10){
		sprintf(dia_sys,"0%i",tempo_struct->tm_mday);
	}
	else{
		sprintf(dia_sys,"%i",tempo_struct->tm_mday);
	}

	if(tempo_struct->tm_mon < 9){
		sprintf(mes_sys,"0%i",tempo_struct->tm_mon+1);
	}
	else{
		sprintf(mes_sys,"%i",tempo_struct->tm_mon+1);
	}

	sprintf(ano_sys,"%i",tempo_struct->tm_year+1900);

	sprintf(data_sys,"%s/%s/%s",dia_sys,mes_sys,ano_sys);
	return 0;
}
