int altera_subgrupo(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	subgrpcode = malloc(MAX_CODE_LEN);
	subgrpcode = (gchar*) gtk_entry_get_text(GTK_ENTRY(cod_subgrp_entry));
	char query[MAX_QUERY_LEN];

	sprintf(query,"select nome,pai from grupos where code = %s",subgrpcode);
	if((res = consultar(query))==NULL)
	{
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Subgrupo não existente");
		gtk_widget_grab_focus(cod_subgrp_entry);
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(nome_subgrp_entry),row[0]);
	gtk_entry_set_text(GTK_ENTRY(cod_subgrp_pai_entry),row[1]);
	gtk_widget_activate(nome_subgrp_entry);
	gtk_widget_activate(cod_subgrp_pai_entry);
	gtk_widget_grab_focus(nome_subgrp_entry);
	alterando_subgrp = 1;
	gtk_widget_set_sensitive(cod_subgrp_entry,FALSE);
	gtk_widget_set_sensitive(psq_subgrpo_button,FALSE);
	gtk_widget_set_sensitive(altera_subgrp_button,FALSE);
	return 0;
}
