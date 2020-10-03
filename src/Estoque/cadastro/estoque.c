void inicializar_est()
{

}

int cad_est()
{
	GtkWidget *janela, *caixa_grande;
	GtkWidget *est_cod_frame, *est_cod_fixed;
	GtkWidget *est_nome_frame, *est_nome_fixed;
	GtkWidget *est_psq_code;
	GtkWidget *linha1, *linha2;


	GtkWidget *caixa_opcoes, *frame_opcoes, *fixed_opcoes;
	char code[MAX_CODE_LEN];

	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(janela),"Estoque");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	if(personalizacao.janela_keep_above==1)
		gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
	gtk_window_set_icon_name(GTK_WINDOW(janela),"x-package-repository");
	gtk_widget_set_size_request(GTK_WIDGET(janela),450,300);

	est_psq_code = gtk_box_new(0,0);
	linha2 = gtk_box_new(0,0);

	est_cad_alterando=0;

	caixa_grande = gtk_box_new(1,0);
	caixa_opcoes = gtk_box_new(0,0);
	frame_opcoes = gtk_frame_new("Opções");
	fixed_opcoes = gtk_fixed_new();

	est_concluir_button = gtk_button_new_with_label("Concluir");
	gtk_button_set_image(GTK_BUTTON(est_concluir_button),gtk_image_new_from_file(IMG_OK));
	est_alterar_button = gtk_button_new_with_label("Alterar");
	gtk_button_set_image(GTK_BUTTON(est_alterar_button),gtk_image_new_from_file(IMG_ALTER));
	est_cancelar_button = gtk_button_new_with_label("Cancelar");
	gtk_button_set_image(GTK_BUTTON(est_cancelar_button),gtk_image_new_from_file(IMG_CANCEL));
	est_excluir_button = gtk_button_new_with_label("Excluir");
	gtk_button_set_image(GTK_BUTTON(est_excluir_button),gtk_image_new_from_file(IMG_EXCLUI));

	gtk_box_pack_start(GTK_BOX(caixa_opcoes),est_concluir_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),est_alterar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),est_cancelar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),est_excluir_button,0,0,5);
	gtk_container_add(GTK_CONTAINER(frame_opcoes),caixa_opcoes);
	gtk_fixed_put(GTK_FIXED(fixed_opcoes),frame_opcoes,10,10);

	est_cod_entry = gtk_entry_new();
	est_cod_fixed = gtk_fixed_new();
	est_cod_frame = gtk_frame_new("Código");

	est_nome_entry = gtk_entry_new();
	est_nome_fixed = gtk_fixed_new();
	est_nome_frame = gtk_frame_new("Nome");

	est_psq_code_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(est_psq_code_button),gtk_image_new_from_file(IMG_PESQ));
	gtk_box_pack_start(GTK_BOX(est_psq_code),est_cod_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(est_psq_code),est_psq_code_button,0,0,0);

	gtk_container_add(GTK_CONTAINER(est_cod_frame),est_psq_code);
	gtk_fixed_put(GTK_FIXED(est_cod_fixed),est_cod_frame,10,20);
	gtk_entry_set_width_chars(GTK_ENTRY(est_cod_entry),10);

	gtk_container_add(GTK_CONTAINER(est_nome_frame),est_nome_entry);
	gtk_fixed_put(GTK_FIXED(est_nome_fixed),est_nome_frame,10,20);
	gtk_entry_set_width_chars(GTK_ENTRY(est_nome_entry),30);

	gtk_box_pack_start(GTK_BOX(linha2),est_nome_fixed,0,0,10);

	gtk_box_pack_start(GTK_BOX(caixa_grande),est_cod_fixed,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),linha2,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),fixed_opcoes,0,0,10);
	gtk_container_add(GTK_CONTAINER(janela),caixa_grande);

	g_signal_connect(est_cod_entry,"activate",G_CALLBACK(est_cad_code),NULL);
	g_signal_connect(est_nome_entry,"activate",G_CALLBACK(est_cad_nome),NULL);

	g_signal_connect(est_concluir_button,"clicked",G_CALLBACK(est_cad_concluir),NULL);
	g_signal_connect(est_concluir_button,"clicked",G_CALLBACK(est_cad_concluir),NULL);
	g_signal_connect(est_alterar_button,"clicked",G_CALLBACK(est_cad_alterar),NULL);
	g_signal_connect(est_cancelar_button,"clicked",G_CALLBACK(est_cad_cancelar),NULL);
	g_signal_connect(est_excluir_button,"clicked",G_CALLBACK(est_cad_excluir),NULL);
	g_signal_connect(est_psq_code_button,"clicked",G_CALLBACK(psq_est),est_cod_entry);

	g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_CAD_EST]);

	sprintf(code,"%i",tasker("estoques"));
	gtk_entry_set_text(GTK_ENTRY(est_cod_entry),code);

	gtk_widget_grab_focus(est_nome_entry);

	gtk_widget_show_all(janela);
	janelas_gerenciadas.vetor_janelas[REG_CAD_EST].reg_id = REG_CAD_EST;
	janelas_gerenciadas.vetor_janelas[REG_CAD_EST].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_CAD_EST]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_CAD_EST].janela_pointer = janela;

	return 0;
}
