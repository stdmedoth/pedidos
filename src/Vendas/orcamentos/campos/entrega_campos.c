GtkWidget *orc_entrega_campos()
{
	GtkWidget *caixa_grande, *colunas, *linhas1,*linhas2;

	GtkWidget *orc_transp_codigo,
	*orc_transp_nome,
	*orc_transp_logradouro,
	*orc_transp_bairro,
	*orc_transp_num,
	*orc_transp_cidade,
	*orc_transp_estado,
	*orc_transp_cep,
	*orc_transp_telefone,
	*orc_transp_cnpj,
	*orc_transp_ie,
	*orc_transp_obs;

	GtkWidget *dados_orc_transp_fixed, *orc_transp_endr_fixed, *orc_transp_cep_fixed, *orc_transp_obs_fixed;
	GtkWidget *orc_transp_obs_scroll;
	GtkWidget *linha1, // nome
	*linha2,   //CNPJ | Inscrição Estadual
	*linha3,  //endereco e cep p/ entrega |  telefone
	*linha4;  //valor minimo para frete pago

	GtkWidget *dados_orc_transp_box;
	GtkWidget *dados_orc_transp_frame, *endr_entrega_frame,*obs_orc_transp_frame;

	GtkWidget *logr_num_box;
	GtkWidget *bai_cid_uf_box;

	GtkWidget *orc_transp_codigo_label,
	*orc_transp_nome_label,
	*orc_transp_num_label,
	*orc_transp_logradouro_label,
	*orc_transp_bairro_label,
	*orc_transp_cidade_label,
	*orc_transp_estado_label,
	*orc_transp_cep_label,
	*orc_transp_telefone_label,
	*orc_transp_cnpj_label,
	*orc_transp_ie_label,
	*orc_transp_obs_label;

	linha1 = gtk_box_new(0,0);
	linha2 = gtk_box_new(0,0);
	linha3 = gtk_box_new(1,0);
	linha4 = gtk_box_new(0,0);

	colunas = gtk_box_new(0,0);
	linhas1 = gtk_box_new(1,0);
	linhas2 = gtk_box_new(1,0);
	caixa_grande = gtk_box_new(1,0);

	dados_orc_transp_box = gtk_box_new(1,0);

	dados_orc_transp_frame = gtk_frame_new("Dados Transportadora");
	endr_entrega_frame = gtk_frame_new("Endereço de Entrega");
	obs_orc_transp_frame =  gtk_frame_new(NULL);//Observações para transporte");

	gtk_widget_set_size_request(dados_orc_transp_frame,550,150);
	gtk_widget_set_size_request(endr_entrega_frame,550,150);

	logr_num_box = gtk_box_new(0,0);
	bai_cid_uf_box = gtk_box_new(0,0);

	psq_ter_orc_transp_button = gtk_button_new();
	psq_ter_orc_transp_img = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(psq_ter_orc_transp_button),psq_ter_orc_transp_img);
	psq_ter_orc_transp_box = gtk_box_new(0,0);

	psq_ter_transpcep_button = gtk_button_new();
	psq_ter_transpcep_img = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(psq_ter_transpcep_button),psq_ter_transpcep_img);
	psq_ter_transpcep_box = gtk_box_new(0,0);

	dados_orc_transp_fixed = gtk_fixed_new();
	orc_transp_endr_fixed = gtk_fixed_new();
	orc_transp_cep_fixed = gtk_fixed_new();
	orc_transp_obs_fixed = gtk_fixed_new();

	orc_transp_obs_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_size_request(orc_transp_obs_scroll,550,90);

	orc_transp_codigo_label = gtk_label_new("Codigo");
	orc_transp_codigo_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_codigo_entry),10);
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_codigo_entry),"Código Transportadora");
	orc_transp_codigo = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_codigo),orc_transp_codigo_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(psq_ter_orc_transp_box),orc_transp_codigo_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_ter_orc_transp_box),psq_ter_orc_transp_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_codigo),psq_ter_orc_transp_box,0,0,5);


	orc_transp_nome_label = gtk_label_new("Nome da Transportadora");
	orc_transp_nome_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_nome_entry),50);
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_nome_entry),"Nome Transportadora");
	orc_transp_nome = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_nome),orc_transp_nome_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(orc_transp_nome),orc_transp_nome_entry,0,0,5);

	orc_transp_cnpj_label = gtk_label_new("Cnpj");
	orc_transp_cnpj_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_cnpj_entry),"CNPJ Transportadora");
	orc_transp_cnpj = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_cnpj),orc_transp_cnpj_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(orc_transp_cnpj),orc_transp_cnpj_entry,0,0,5);

	orc_transp_logradouro_label = gtk_label_new("Logradouro");
	orc_transp_logradouro_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_logradouro_entry),"Logradouro Transportadora");
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_logradouro_entry),50);
	orc_transp_logradouro = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_logradouro),orc_transp_logradouro_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(orc_transp_logradouro),orc_transp_logradouro_entry,0,0,5);

	orc_transp_num_label = gtk_label_new("Número");
	orc_transp_num_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_num_entry),"Numero Transportadora");
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_num_entry),5);
	orc_transp_num = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_num),orc_transp_num_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(orc_transp_num),orc_transp_num_entry,0,0,5);

	orc_transp_cep_label = gtk_label_new("CEP");
	orc_transp_cep_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_cep_entry),"CEP Transportadora");
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_cep_entry),20);
	orc_transp_cep = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_cep),orc_transp_cep_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(psq_ter_transpcep_box),orc_transp_cep_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_ter_transpcep_box),psq_ter_transpcep_button,0,0,0);
	gtk_fixed_put(GTK_FIXED(orc_transp_cep_fixed),psq_ter_transpcep_box,5,0);

	orc_transp_cidade_label = gtk_label_new("Cidade");
	orc_transp_cidade_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_cidade_entry),"Cidade Transportadora");
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_cidade_entry),20);
	orc_transp_cidade = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_cidade),orc_transp_cidade_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(orc_transp_cidade),orc_transp_cidade_entry,0,0,5);

	orc_transp_bairro_label = gtk_label_new("Bairro");
	orc_transp_bairro_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_bairro_entry),"Bairro Transportadora");
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_bairro_entry),20);
	orc_transp_bairro = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_bairro),orc_transp_bairro_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(orc_transp_bairro),orc_transp_bairro_entry,0,0,5);

	orc_transp_estado_label = gtk_label_new("UF: ");
	orc_transp_estado_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_estado_entry),"UF Transportadora");
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_estado_entry),5);
	orc_transp_estado = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_estado),orc_transp_estado_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(orc_transp_estado),orc_transp_estado_entry,0,0,5);

	orc_transp_telefone_label = gtk_label_new("Telefone");
	orc_transp_telefone_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_telefone_entry),"Tel/Cel Transportadora");
	orc_transp_telefone = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_telefone),orc_transp_telefone_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(orc_transp_telefone),orc_transp_telefone_entry,0,0,5);

	orc_transp_ie_label = gtk_label_new("IE:");
	orc_transp_ie_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_ie_entry),"IE da Transportadora");
	orc_transp_ie = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_ie),orc_transp_ie_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(orc_transp_ie),orc_transp_ie_entry,0,0,5);

	orc_transp_obs_label = gtk_label_new("Observações Transporte");
	orc_transp_obs_entry =  gtk_text_view_new();
	orc_transp_obs = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_obs),orc_transp_obs_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(orc_transp_obs),orc_transp_obs_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(obs_orc_transp_frame),orc_transp_obs);

	gtk_widget_set_size_request(orc_transp_obs,550,150);
	gtk_widget_set_size_request(orc_transp_obs_scroll,550,150);
	gtk_widget_set_size_request(orc_transp_obs_entry,550,150);

	gtk_container_add(GTK_CONTAINER(orc_transp_obs_scroll),obs_orc_transp_frame);

	gtk_fixed_put(GTK_FIXED(orc_transp_obs_fixed),orc_transp_obs_scroll,20,10);

	gtk_box_pack_start(GTK_BOX(logr_num_box),orc_transp_logradouro,0,0,5);
	gtk_box_pack_start(GTK_BOX(logr_num_box),orc_transp_num,0,0,5);

	gtk_box_pack_start(GTK_BOX(bai_cid_uf_box),orc_transp_bairro,0,0,5);
	gtk_box_pack_start(GTK_BOX(bai_cid_uf_box),orc_transp_cidade,0,0,5);
	gtk_box_pack_start(GTK_BOX(bai_cid_uf_box),orc_transp_estado,0,0,5);

	gtk_box_pack_start(GTK_BOX(linha1),orc_transp_codigo,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha1),orc_transp_nome,0,0,5);

	gtk_box_pack_start(GTK_BOX(linha2),orc_transp_cnpj,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha2),orc_transp_ie,0,0,5);

	gtk_box_pack_start(GTK_BOX(dados_orc_transp_box),linha1,0,0,0);
	gtk_box_pack_start(GTK_BOX(dados_orc_transp_box),linha2,0,0,0);
	gtk_container_add(GTK_CONTAINER(dados_orc_transp_frame),dados_orc_transp_box);
	gtk_fixed_put(GTK_FIXED(dados_orc_transp_fixed),dados_orc_transp_frame,100,0);

	gtk_box_pack_start(GTK_BOX(linha3),orc_transp_cep_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha3),logr_num_box,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha3),bai_cid_uf_box,0,0,5);
	gtk_container_add(GTK_CONTAINER(endr_entrega_frame),linha3);
	gtk_fixed_put(GTK_FIXED(orc_transp_endr_fixed),endr_entrega_frame,100,0);

	gtk_box_pack_start(GTK_BOX(linhas1),dados_orc_transp_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linhas1),orc_transp_endr_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linhas2),orc_transp_obs_fixed,0,0,0);

	gtk_box_pack_start(GTK_BOX(colunas),linhas1,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),linhas2,0,0,0);

	gtk_box_pack_start(GTK_BOX(caixa_grande),colunas,0,0,5);

	g_signal_connect(GTK_BUTTON(psq_ter_orc_transp_button),"clicked",G_CALLBACK(psq_ter),orc_transp_codigo_entry);
	g_signal_connect(GTK_BUTTON(psq_ter_transpcep_button),"clicked",G_CALLBACK(psq_cep),orc_transp_cep_entry);

	g_signal_connect(GTK_ENTRY(orc_transp_codigo_entry),"activate",G_CALLBACK(orc_transp_codigo_fun),NULL);
	g_signal_connect(GTK_ENTRY(orc_transp_nome_entry),"activate",G_CALLBACK(orc_transp_nomec),NULL);
	g_signal_connect(GTK_ENTRY(orc_transp_cnpj_entry),"activate",G_CALLBACK(orc_transp_cnpjc),NULL);
	g_signal_connect(GTK_ENTRY(orc_transp_ie_entry),"activate",G_CALLBACK(orc_transp_ie_fun),NULL);
	g_signal_connect(GTK_ENTRY(orc_transp_cep_entry),"activate",G_CALLBACK(orc_transp_cepc),NULL);
	g_signal_connect(GTK_ENTRY(orc_transp_logradouro_entry),"activate",G_CALLBACK(orc_transp_logr_fun),NULL);
	g_signal_connect(GTK_ENTRY(orc_transp_bairro_entry),"activate",G_CALLBACK(orc_transp_bairroc),NULL);
	g_signal_connect(GTK_ENTRY(orc_transp_num_entry),"activate",G_CALLBACK(orc_transp_num_fun),NULL);
	g_signal_connect(GTK_ENTRY(orc_transp_cidade_entry),"activate",G_CALLBACK(orc_transp_cidadec),NULL);
	g_signal_connect(GTK_ENTRY(orc_transp_estado_entry),"activate",G_CALLBACK(orc_transp_estado_fun),NULL);

	return caixa_grande;
}
