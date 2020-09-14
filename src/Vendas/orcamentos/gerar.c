int gerar_orc()
{
	codigo_orc_gchar = (gchar *)gtk_entry_get_text(GTK_ENTRY(codigo_orc_entry));
	if(codigo_orc_gchar)
		gerar_orcs( atoi(codigo_orc_gchar) );
	return 0;

	return 0;
}
