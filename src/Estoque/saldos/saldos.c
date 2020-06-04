int cad_est_sld()
{
	GtkWidget *janela, *caixa_grande;
	GtkWidget *est_sld_prod_cod_frame, *est_sld_prod_cod_fixed;
	GtkWidget *est_sld_prod_nome_frame, *est_sld_prod_nome_fixed;
	
	GtkWidget *est_sld_grp_cod_frame, *est_sld_grp_cod_fixed, *est_sld_grp_cod_box, *est_sld_grp_cod_psq;
	GtkWidget *est_sld_grp_nome_frame, *est_sld_grp_nome_fixed, *est_sld_grp_nome_entry;
	
	GtkWidget *est_sld_cod_frame, *est_sld_cod_fixed, *est_sld_grp_box, *est_sld_grp_frame;
	GtkWidget *est_sld_prod_frame, *est_sld_prod_fixed;
	
	GtkWidget *est_prod_pes_button;
	GtkWidget *caixa_linha1, *caixa_linha2, *caixa_linha3;
	
	GtkWidget *caixa_opcoes, *frame_opcoes, *fixed_opcoes;
	GtkWidget *box;
	
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(janela),"Saldo Estoque");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	if(personalizacao.janela_keep_above==1)	
		gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
	gtk_window_set_icon_name(GTK_WINDOW(janela),"system-software-install");
	gtk_widget_set_size_request(GTK_WIDGET(janela),450,300);
	
	box = gtk_box_new(0,0);
	caixa_grande = gtk_box_new(1,0);
	caixa_opcoes = gtk_box_new(0,0);
	frame_opcoes = gtk_frame_new("Opções");
	fixed_opcoes = gtk_fixed_new();
	caixa_linha1 = gtk_box_new(0,0);
	caixa_linha2 = gtk_box_new(0,0);
	caixa_linha3 = gtk_box_new(0,0);
	
	est_prod_pes_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(est_prod_pes_button),gtk_image_new_from_file(IMG_PESQ));
	
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
	gtk_entry_set_placeholder_text(GTK_ENTRY(est_sld_prod_cod_entry),"0");	
	est_sld_prod_cod_fixed = gtk_fixed_new();
	est_sld_prod_cod_frame = gtk_frame_new("Código Produto");
	
	est_sld_grp_frame = gtk_frame_new("Grupo");
	
	est_sld_grp_cod_entry = gtk_entry_new();
	est_sld_grp_cod_box = gtk_box_new(0,0);
	est_sld_grp_cod_fixed = gtk_fixed_new();
	est_sld_grp_cod_psq = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(est_sld_grp_cod_psq),gtk_image_new_from_file(IMG_PESQ));

	gtk_box_pack_start(GTK_BOX(est_sld_grp_cod_box),est_sld_grp_cod_entry,0,0,5);
	gtk_entry_set_width_chars(GTK_ENTRY(est_sld_grp_cod_entry),5);
	gtk_box_pack_start(GTK_BOX(est_sld_grp_cod_box),est_sld_grp_cod_psq,0,0,5);

	gtk_fixed_put(GTK_FIXED(est_sld_grp_cod_fixed),est_sld_grp_cod_box,10,10);

	est_sld_grp_nome_entry = gtk_entry_new();
	est_sld_grp_nome_fixed = gtk_fixed_new();
	gtk_entry_set_width_chars(GTK_ENTRY(est_sld_grp_nome_entry),30);
	gtk_widget_set_sensitive(est_sld_grp_nome_entry,FALSE);
	
	gtk_fixed_put(GTK_FIXED(est_sld_grp_nome_fixed),est_sld_grp_nome_entry,10,10);
		
	est_sld_grp_box = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(est_sld_grp_box),est_sld_grp_cod_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(est_sld_grp_box),est_sld_grp_nome_fixed,0,0,5);
	gtk_container_add(GTK_CONTAINER(est_sld_grp_frame),est_sld_grp_box);
	gtk_container_set_border_width(GTK_CONTAINER(est_sld_grp_frame),5);
	
	est_sld_cod_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(est_sld_cod_entry),5);
	gtk_entry_set_placeholder_text(GTK_ENTRY(est_sld_cod_entry),"0");	
	est_sld_cod_fixed = gtk_fixed_new();
	est_sld_cod_frame = gtk_frame_new("Estoque");	
	
	gtk_container_add(GTK_CONTAINER(est_sld_cod_frame),est_sld_cod_entry);
	gtk_fixed_put(GTK_FIXED(est_sld_cod_fixed),est_sld_cod_frame,20,20);
	
	est_sld_prod_nome_entry = gtk_entry_new();
	gtk_widget_set_sensitive(est_sld_prod_nome_entry,FALSE);
	gtk_entry_set_width_chars(GTK_ENTRY(est_sld_prod_nome_entry),30);
	gtk_entry_set_placeholder_text(GTK_ENTRY(est_sld_prod_nome_entry),"-");	
	est_sld_prod_nome_fixed = gtk_fixed_new();
	est_sld_prod_nome_frame = gtk_frame_new("Nome Produto");
	
	est_sld_prod_frame = gtk_frame_new("Saldo");
	est_sld_prod_fixed = gtk_fixed_new();
	est_sld_prod_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(est_sld_prod_entry),5);	
	gtk_entry_set_placeholder_text(GTK_ENTRY(est_sld_prod_entry),"0.0");	
	
	gtk_box_pack_start(GTK_BOX(box),est_sld_prod_cod_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(box),est_prod_pes_button,0,0,5);
	gtk_container_add(GTK_CONTAINER(est_sld_prod_cod_frame),box);
	gtk_fixed_put(GTK_FIXED(est_sld_prod_cod_fixed),est_sld_prod_cod_frame,20,20);
	
	gtk_container_add(GTK_CONTAINER(est_sld_prod_nome_frame),est_sld_prod_nome_entry);
	gtk_fixed_put(GTK_FIXED(est_sld_prod_nome_fixed),est_sld_prod_nome_frame,20,20);
	
	gtk_container_add(GTK_CONTAINER(est_sld_prod_frame),est_sld_prod_entry);
	gtk_fixed_put(GTK_FIXED(est_sld_prod_fixed),est_sld_prod_frame,20,20);
	
	gtk_box_pack_start(GTK_BOX(caixa_linha1),est_sld_prod_cod_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_linha1),est_sld_prod_nome_fixed,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(caixa_linha2),est_sld_grp_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_linha2),est_sld_cod_fixed,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(caixa_linha3),est_sld_prod_fixed,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_linha1,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_linha2,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_linha3,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),fixed_opcoes,0,0,10);
	
	g_signal_connect(est_prod_pes_button,"clicked",G_CALLBACK(psq_prod),est_sld_prod_cod_entry);
	g_signal_connect(est_sld_grp_cod_psq,"clicked",G_CALLBACK(pesquisa_subgrp),est_sld_grp_cod_entry);
	gtk_container_add(GTK_CONTAINER(janela),caixa_grande);
	gtk_widget_show_all(janela);
	return 0;
}


