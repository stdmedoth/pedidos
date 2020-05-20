int cad_est_sld()
{
	GtkWidget *janela, *caixa_grande;
	GtkWidget *est_sld_prod_cod_frame, *est_sld_prod_cod_fixed;
	GtkWidget *est_sld_cod_frame, *est_sld_cod_fixed;
	GtkWidget *caixa_linha1;
	GtkCssProvider *css_provider;
	GError *erro;
	GtkWidget *est_sld_prod_nome_frame, *est_sld_prod_nome_fixed;
	GtkWidget *caixa_opcoes, *frame_opcoes, *fixed_opcoes;
	
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(janela),"Saldo Estoque");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
	gtk_window_set_icon_name(GTK_WINDOW(janela),"x-package-repository");
	gtk_widget_set_size_request(GTK_WIDGET(janela),450,300);
	
	caixa_grande = gtk_box_new(1,0);
	caixa_opcoes = gtk_box_new(0,0);
	frame_opcoes = gtk_frame_new("Opções");
	fixed_opcoes = gtk_fixed_new();
	caixa_linha1 = gtk_box_new(0,0);
	
	est_sld_concluir_button = gtk_button_new_with_label("Concluir");
	gtk_button_set_image(GTK_BUTTON(est_sld_concluir_button),gtk_image_new_from_file(IMG_OK));
	est_sld_alterar_button = gtk_button_new_with_label("Alterar");
	gtk_button_set_image(GTK_BUTTON(est_sld_alterar_button),gtk_image_new_from_file(IMG_ALTER));
	est_sld_cancelar_button = gtk_button_new_with_label("Cancelar");
	gtk_button_set_image(GTK_BUTTON(est_sld_cancelar_button),gtk_image_new_from_file(IMG_CANCEL));
	est_sld_excluir_button = gtk_button_new_with_label("Excluir");
	gtk_button_set_image(GTK_BUTTON(est_sld_excluir_button),gtk_image_new_from_file(IMG_EXCLUI));
	
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),est_sld_concluir_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),est_sld_alterar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),est_sld_cancelar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),est_sld_excluir_button,0,0,5);
	gtk_container_add(GTK_CONTAINER(frame_opcoes),caixa_opcoes);
	gtk_fixed_put(GTK_FIXED(fixed_opcoes),frame_opcoes,10,10);
	
	est_sld_prod_cod_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(est_sld_prod_cod_entry),5);
	est_sld_prod_cod_fixed = gtk_fixed_new();
	est_sld_prod_cod_frame = gtk_frame_new("Código Produto");
	
	est_sld_cod_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(est_sld_cod_entry),5);
	est_sld_cod_fixed = gtk_fixed_new();
	est_sld_cod_frame = gtk_frame_new("Estoque");	
	
	gtk_container_add(GTK_CONTAINER(est_sld_cod_frame),est_sld_cod_entry);
	gtk_fixed_put(GTK_FIXED(est_sld_cod_fixed),est_sld_cod_frame,20,20);
	
	est_sld_prod_nome_entry = gtk_entry_new();
	gtk_widget_set_sensitive(est_sld_prod_nome_entry,FALSE);
	gtk_entry_set_width_chars(GTK_ENTRY(est_sld_prod_nome_entry),30);
	est_sld_prod_nome_fixed = gtk_fixed_new();
	est_sld_prod_nome_frame = gtk_frame_new("Nome Produto");
	
	gtk_container_add(GTK_CONTAINER(est_sld_prod_cod_frame),est_sld_prod_cod_entry);
	gtk_fixed_put(GTK_FIXED(est_sld_prod_cod_fixed),est_sld_prod_cod_frame,20,20);
	
	gtk_container_add(GTK_CONTAINER(est_sld_prod_nome_frame),est_sld_prod_nome_entry);
	gtk_fixed_put(GTK_FIXED(est_sld_prod_nome_fixed),est_sld_prod_nome_frame,20,20);
	
	gtk_box_pack_start(GTK_BOX(caixa_linha1),est_sld_prod_cod_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_linha1),est_sld_cod_fixed,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_linha1,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),est_sld_prod_nome_fixed,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),fixed_opcoes,0,0,10);
	gtk_container_add(GTK_CONTAINER(janela),caixa_grande);
	gtk_widget_show_all(janela);
	return 0;
}


