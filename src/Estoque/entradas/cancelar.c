void est_ent_cancelar_fun()
{
	char code[MAX_CODE_LEN];
	cancelando_mov_ent_est=1;
	gtk_entry_set_text(GTK_ENTRY(est_ent_campo_nome_prod),"");
	gtk_entry_set_text(GTK_ENTRY(est_ent_campo_nome_client),"");
	gtk_entry_set_text(GTK_ENTRY(est_ent_data_entry),data_sys);
	gtk_entry_set_text(GTK_ENTRY(est_ent_client_entry),"");
	gtk_entry_set_text(GTK_ENTRY(est_ent_prod_entry),"");
	gtk_entry_set_text(GTK_ENTRY(est_ent_qnt_entry),"");
	gtk_entry_set_text(GTK_ENTRY(est_ent_ped_entry),"");

	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(est_ent_obs_view));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), "", 0);

	gtk_combo_box_set_active(GTK_COMBO_BOX(est_ent_tipo_combo),0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(est_ent_est_combo),0);
	sprintf(code,"%i",tasker("movimento_estoque"));
	gtk_entry_set_text(GTK_ENTRY(est_ent_cod_entry),code);
	gtk_widget_grab_focus(est_ent_client_entry);
	alterando_mov_ent_est=0;
	concluindo_mov_ent_est=0;
	cancelando_mov_ent_est=0;
	gtk_widget_set_sensitive(est_ent_altera_button,TRUE);
	gtk_widget_set_sensitive(est_ent_cod_entry,TRUE);
	gtk_widget_set_sensitive(est_ent_psqcod_button,TRUE);
}
