int exclui_subgrupo(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	gchar *nome;
	char query[MAX_QUERY_LEN];
	subgrpcode = malloc(MAX_CODE_LEN);
	subgrpcode = (gchar*) gtk_entry_get_text(GTK_ENTRY(cod_subgrp_entry));
	if(strlen(subgrpcode)<=0)
	{
		popup(NULL,"Insira um código para o subgrupo");
		gtk_widget_grab_focus(cod_subgrp_entry);
		return 1;
	}
	if(strlen(subgrpcode)>MAX_CODE_LEN)
	{
		popup(NULL,"Código muito grande para o subgrupo");
		gtk_widget_grab_focus(cod_subgrp_entry);
		return 1;
	}
	sprintf(query,"select nome from grupos where code = %s",subgrpcode);
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
	sprintf(query,"delete from grupos where code = %s",subgrpcode);
	if(enviar_query(query)!=0)
	{
		return 1;
	}
	cancela_subgrupo();
	popup(NULL,"Subgrupo excluido com sucesso");
	gtk_widget_grab_focus(cod_subgrp_entry);
	return 0;
}
