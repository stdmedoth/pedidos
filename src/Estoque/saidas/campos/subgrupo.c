int est_said_subgrp_fun()
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *estado;
	MYSQL_ROW campo;

	est_said_subgrp_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_said_subgrp_entry));
	
	if(strlen(est_said_subgrp_gchar)<=0)
	{
		popup(NULL,"Insira o código");
		gtk_widget_grab_focus(est_said_subgrp_entry);
		return 1;
	}
	
	sprintf(query,"select nome from grupos where code = %s",est_said_subgrp_gchar);
	if((estado = consultar(query))==NULL)
		return 1;
	if((campo = mysql_fetch_row(estado))==NULL)
	{
		popup(NULL,"O subgrupo não existe");
		return 1;
	}
	
	gtk_entry_set_text(GTK_ENTRY(est_said_campo_subgrp_prod),campo[0]);	
	
	
	gtk_widget_grab_focus(est_said_qnt_entry);
	
	return 0;
}
