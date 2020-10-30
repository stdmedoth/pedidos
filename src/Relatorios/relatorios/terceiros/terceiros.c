#include "campos/codigo.c"
#include "campos/query.c"
#include "campos/terceiro.c"
#include "campos/cep.c"
#include "campos/query_man.c"
#include "gerar.c"

void relat_ter_fun()
{
	GtkWidget *janela;
	GtkWidget *box, *fixed, *caixa;

	GtkWidget *relat_ter_code_frame, *relat_ter_code_fixed;
	GtkWidget *relat_ter_nome_frame, *relat_ter_nome_fixed;
	GtkWidget *relat_ter_query_frame, *relat_ter_query_fixed;
	GtkWidget *relat_ter_opcoes_fixed, *relat_ter_opcoes_box;

	GtkWidget *	relat_ter_cod_int_box, *relat_ter_tipo_box, *relat_ter_pes_box, *relat_ter_cep_int_box;

	GtkWidget *relat_ter_code_box;
	GtkWidget *relat_ter_tipos_box, *relat_ter_tipos_fixed;

	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_window_set_position(GTK_WINDOW(janela),3);

	relat_psq_cod_ter_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(relat_psq_cod_ter_button),gtk_image_new_from_file(IMG_PESQ));

	relat_psq_cep_ter_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(relat_psq_cep_ter_button),gtk_image_new_from_file(IMG_PESQ));

	relat_ter_code_box = gtk_box_new(0,0);
	psq_relat_ter_code = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(psq_relat_ter_code),gtk_image_new_from_file(IMG_PESQ));

	relat_ter_opcoes_box = gtk_box_new(1,0);
	relat_ter_opcoes_fixed = gtk_fixed_new();
	relat_ter_gerar_button = gtk_button_new_with_label("Gerar");
	gtk_button_set_image(GTK_BUTTON(relat_ter_gerar_button),gtk_image_new_from_icon_name("document-print",GTK_ICON_SIZE_DND));
	gtk_box_pack_start(GTK_BOX(relat_ter_opcoes_box),relat_ter_gerar_button,0,0,0);
	gtk_fixed_put(GTK_FIXED(relat_ter_opcoes_fixed),relat_ter_opcoes_box,100,20);

	relat_ter_code_entry = gtk_entry_new();
	relat_ter_code_frame = gtk_frame_new("Código");
	gtk_entry_set_placeholder_text(GTK_ENTRY(relat_ter_code_entry),"Buscar ->");
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(relat_ter_code_entry),GTK_ENTRY_ICON_PRIMARY,"emblem-system");
	relat_ter_code_fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(relat_ter_code_box),relat_ter_code_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(relat_ter_code_box),psq_relat_ter_code,0,0,0);
	gtk_container_add(GTK_CONTAINER(relat_ter_code_frame),relat_ter_code_box);
	gtk_fixed_put(GTK_FIXED(relat_ter_code_fixed),relat_ter_code_frame,20,20);
	gtk_entry_set_width_chars(GTK_ENTRY(relat_ter_code_entry),12);

	relat_ter_nome_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(relat_ter_nome_entry),"Nome do Relatorio");
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(relat_ter_nome_entry),GTK_ENTRY_ICON_PRIMARY,"format-text-underline");
	relat_ter_nome_frame = gtk_frame_new("Nome");
	relat_ter_nome_fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(relat_ter_nome_frame),relat_ter_nome_entry);
	gtk_fixed_put(GTK_FIXED(relat_ter_nome_fixed),relat_ter_nome_frame,20,20);

	relat_ter_query_entry = gtk_entry_new();
	relat_ter_query_frame = gtk_frame_new("Query Debug:");
	gtk_entry_set_placeholder_text(GTK_ENTRY(relat_ter_query_entry),"Query para análise");
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(relat_ter_query_entry),GTK_ENTRY_ICON_PRIMARY,"utilities-system-monitor");
	relat_ter_query_fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(relat_ter_query_frame),relat_ter_query_entry);
	gtk_fixed_put(GTK_FIXED(relat_ter_query_fixed),relat_ter_query_frame,20,20);
	gtk_entry_set_width_chars(GTK_ENTRY(relat_ter_query_entry),55);

	relat_ter_cod_int1_entry = gtk_spin_button_new_with_range(0,100000,1);
	gtk_entry_set_width_chars(GTK_ENTRY(relat_ter_cod_int1_entry),8);
	relat_ter_cod_int2_entry = gtk_spin_button_new_with_range(0,100000,1);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_ter_cod_int2_entry),100000);
	gtk_entry_set_width_chars(GTK_ENTRY(relat_ter_cod_int2_entry),8);
	relat_ter_cod_int_box = gtk_box_new(0,0);
	relat_ter_cod_int_frame = gtk_frame_new("Intervalo Terceiros");
	relat_ter_cod_int_fixed = gtk_fixed_new();

	relat_ter_tipos_box = gtk_box_new(0,0);
	relat_ter_tipos_fixed = gtk_fixed_new();

	relat_ter_tipo_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_ter_tipo_combo),"Todos");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_ter_tipo_combo),"Cliente");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_ter_tipo_combo),"Fornecedor");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_ter_tipo_combo),"Cliente e Fornecedor");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_ter_tipo_combo),"Transportadora");
	gtk_combo_box_set_active(GTK_COMBO_BOX(relat_ter_tipo_combo),0);
	relat_ter_tipo_box = gtk_box_new(0,0);
	relat_ter_tipo_frame = gtk_frame_new("Tipo Terceiro");

	relat_ter_pes_box = gtk_box_new(0,0);
	relat_ter_pes_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_ter_pes_combo),"Todos");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_ter_pes_combo),"Jurídica");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_ter_pes_combo),"Fisica");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_ter_pes_combo),"Sem CPF/CNPJ");
	gtk_combo_box_set_active(GTK_COMBO_BOX(relat_ter_pes_combo),0);
	relat_ter_pes_frame = gtk_frame_new("Tipo Pessoa");

	relat_ter_cep_int1_entry = gtk_spin_button_new_with_range(0,99999999,1);
	gtk_entry_set_width_chars(GTK_ENTRY(relat_ter_cep_int1_entry),8);
	relat_ter_cep_int2_entry = gtk_spin_button_new_with_range(0,99999999,1);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_ter_cep_int2_entry),99999999);
	gtk_entry_set_width_chars(GTK_ENTRY(relat_ter_cep_int2_entry),8);
	relat_ter_cep_int_box = gtk_box_new(0,0);
	relat_ter_cep_int_frame = gtk_frame_new("Intervalo CEP");
	relat_ter_cep_int_fixed = gtk_fixed_new();

	relat_ter_ordem_frame = gtk_frame_new("Ordem");
	relat_ter_crescente_combo = gtk_combo_box_text_new();
	relat_ter_ordem_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_ter_ordem_combo),"Selecionar Ordem");

	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_ter_crescente_combo),"Crescente");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_ter_crescente_combo),"Decrescente");

	gtk_combo_box_set_active(GTK_COMBO_BOX(relat_ter_crescente_combo),0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(relat_ter_ordem_combo),0);
	relat_ter_ordem_fixed = gtk_fixed_new();
	relat_ter_ordem_box = gtk_box_new(0,0);

	gtk_box_pack_start(GTK_BOX(relat_ter_cod_int_box),relat_ter_cod_int1_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(relat_ter_cod_int_box),relat_ter_cod_int2_entry,0,0,5);
	gtk_box_pack_start(GTK_BOX(relat_ter_cod_int_box),relat_psq_cod_ter_button,0,0,5);
	gtk_container_add(GTK_CONTAINER(relat_ter_cod_int_frame), relat_ter_cod_int_box);

	gtk_box_pack_start(GTK_BOX(relat_ter_pes_box),relat_ter_pes_combo,0,0,0);
	gtk_container_add(GTK_CONTAINER(relat_ter_pes_frame), relat_ter_pes_box);

	gtk_box_pack_start(GTK_BOX(relat_ter_tipo_box),relat_ter_tipo_combo,0,0,0);
	gtk_container_add(GTK_CONTAINER(relat_ter_tipo_frame), relat_ter_tipo_box);

	gtk_box_pack_start(GTK_BOX(relat_ter_tipos_box),relat_ter_pes_frame,0,0,0);
	gtk_box_pack_start(GTK_BOX(relat_ter_tipos_box),relat_ter_tipo_frame,0,0,5);


	gtk_box_pack_start(GTK_BOX(relat_ter_cep_int_box),relat_ter_cep_int1_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(relat_ter_cep_int_box),relat_ter_cep_int2_entry,0,0,5);
	gtk_box_pack_start(GTK_BOX(relat_ter_cep_int_box),relat_psq_cep_ter_button,0,0,5);
	gtk_container_add(GTK_CONTAINER(relat_ter_cep_int_frame), relat_ter_cep_int_box);

	gtk_box_pack_start(GTK_BOX(relat_ter_ordem_box),relat_ter_ordem_combo,0,0,0);
	gtk_box_pack_start(GTK_BOX(relat_ter_ordem_box),relat_ter_crescente_combo,0,0,5);
	gtk_container_add(GTK_CONTAINER(relat_ter_ordem_frame), relat_ter_ordem_box);

	fixed = gtk_fixed_new();
	box = gtk_box_new(1,0);
	//gtk_fixed_put(GTK_FIXED(relat_ter_code_fixed),relat_ter_code_frame,0,0);
	gtk_box_pack_start(GTK_BOX(box),relat_ter_code_fixed,0,0,1);

	//gtk_fixed_put(GTK_FIXED(relat_ter_nome_fixed),relat_ter_nome_frame,0,0);
	gtk_box_pack_start(GTK_BOX(box),relat_ter_nome_fixed,0,0,1);

	gtk_fixed_put(GTK_FIXED(relat_ter_cod_int_fixed),relat_ter_cod_int_frame,20,0);
	gtk_box_pack_start(GTK_BOX(box),relat_ter_cod_int_fixed,0,0,1);

	gtk_fixed_put(GTK_FIXED(relat_ter_cep_int_fixed),relat_ter_cep_int_frame,20,0);
	gtk_box_pack_start(GTK_BOX(box),relat_ter_cep_int_fixed,0,0,1);

	gtk_fixed_put(GTK_FIXED(relat_ter_tipos_fixed),relat_ter_tipos_box,20,0);
	gtk_box_pack_start(GTK_BOX(box),relat_ter_tipos_fixed,0,0,1);

	gtk_fixed_put(GTK_FIXED(relat_ter_ordem_fixed),relat_ter_ordem_frame,20,0);
	gtk_box_pack_start(GTK_BOX(box),relat_ter_ordem_fixed,0,0,1);

	gtk_fixed_put(GTK_FIXED(fixed),box,0,0);

	caixa = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(caixa),fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa),relat_ter_opcoes_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa),relat_ter_query_fixed,0,0,0);

	tabelas_bd_id=2;

	g_signal_connect(psq_relat_ter_code,"clicked",G_CALLBACK(psq_tables_relat),relat_ter_code_entry);
	g_signal_connect(relat_ter_gerar_button,"clicked",G_CALLBACK(relat_ter_query_fun),NULL);
	g_signal_connect(relat_ter_code_entry,"activate",G_CALLBACK(relat_ter_codigo_fun),NULL);

	g_signal_connect(relat_ter_query_entry,"activate",G_CALLBACK(relat_ter_query_manual),NULL);

	g_signal_connect(relat_ter_cod_int1_entry,"activate",G_CALLBACK(relat_ter_ter_i1_fun),NULL);
	g_signal_connect(relat_ter_cep_int1_entry,"activate",G_CALLBACK(relat_ter_cep_i1_fun),NULL);

	g_signal_connect(relat_psq_cod_ter_button,"clicked",G_CALLBACK(psq_ter),relat_ter_cod_int1_entry);
	g_signal_connect(relat_psq_cep_ter_button,"clicked",G_CALLBACK(psq_cep),relat_ter_cep_int1_entry);

	gtk_widget_set_sensitive(relat_ter_nome_entry,FALSE);
	gtk_widget_set_sensitive(relat_ter_code_entry,FALSE);

	gtk_widget_grab_focus(psq_relat_ter_code);

	gtk_container_add(GTK_CONTAINER(janela),caixa);
	gtk_widget_set_size_request(janela,500,300);
	gtk_widget_show_all(janela);
}
