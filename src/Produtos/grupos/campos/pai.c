int codpai_grp(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
	paigrpcode = (gchar*) gtk_entry_get_text(GTK_ENTRY(pai_grp_entry));

  if(!strlen(paigrpcode)){
    paigrpcode = strdup("1");
    gtk_entry_set_text(GTK_ENTRY(pai_grp_entry), paigrpcode);
	//	popup(NULL,"Insira o código do grupo pai");
	//	gtk_widget_grab_focus(pai_grp_entry);
	//	return 1;
	}

  struct _grupo *grupo = grp_get_grupo(atoi(paigrpcode));
  if(!grupo){
    popup(NULL,"Grupo pai não existente");
    return 1;
  }
  grpnivel = grupo->nivel + 1;
  gtk_entry_set_text(GTK_ENTRY(painome_grp_entry), grupo->nome);

	return 0;
}
