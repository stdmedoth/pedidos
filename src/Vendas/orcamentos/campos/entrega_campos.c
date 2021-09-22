#include "entrega/srv_transp.c"
#include "entrega/transp_codigo.c"
#include "entrega/transp_nome.c"
#include "entrega/transp_cnpj.c"
#include "entrega/transp_estado.c"
#include "entrega/transp_cidade.c"
#include "entrega/transp_num.c"
#include "entrega/transp_ie.c"
#include "entrega/transp_logradouro.c"
#include "entrega/transp_bairro.c"
#include "entrega/transp_cep.c"
#include "entrega/valor_frete.c"
#include "entrega/flag_entrega.c"
#include "entrega/frete_pago.c"
#include "entrega/valor_desconto_frete.c"

#include "entrega/concluir.c"
#include "entrega/cancelar.c"
#include "entrega/alterar.c"

GtkWidget *orc_entrega_campos()
{
	GtkWidget *orc_servi_transp_codigo;

	GtkWidget *orc_transp_codigo_box,
	*orc_transp_nome_box,
	*orc_transp_logradouro_box,
	*orc_transp_bairro_box,
	*orc_transp_num_box,
	*orc_transp_cidade_box,
	*orc_transp_estado_box,
	*orc_transp_cep_box,
	*orc_transp_telefone_box,
	*orc_transp_cnpj_box,
	*orc_transp_ie_box,
	*orc_transp_obs_box,
	*orc_transp_valor_box,
	*orc_transp_desconto_box;

	GtkWidget *dados_orc_transp_fixed,
	*orc_transp_endr_fixed,
	*orc_transp_cep_fixed,
	*orc_transp_obs_fixed,
	*orc_transp_valor_fixed,
	*orc_transp_frete_pago_fixed,
	*orc_transp_desconto_fixed;

	GtkWidget *dados_orc_transp_box;
	GtkWidget *dados_orc_transp_frame,
	*endr_entrega_frame,
	*obs_orc_transp_frame,
	*valor_orc_transp_frame,
	*desconto_orc_transp_frame;

	GtkWidget *orc_srv_transp_frame,
	*orc_srv_transp_box,
	*psq_orc_srv_transp_box,
	*psq_orc_srv_transp_button;

	GtkWidget *orc_transp_obs_scroll;

	GtkWidget *logr_num_box;
	GtkWidget *bai_cid_uf_box;

	GtkWidget *orc_transp_codigo_frame,
	*orc_transp_nome_frame,
	*orc_transp_num_frame,
	*orc_transp_logradouro_frame,
	*orc_transp_bairro_frame,
	*orc_transp_cidade_frame,
	*orc_transp_estado_frame,
	*orc_transp_cep_frame,
	*orc_transp_telefone_frame,
	*orc_transp_cnpj_frame,
	*orc_transp_ie_frame,
	*orc_transp_obs_frame;

	dados_orc_transp_box = gtk_box_new(1,0);
	dados_orc_transp_frame = gtk_frame_new("Dados Transportadora");
	endr_entrega_frame = gtk_frame_new("Endereço de Entrega");
	obs_orc_transp_frame =  gtk_frame_new(NULL);//Observações para transporte");

	psq_ter_orc_transp_button = gtk_button_new();
	psq_ter_orc_transp_img = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(psq_ter_orc_transp_button),psq_ter_orc_transp_img);
	psq_ter_orc_transp_box = gtk_box_new(0,0);

	psq_ter_transpcep_button = gtk_button_new();
	psq_ter_transpcep_img = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(psq_ter_transpcep_button),psq_ter_transpcep_img);
	psq_ter_orc_transpcep_box = gtk_box_new(0,0);

	psq_orc_srv_transp_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(psq_orc_srv_transp_button),gtk_image_new_from_file(IMG_PESQ));
	psq_orc_srv_transp_box = gtk_box_new(0,0);

	dados_orc_transp_fixed = gtk_fixed_new();
	orc_transp_endr_fixed = gtk_fixed_new();
	orc_transp_cep_fixed = gtk_fixed_new();
	orc_transp_obs_fixed = gtk_fixed_new();
	orc_transp_valor_fixed = gtk_fixed_new();
	orc_transp_frete_pago_fixed = gtk_fixed_new();
	orc_transp_desconto_fixed = gtk_fixed_new();

	orc_transp_obs_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_size_request(orc_transp_obs_scroll,550,90);

	orc_srv_transp_frame = gtk_frame_new("Serviço de Transporte");
	orc_srv_transp_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(orc_srv_transp_entry),8);
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_srv_transp_entry),"Serviço de Transporte");
	orc_srv_transp_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(orc_srv_transp_box),orc_srv_transp_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(orc_srv_transp_box),psq_orc_srv_transp_button,0,0,0);
	gtk_container_add(GTK_CONTAINER(orc_srv_transp_frame), orc_srv_transp_box);

	orc_transp_codigo_frame = gtk_frame_new("Codigo");
	orc_transp_codigo_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_codigo_entry),8);
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_codigo_entry),"Código Transportadora");
	orc_transp_codigo_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_codigo_box),orc_transp_codigo_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_codigo_box),psq_ter_orc_transp_button,0,0,0);
	gtk_container_add(GTK_CONTAINER(orc_transp_codigo_frame), orc_transp_codigo_box);

	orc_transp_nome_frame = gtk_frame_new("Nome da Transportadora");
	orc_transp_nome_entry = gtk_entry_new();
	orc_transp_nome_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_nome_box),orc_transp_nome_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(orc_transp_nome_frame), orc_transp_nome_box);
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_nome_entry),50);
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_nome_entry),"Nome Transportadora");

	orc_transp_cnpj_frame = gtk_frame_new("Cnpj");
	orc_transp_cnpj_entry = gtk_entry_new();
	orc_transp_cnpj_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_cnpj_box),orc_transp_cnpj_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(orc_transp_cnpj_frame), orc_transp_cnpj_box);
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_cnpj_entry),"CNPJ Transportadora");

	orc_transp_logradouro_frame = gtk_frame_new("Logradouro");
	orc_transp_logradouro_entry = gtk_entry_new();
	orc_transp_logradouro_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_logradouro_box),orc_transp_logradouro_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(orc_transp_logradouro_frame), orc_transp_logradouro_box);
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_logradouro_entry),"Logradouro Entrega");
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_logradouro_entry),50);

	orc_transp_num_frame = gtk_frame_new("Número");
	orc_transp_num_box = gtk_box_new(0,0);
	orc_transp_num_entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(orc_transp_num_box),orc_transp_num_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(orc_transp_num_frame), orc_transp_num_box);
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_num_entry),"Número Destino");
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_num_entry),5);

	orc_transp_cep_frame = gtk_frame_new("CEP");
	orc_transp_cep_entry = gtk_entry_new();
	orc_transp_cep_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_cep_box),orc_transp_cep_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_cep_box),psq_ter_transpcep_button,0,0,0);
	gtk_container_add(GTK_CONTAINER(orc_transp_cep_frame), orc_transp_cep_box);
	gtk_fixed_put(GTK_FIXED(orc_transp_cep_fixed),orc_transp_cep_frame,5,0);
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_cep_entry),"CEP Destino");
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_cep_entry),20);

	orc_transp_cidade_frame = gtk_frame_new("Cidade");
	orc_transp_cidade_entry = gtk_entry_new();
	orc_transp_cidade_box = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_cidade_box),orc_transp_cidade_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(orc_transp_cidade_frame), orc_transp_cidade_box);
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_cidade_entry),"Cidade Destino");
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_cidade_entry),20);

	orc_transp_bairro_frame = gtk_frame_new("Bairro");
	orc_transp_bairro_entry = gtk_entry_new();
	orc_transp_bairro_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_bairro_box),orc_transp_bairro_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(orc_transp_bairro_frame), orc_transp_bairro_box);
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_bairro_entry),"Bairro Destino");
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_bairro_entry),20);

	orc_transp_estado_frame = gtk_frame_new("UF: ");
	orc_transp_estado_entry = gtk_entry_new();
	orc_transp_estado_box = gtk_box_new(0,0);
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_estado_entry),"UF Destino");
	gtk_entry_set_width_chars(GTK_ENTRY(orc_transp_estado_entry),5);
	gtk_box_pack_start(GTK_BOX(orc_transp_estado_box),orc_transp_estado_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(orc_transp_estado_frame), orc_transp_estado_box);

	orc_transp_telefone_frame = gtk_frame_new("Telefone");
	orc_transp_telefone_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_telefone_entry),"Tel/Cel Transportadora");
	orc_transp_telefone_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_telefone_box),orc_transp_telefone_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(orc_transp_telefone_frame), orc_transp_telefone_box);

	orc_transp_ie_frame = gtk_frame_new("IE:");
	orc_transp_ie_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_transp_ie_entry),"IE da Transportadora");
	orc_transp_ie_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_ie_box),orc_transp_ie_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(orc_transp_ie_frame), orc_transp_ie_box);

	orc_transp_obs_frame = gtk_frame_new("Observações Transporte");
	orc_transp_obs_entry =  gtk_text_view_new();
	orc_transp_obs_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_obs_box),orc_transp_obs_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(orc_transp_obs_frame), orc_transp_obs_box);

	orc_transp_frete_pago_button = gtk_check_button_new_with_label("Frete pago?");
	orc_transp_frete_pago_label = gtk_label_new("Do cliente : (-)");
	gtk_fixed_put(GTK_FIXED(orc_transp_frete_pago_fixed),orc_transp_frete_pago_button,20,20);
	gtk_fixed_put(GTK_FIXED(orc_transp_frete_pago_fixed),orc_transp_frete_pago_label,130,23);

	valor_orc_transp_frame = gtk_frame_new("Valor Frete");
	orc_transp_valor_frete_entry = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(orc_transp_valor_frete_entry),GTK_ENTRY_ICON_PRIMARY,"money");
	orc_transp_valor_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_valor_box),orc_transp_valor_frete_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(valor_orc_transp_frame),orc_transp_valor_box);
	gtk_fixed_put(GTK_FIXED(orc_transp_valor_fixed),valor_orc_transp_frame,20,20);

	desconto_orc_transp_frame = gtk_frame_new("desconto Frete");
	orc_transp_desconto_frete_entry = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(orc_transp_desconto_frete_entry),GTK_ENTRY_ICON_PRIMARY,"money");
	orc_transp_desconto_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(orc_transp_desconto_box),orc_transp_desconto_frete_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(desconto_orc_transp_frame),orc_transp_desconto_box);
	gtk_fixed_put(GTK_FIXED(orc_transp_desconto_fixed),desconto_orc_transp_frame,20,20);

	gtk_widget_set_size_request(orc_transp_obs_box,550,150);
	gtk_widget_set_size_request(orc_transp_obs_scroll,550,150);
	gtk_widget_set_size_request(orc_transp_obs_entry,550,150);

	gtk_container_add(GTK_CONTAINER(orc_transp_obs_scroll),obs_orc_transp_frame);
	gtk_fixed_put(GTK_FIXED(orc_transp_obs_fixed),orc_transp_obs_scroll,20,10);

	GtkWidget *linha1 = gtk_box_new(0,0);
	GtkWidget *linha2 = gtk_box_new(0,0);
	GtkWidget *linha3 = gtk_box_new(0,0);
	GtkWidget *linha4 = gtk_box_new(1,0);
	GtkWidget *linha5 = gtk_box_new(1,0);
	GtkWidget *linha6 = gtk_box_new(0,0);

	GtkWidget *colunas = gtk_box_new(0,0);
	GtkWidget *linhas1 = gtk_box_new(1,0);
	GtkWidget *linhas2 = gtk_box_new(1,0);
	GtkWidget *caixa_grande = gtk_box_new(1,0);


	gtk_widget_set_size_request(dados_orc_transp_frame,550,150);
	gtk_widget_set_size_request(endr_entrega_frame,550,150);

	logr_num_box = gtk_box_new(0,0);
	bai_cid_uf_box = gtk_box_new(0,0);

	gtk_box_pack_start(GTK_BOX(logr_num_box),orc_transp_logradouro_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(logr_num_box),orc_transp_num_frame,0,0,5);

	gtk_box_pack_start(GTK_BOX(bai_cid_uf_box),orc_transp_bairro_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(bai_cid_uf_box),orc_transp_cidade_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(bai_cid_uf_box),orc_transp_estado_frame,0,0,5);

	gtk_box_pack_start(GTK_BOX(linha1),orc_srv_transp_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha2),orc_transp_codigo_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha2),orc_transp_nome_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha3),orc_transp_cnpj_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha3),orc_transp_ie_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha3),orc_transp_telefone_frame,0,0,5);

	// dados do frame Dados Transporte
	gtk_box_pack_start(GTK_BOX(dados_orc_transp_box),linha1,0,0,0);
	gtk_box_pack_start(GTK_BOX(dados_orc_transp_box),linha2,0,0,0);
	gtk_box_pack_start(GTK_BOX(dados_orc_transp_box),linha3,0,0,0);
	gtk_container_add(GTK_CONTAINER(dados_orc_transp_frame),dados_orc_transp_box);
	gtk_fixed_put(GTK_FIXED(dados_orc_transp_fixed),dados_orc_transp_frame,50,0);

	// dados do frame de Endereço
	gtk_box_pack_start(GTK_BOX(linha4),orc_transp_cep_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha4),logr_num_box,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha4),bai_cid_uf_box,0,0,5);
	gtk_container_add(GTK_CONTAINER(endr_entrega_frame),linha4);
	gtk_fixed_put(GTK_FIXED(orc_transp_endr_fixed),endr_entrega_frame,50,0);

	gtk_box_pack_start(GTK_BOX(linhas1),dados_orc_transp_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linhas1),orc_transp_endr_fixed,0,0,0);

	gtk_box_pack_start(GTK_BOX(linhas2),orc_transp_obs_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linhas2),orc_transp_frete_pago_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linhas2),orc_transp_valor_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linhas2),orc_transp_desconto_fixed,0,0,0);

	gtk_box_pack_start(GTK_BOX(colunas),linhas1,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),linhas2,0,0,0);

	gtk_box_pack_start(GTK_BOX(caixa_grande),colunas,0,0,5);

	g_signal_connect(GTK_BUTTON(psq_orc_srv_transp_button),"clicked",G_CALLBACK(psq_srv_trsp),orc_srv_transp_entry);
	g_signal_connect(GTK_BUTTON(psq_ter_orc_transp_button),"clicked",G_CALLBACK(psq_ter),orc_transp_codigo_entry);
	//g_signal_connect(GTK_BUTTON(psq_orc_transpcep_button),"clicked",G_CALLBACK(psq_cep),orc_transp_cep_entry);

	g_signal_connect(GTK_ENTRY(orc_srv_transp_entry),"activate",G_CALLBACK(orc_srv_transp_fun),NULL);
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
	g_signal_connect(orc_transp_frete_pago_button,"toggled",G_CALLBACK(orc_transp_frete_pago_fun),NULL);
	g_signal_connect(GTK_ENTRY(orc_transp_valor_frete_entry),"activate",G_CALLBACK(orc_transp_valor_frete),NULL);
	g_signal_connect(GTK_ENTRY(orc_transp_desconto_frete_entry),"activate",G_CALLBACK(orc_transp_desconto_frete),NULL);
	return caixa_grande;
}
