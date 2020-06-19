int est_ent_subgrp_fun()
{
	char query[MAX_QUERY_LEN],**familia_char;
	char *source,*dest;
	int grupo_len;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	
	familia_char = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO-1);
	source = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO);
	dest = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO);
	
	est_ent_subgrp_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_ent_subgrp_entry));
	
	if(strlen(est_ent_subgrp_gchar)<=0)
	{
		popup(NULL,"Insira o código");
		gtk_entry_set_text(GTK_ENTRY(est_ent_campo_subgrp_prod),"");
		gtk_widget_grab_focus(est_ent_subgrp_entry);
		return 1;
	}
	
	if((grupo_len = rec_familia_nome(familia_char, atoi(est_ent_subgrp_gchar) ))<=0)
		return 1;
	
	memset(dest,0x0,strlen(dest));
	memset(source,0x0,strlen(source));
	
	for(int cont=grupo_len;cont>0;cont--)
	{
		sprintf(dest,"%s %s",source,familia_char[cont]);
		
		strcpy(source,dest);
	}
	
	gtk_entry_set_text(GTK_ENTRY(est_ent_campo_subgrp_prod),dest);	
	
	
	gtk_widget_grab_focus(est_ent_qnt_entry);
	
	return 0;
}
