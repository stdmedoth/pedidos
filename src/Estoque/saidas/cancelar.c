void est_said_cancelar_fun()
{
	cancelando_mov_said_est=1;
	char code[MAX_CODE_LEN];
	gtk_entry_set_text(GTK_ENTRY(est_said_campo_nome_prod),"");
	gtk_entry_set_text(GTK_ENTRY(est_said_campo_nome_client),"");
	gtk_entry_set_text(GTK_ENTRY(est_said_data_entry),data_sys);
	gtk_entry_set_text(GTK_ENTRY(est_said_client_entry),"");
	gtk_entry_set_text(GTK_ENTRY(est_said_prod_entry),"");
	gtk_entry_set_text(GTK_ENTRY(est_said_qnt_entry),"");
	gtk_entry_set_text(GTK_ENTRY(est_said_ped_entry),"");
	gtk_combo_box_set_active(GTK_COMBO_BOX(est_said_tipo_combo),0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(est_said_est_combo),0);
	sprintf(code,"%i",tasker("movimento_estoque"));
	gtk_entry_set_text(GTK_ENTRY(est_said_cod_entry),code);
	gtk_widget_grab_focus(est_said_client_entry);
	cancelando_mov_said_est=0;
	alterando_mov_said_est=0;
	concluindo_mov_said_est=0;
	gtk_widget_set_sensitive(est_said_altera_button,TRUE);

}
