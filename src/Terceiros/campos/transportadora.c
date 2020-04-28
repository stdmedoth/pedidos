#include "entrega/transp_codigo.c"
#include "entrega/transp_nome.c"
#include "entrega/transp_logradouro.c"
#include "entrega/transp_num.c"
#include "entrega/transp_cidade.c"
#include "entrega/transp_estado.c"
#include "entrega/transp_cep.c"
#include "entrega/transp_telefone.c"
#include "entrega/transp_cnpj.c"
#include "entrega/transp_ie.c"
#include "entrega/transp_obs.c"

GtkWidget *entrega_campos()
{
	GtkWidget *caixa_grande;
	
	GtkWidget *transp_codigo, 
	*transp_nome, 
	*transp_logradouro, 
	*transp_num,
	*transp_cidade,
	*transp_estado,
	*transp_cep,
	*transp_telefone,
	*transp_cnpj, 
	*transp_ie, 
	*transp_obs;
	
	GtkWidget *dados_transp_fixed, *transp_endr_fixed, *transp_cep_fixed, *transp_obs_fixed; 
	GtkWidget *transp_obs_scroll;
	GtkWidget *linha1, // nome
	*linha2,   //CNPJ | Inscrição Estadual
	*linha3,  //endereco e cep p/ entrega |  telefone
	*linha4;  //valor minimo para frete pago
	
	GtkWidget *dados_transp_box;
	GtkWidget *dados_transp_frame, *endr_entrega_frame,*obs_transp_frame;
	
	GtkWidget *logr_num_box;
	GtkWidget *cid_uf_box;
	
	GtkWidget *transp_codigo_label, 
	*transp_nome_label, 
	*transp_num_label, 
	*transp_logradouro_label, 
	*transp_cidade_label, 
	*transp_estado_label, 
	*transp_cep_label, 
	*transp_telefone_label, 
	*transp_cnpj_label, 
	*transp_ie_label, 
	*transp_obs_label;
	
	linha1 = gtk_box_new(0,0);
	linha2 = gtk_box_new(0,0);
	linha3 = gtk_box_new(1,0);
	linha4 = gtk_box_new(0,0);
	caixa_grande = gtk_box_new(1,0);
	
	dados_transp_box = gtk_box_new(1,0);
	
	dados_transp_frame = gtk_frame_new("Dados Transportadora");
	endr_entrega_frame = gtk_frame_new("Endereço de Entrega");
	obs_transp_frame =  gtk_frame_new(NULL);//Observações para transporte");
	
	gtk_widget_set_size_request(dados_transp_frame,550,150);
	gtk_widget_set_size_request(endr_entrega_frame,550,150);
	
	logr_num_box = gtk_box_new(0,0);
	cid_uf_box = gtk_box_new(0,0);
	
	dados_transp_fixed = gtk_fixed_new();
	transp_endr_fixed = gtk_fixed_new();
	transp_cep_fixed = gtk_fixed_new();
	transp_obs_fixed = gtk_fixed_new();
	
	transp_obs_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_size_request(transp_obs_scroll,550,90);
	
	transp_codigo_label = gtk_label_new("Codigo");
	transp_codigo_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(transp_codigo_entry),10);
	gtk_entry_set_placeholder_text(GTK_ENTRY(transp_codigo_entry),"Código Transportadora");
	transp_codigo = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(transp_codigo),transp_codigo_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(transp_codigo),transp_codigo_entry,0,0,5);
	
	transp_nome_label = gtk_label_new("Nome da Transportadora");
	transp_nome_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(transp_nome_entry),50);
	gtk_entry_set_placeholder_text(GTK_ENTRY(transp_nome_entry),"Nome Transportadora");
	transp_nome = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(transp_nome),transp_nome_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(transp_nome),transp_nome_entry,0,0,5);
	
	transp_cnpj_label = gtk_label_new("Cnpj");
	transp_cnpj_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(transp_cnpj_entry),"CNPJ Transportadora");
	transp_cnpj = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(transp_cnpj),transp_cnpj_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(transp_cnpj),transp_cnpj_entry,0,0,5);
	
	transp_logradouro_label = gtk_label_new("Logradouro");
	transp_logradouro_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(transp_logradouro_entry),"Logradouro Transportadora");
	gtk_entry_set_width_chars(GTK_ENTRY(transp_logradouro_entry),50);
	transp_logradouro = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(transp_logradouro),transp_logradouro_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(transp_logradouro),transp_logradouro_entry,0,0,5);
	
	transp_num_label = gtk_label_new("Número");
	transp_num_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(transp_num_entry),"Numero Transportadora");
	gtk_entry_set_width_chars(GTK_ENTRY(transp_num_entry),5);
	transp_num = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(transp_num),transp_num_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(transp_num),transp_num_entry,0,0,5);
	
	transp_cep_label = gtk_label_new("CEP");
	transp_cep_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(transp_cep_entry),"CEP Transportadora");
	gtk_entry_set_width_chars(GTK_ENTRY(transp_cep_entry),20);
	transp_cep = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(transp_cep),transp_cep_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(transp_cep),transp_cep_entry,0,0,5);
	gtk_fixed_put(GTK_FIXED(transp_cep_fixed),transp_cep,5,0);
	
	transp_cidade_label = gtk_label_new("Cidade");
	transp_cidade_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(transp_cidade_entry),"Cidade Transportadora");
	gtk_entry_set_width_chars(GTK_ENTRY(transp_cidade_entry),20);
	transp_cidade = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(transp_cidade),transp_cidade_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(transp_cidade),transp_cidade_entry,0,0,5);
	
	transp_estado_label = gtk_label_new("UF: ");
	transp_estado_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(transp_estado_entry),"UF Transportadora");
	gtk_entry_set_width_chars(GTK_ENTRY(transp_estado_entry),5);
	transp_estado = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(transp_estado),transp_estado_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(transp_estado),transp_estado_entry,0,0,5);
	
	transp_telefone_label = gtk_label_new("Telefone");
	transp_telefone_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(transp_telefone_entry),"Tel/Cel Transportadora");
	transp_telefone = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(transp_telefone),transp_telefone_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(transp_telefone),transp_telefone_entry,0,0,5);
	
	transp_ie_label = gtk_label_new("IE:");
	transp_ie_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(transp_ie_entry),"IE da Transportadora");
	transp_ie = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(transp_ie),transp_ie_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(transp_ie),transp_ie_entry,0,0,5);
	
	transp_obs_label = gtk_label_new("Observações Transporte");
	transp_obs_entry =  gtk_text_view_new();
	transp_obs = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(transp_obs),transp_obs_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(transp_obs),transp_obs_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(obs_transp_frame),transp_obs);
	gtk_widget_set_size_request(transp_obs,550,90);
	gtk_widget_set_size_request(obs_transp_frame,550,90);
	gtk_widget_set_size_request(transp_obs_entry,550,50);
	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(transp_obs_scroll),obs_transp_frame);
	#endif
	gtk_fixed_put(GTK_FIXED(transp_obs_fixed),transp_obs_scroll,180,0);
	
	gtk_box_pack_start(GTK_BOX(logr_num_box),transp_logradouro,0,0,5);
	gtk_box_pack_start(GTK_BOX(logr_num_box),transp_num,0,0,5);

	gtk_box_pack_start(GTK_BOX(cid_uf_box),transp_cidade,0,0,5);
	gtk_box_pack_start(GTK_BOX(cid_uf_box),transp_estado,0,0,5);

	gtk_box_pack_start(GTK_BOX(linha1),transp_codigo,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha1),transp_nome,0,0,5);
	
	gtk_box_pack_start(GTK_BOX(linha2),transp_cnpj,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha2),transp_ie,0,0,5);
	
	gtk_box_pack_start(GTK_BOX(dados_transp_box),linha1,0,0,0);
	gtk_box_pack_start(GTK_BOX(dados_transp_box),linha2,0,0,0);
	gtk_container_add(GTK_CONTAINER(dados_transp_frame),dados_transp_box);
	gtk_fixed_put(GTK_FIXED(dados_transp_fixed),dados_transp_frame,180,0);
	
	gtk_box_pack_start(GTK_BOX(linha3),transp_cep_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha3),logr_num_box,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha3),cid_uf_box,0,0,5);
	gtk_container_add(GTK_CONTAINER(endr_entrega_frame),linha3);
	gtk_fixed_put(GTK_FIXED(transp_endr_fixed),endr_entrega_frame,180,0);
	
	gtk_box_pack_start(GTK_BOX(caixa_grande),dados_transp_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_grande),transp_endr_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_grande),transp_obs_fixed,0,0,5);
	
	
	g_signal_connect(GTK_ENTRY(transp_codigo_entry),"activate",G_CALLBACK(transp_codigo_fun),NULL);
	g_signal_connect(GTK_ENTRY(transp_nome_entry),"activate",G_CALLBACK(transp_nomec),NULL);
	g_signal_connect(GTK_ENTRY(transp_cnpj_entry),"activate",G_CALLBACK(transp_cnpjc),NULL);
	g_signal_connect(GTK_ENTRY(transp_ie_entry),"activate",G_CALLBACK(transp_ie_fun),NULL);
	g_signal_connect(GTK_ENTRY(transp_cep_entry),"activate",G_CALLBACK(transp_cepc),NULL);
	g_signal_connect(GTK_ENTRY(transp_logradouro_entry),"activate",G_CALLBACK(transp_logr_fun),NULL);
	g_signal_connect(GTK_ENTRY(transp_num_entry),"activate",G_CALLBACK(transp_num_fun),NULL);
	g_signal_connect(GTK_ENTRY(transp_cidade_entry),"activate",G_CALLBACK(transp_cidadec),NULL);
	g_signal_connect(GTK_ENTRY(transp_estado_entry),"activate",G_CALLBACK(transp_estado_fun),NULL);
	
	
	return caixa_grande;
}

