int nome_subgrp()
{
	subgrpnome = malloc(MAX_GRP_LEN);
	subgrpnome = (gchar*) gtk_entry_get_text(GTK_ENTRY(nome_subgrp_entry));
	if(strlen(subgrpnome)>MAX_GRP_LEN)
	{
		popup(NULL,"O nome está muito extenso");
		return 1;
	}
	gtk_widget_grab_focus(cod_subgrp_pai_entry);
	return 0;
}
