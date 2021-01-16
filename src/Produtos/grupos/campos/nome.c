int nome_grp(){
	grpnome = (gchar*) gtk_entry_get_text(GTK_ENTRY(nome_grp_entry));
	if(!strlen(grpnome)){
		popup(NULL,"Insira um nome para o grupo");
		gtk_widget_grab_focus(nome_grp_entry);
		return 1;
	}

	if(strlen(grpnome)>MAX_GRP_LEN){
		popup(NULL,"Nome muito grande para o grupo");
		gtk_widget_grab_focus(nome_grp_entry);
		return 1;
	}
	gtk_widget_grab_focus(confirma_grp_button);
	return 0;
}
