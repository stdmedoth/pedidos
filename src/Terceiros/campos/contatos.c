int mostrar_contatoc1()
{
	g_print("contatoc1\n");
	gtk_widget_show(contatoc1_label);
	gtk_widget_show(contatoc1_entry);
	return 0;
}

int mostrar_contatot1()
{
	g_print("contatot1");
	gtk_widget_show(contatot1_label);
	gtk_widget_show(contatot1_entry);
//	g_signal_connect(GTK_ENTRY(contatot1_entry),"activate",G_CALLBACK(gtk_widget_grab_focus),);
	return 0;
}
int contc1()
{
	gtk_widget_grab_focus(telefone1_entry);
	return 0;
}
int contt1()
{
	//gtk_widget_grab_focus(telefone1_entry);
	return 0;
}
int cel1()
{
	gtk_widget_grab_focus(contatoc1_entry);
	return 0;
}
int tel1()
{
	gtk_widget_grab_focus(contatot1_entry);
	return 0;
}
