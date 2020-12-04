#include "campos/codigo.c"
#include "campos/nome.c"
#include "campos/tipo.c"
#include "campos/setor.c"
#include "campos/header.c"
#include "campos/body.c"
#include "campos/footer.c"

#include "alterar.c"
#include "cancelar.c"
#include "excluir.c"
#include "concluir.c"
#include "visualizar.c"
#include "modelosprontos.c"
#include "montar.c"

int mkt_email_models(){

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *grid = gtk_grid_new();
  GtkWidget *html_header_scroll = gtk_scrolled_window_new(NULL,NULL);
  GtkWidget *editor_header_scroll = gtk_scrolled_window_new(NULL,NULL);
  GtkWidget *html_corpo_scroll = gtk_scrolled_window_new(NULL,NULL);
  GtkWidget *editor_corpo_scroll = gtk_scrolled_window_new(NULL,NULL);
  GtkWidget *html_footer_scroll = gtk_scrolled_window_new(NULL,NULL);
  GtkWidget *editor_footer_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_name(janela,"Modelos de Emails");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Modelos de Emails");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"mail-replied");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

	janelas_gerenciadas.vetor_janelas[REG_MODMAIL_WND].reg_id = REG_MODMAIL_WND;
	janelas_gerenciadas.vetor_janelas[REG_MODMAIL_WND].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_MODMAIL_WND]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_MODMAIL_WND].janela_pointer = janela;

  GtkWidget *mkt_mail_code_frame, *mkt_mail_html_frame, *mkt_mail_editor_frame;
  GtkWidget *mkt_mail_code_box, *mkt_mail_html_box, *mkt_mail_editor_box;
  GtkWidget *mkt_mail_code_fixed, *mkt_mail_html_fixed, *mkt_mail_editor_fixed;
  GtkWidget *opcoes_box, *opcoes_fixed, *cancelar_button, *excluir_button, *alterar_button, *visualiza_button;
  GtkWidget *mkt_mail_nome_frame, *mkt_mail_nome_box, *mkt_mail_nome_fixed;
  GtkWidget *mkt_mail_tipo_frame, *mkt_mail_tipo_box;
  GtkWidget *mkt_mail_setor_frame, *mkt_mail_setor_box;
  GtkWidget *mkt_mail_opt_box = gtk_box_new(0,0);

  GtkWidget *mkt_mail_css_path_frame, *mkt_mail_css_path_box, *mkt_mail_css_path_fixed;
  GtkWidget *mkt_mail_title_frame, *mkt_mail_title_box, *mkt_mail_title_fixed;
  GtkWidget *mkt_mail_editorbody0_frame, *mkt_mail_editorbody0_box, *mkt_mail_editorbody0_fixed;
  GtkWidget *mkt_mail_editorbody1_frame, *mkt_mail_editorbody1_box, *mkt_mail_editorbody1_fixed, *mkt_mail_editorbody1_scroll;
  GtkWidget *mkt_mail_editorbody2_frame, *mkt_mail_editorbody2_box, *mkt_mail_editorbody2_fixed, *mkt_mail_editorbody2_scroll;
  GtkWidget *mkt_mail_editorbody3_frame, *mkt_mail_editorbody3_box, *mkt_mail_editorbody3_fixed, *mkt_mail_editorbody3_scroll;
  GtkWidget *mkt_mail_editorbody_boxh, *mkt_mail_editorbody_boxv;
  GtkWidget *mkt_mail_footer_frame, *mkt_mail_footer_box, *mkt_mail_footer_fixed;
  GtkWidget *mkt_mail_headerimg_path_frame, *mkt_mail_headerimg_path_box, *mkt_mail_headerimg_path_fixed;
  GtkWidget *mkt_mail_backimg_path_frame, *mkt_mail_backimg_path_box, *mkt_mail_backimg_path_fixed;

  GtkWidget *mkt_mail_editheader_frame,
  *mkt_mail_editheader_box,
  *mkt_mail_editheader1_box,
  *mkt_mail_editheader2_box,
  *mkt_mail_editheader3_box,
  *mkt_mail_editheader_fixed;

  GtkWidget *processa_button;
  GtkWidget *mkt_mail_editbody_frame, *mkt_mail_editbody_box, *mkt_mail_editbody_fixed;

  mkt_mail_modelos_button = gtk_button_new_with_label("Modelos Base");

  mkt_mail_css_path_frame = gtk_frame_new("Arquivo CSS");
  mkt_mail_css_path_box = gtk_box_new(0,0);
  mkt_mail_css_path_fixed = gtk_fixed_new();
  mkt_mail_css_path_choose = gtk_file_chooser_button_new("Escolher Caminho", GTK_FILE_CHOOSER_ACTION_OPEN);
  gtk_box_pack_start(GTK_BOX(mkt_mail_css_path_box), mkt_mail_css_path_choose,0,0,0);
  gtk_container_add(GTK_CONTAINER(mkt_mail_css_path_frame), mkt_mail_css_path_box);
  gtk_fixed_put(GTK_FIXED(mkt_mail_css_path_fixed), mkt_mail_css_path_frame,10,10);

  mkt_mail_title_frame = gtk_frame_new("Título (.titulo)");
  mkt_mail_title_box = gtk_box_new(0,0);
  mkt_mail_title_fixed = gtk_fixed_new();
  mkt_mail_title_entry = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(mkt_mail_title_box), mkt_mail_title_entry,0,0,0);
  gtk_container_add(GTK_CONTAINER(mkt_mail_title_frame), mkt_mail_title_box);
  gtk_fixed_put(GTK_FIXED(mkt_mail_title_fixed), mkt_mail_title_frame,10,10);

  mkt_mail_editorbody0_frame = gtk_frame_new("Corpo Header");
  mkt_mail_editorbody0_box = gtk_box_new(1,0);
  mkt_mail_editorbody0_fixed = gtk_fixed_new();

  mkt_mail_editorbody1_frame = gtk_frame_new("Corpo 1 (.corpo1)");
  mkt_mail_editorbody1_box = gtk_box_new(0,0);
  mkt_mail_editorbody1_fixed = gtk_fixed_new();
  mkt_mail_editorbody1_view = gtk_text_view_new();
  mkt_mail_editorbody1_scroll = gtk_scrolled_window_new(NULL,NULL);
  gtk_widget_set_size_request(mkt_mail_editorbody1_box,200,200);
  gtk_widget_set_size_request(mkt_mail_editorbody1_view,200,200);
  gtk_widget_set_size_request(mkt_mail_editorbody1_scroll,200,200);

  mkt_mail_editorbody2_frame = gtk_frame_new("Corpo 2 (.corpo2)");
  mkt_mail_editorbody2_box = gtk_box_new(0,0);
  mkt_mail_editorbody2_fixed = gtk_fixed_new();
  mkt_mail_editorbody2_view = gtk_text_view_new();
  mkt_mail_editorbody2_scroll = gtk_scrolled_window_new(NULL,NULL);
  gtk_widget_set_size_request(mkt_mail_editorbody2_box,200,200);
  gtk_widget_set_size_request(mkt_mail_editorbody2_view,200,200);
  gtk_widget_set_size_request(mkt_mail_editorbody2_scroll,200,200);

  mkt_mail_editorbody3_frame = gtk_frame_new("Corpo 3 (.corpo3)");
  mkt_mail_editorbody3_box = gtk_box_new(0,0);
  mkt_mail_editorbody3_fixed = gtk_fixed_new();
  mkt_mail_editorbody3_view = gtk_text_view_new();
  mkt_mail_editorbody3_scroll = gtk_scrolled_window_new(NULL,NULL);
  gtk_widget_set_size_request(mkt_mail_editorbody3_box,200,200);
  gtk_widget_set_size_request(mkt_mail_editorbody3_view,200,200);
  gtk_widget_set_size_request(mkt_mail_editorbody3_scroll,200,200);

  mkt_mail_editorbody_boxv = gtk_box_new(1,0);
  mkt_mail_editorbody_boxh = gtk_box_new(0,0);

  mkt_mail_footer_frame = gtk_frame_new("Footer (.footer)");
  mkt_mail_footer_box = gtk_box_new(0,0);
  mkt_mail_footer_fixed = gtk_fixed_new();

  mkt_mail_headerimg_path_frame = gtk_frame_new("Imagem Header");
  mkt_mail_headerimg_path_box = gtk_box_new(0,0);
  mkt_mail_headerimg_path_fixed = gtk_fixed_new();
  mkt_mail_headerimg_path_choose = gtk_file_chooser_button_new("Escolher Imagem", GTK_FILE_CHOOSER_ACTION_OPEN);
  gtk_box_pack_start(GTK_BOX(mkt_mail_headerimg_path_box), mkt_mail_headerimg_path_choose,0,0,0);
  gtk_container_add(GTK_CONTAINER(mkt_mail_headerimg_path_frame), mkt_mail_headerimg_path_box);
  gtk_fixed_put(GTK_FIXED(mkt_mail_headerimg_path_fixed), mkt_mail_headerimg_path_frame,10,10);

  mkt_mail_backimg_path_frame = gtk_frame_new("Imagem Fundo");
  mkt_mail_backimg_path_box = gtk_box_new(0,0);
  mkt_mail_backimg_path_fixed = gtk_fixed_new();
  mkt_mail_headerimg_path_choose = gtk_file_chooser_button_new("Escolher Imagem", GTK_FILE_CHOOSER_ACTION_OPEN);
  gtk_box_pack_start(GTK_BOX(mkt_mail_backimg_path_box), mkt_mail_headerimg_path_choose,0,0,0);
  gtk_container_add(GTK_CONTAINER(mkt_mail_backimg_path_frame), mkt_mail_backimg_path_box);
  gtk_fixed_put(GTK_FIXED(mkt_mail_backimg_path_fixed), mkt_mail_backimg_path_frame,10,10);

  mkt_mail_editheader_frame = gtk_frame_new("Componentes");
  mkt_mail_editheader_box = gtk_box_new(0,0);
  mkt_mail_editheader1_box = gtk_box_new(0,0);
  mkt_mail_editheader2_box = gtk_box_new(0,0);
  mkt_mail_editheader3_box = gtk_box_new(0,0);
  mkt_mail_editheader_fixed = gtk_fixed_new();

  gtk_box_pack_start(GTK_BOX(mkt_mail_editheader1_box), mkt_mail_css_path_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(mkt_mail_editheader2_box), mkt_mail_headerimg_path_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(mkt_mail_editheader_box), mkt_mail_editheader1_box,0,0,0);
  gtk_box_pack_start(GTK_BOX(mkt_mail_editheader_box), mkt_mail_editheader2_box,0,0,0);
  gtk_box_pack_start(GTK_BOX(mkt_mail_editheader_box), mkt_mail_editheader3_box,0,0,0);
  gtk_container_add(GTK_CONTAINER(editor_header_scroll), mkt_mail_editheader_box);

  mkt_mail_editbody_frame = gtk_frame_new("Componentes");
  mkt_mail_editbody_box = gtk_box_new(0,0);
  mkt_mail_editbody_fixed = gtk_fixed_new();

  gtk_container_add(GTK_CONTAINER(mkt_mail_editorbody1_scroll), mkt_mail_editorbody1_view);
  gtk_container_add(GTK_CONTAINER(mkt_mail_editorbody2_scroll), mkt_mail_editorbody2_view);
  gtk_container_add(GTK_CONTAINER(mkt_mail_editorbody3_scroll), mkt_mail_editorbody3_view);


  gtk_box_pack_start(GTK_BOX(mkt_mail_editorbody0_box), mkt_mail_title_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(mkt_mail_editorbody0_box), mkt_mail_backimg_path_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(mkt_mail_editorbody1_box), mkt_mail_editorbody1_scroll,0,0,0);
  gtk_box_pack_start(GTK_BOX(mkt_mail_editorbody2_box), mkt_mail_editorbody2_scroll,0,0,0);
  gtk_box_pack_start(GTK_BOX(mkt_mail_editorbody3_box), mkt_mail_editorbody3_scroll,0,0,0);

  gtk_container_add(GTK_CONTAINER(mkt_mail_editorbody0_frame), mkt_mail_editorbody0_box);
  gtk_container_add(GTK_CONTAINER(mkt_mail_editorbody1_frame), mkt_mail_editorbody1_box);
  gtk_container_add(GTK_CONTAINER(mkt_mail_editorbody2_frame), mkt_mail_editorbody2_box);
  gtk_container_add(GTK_CONTAINER(mkt_mail_editorbody3_frame), mkt_mail_editorbody3_box);

  gtk_fixed_put(GTK_FIXED(mkt_mail_editorbody0_fixed), mkt_mail_editorbody0_frame,0,0);
  gtk_fixed_put(GTK_FIXED(mkt_mail_editorbody1_fixed), mkt_mail_editorbody1_frame,0,0);
  gtk_fixed_put(GTK_FIXED(mkt_mail_editorbody2_fixed), mkt_mail_editorbody2_frame,0,0);
  gtk_fixed_put(GTK_FIXED(mkt_mail_editorbody3_fixed), mkt_mail_editorbody3_frame,0,0);


  gtk_box_pack_start(GTK_BOX(mkt_mail_editorbody_boxh), mkt_mail_editorbody0_fixed,0,0,5);
  gtk_box_pack_start(GTK_BOX(mkt_mail_editorbody_boxh), mkt_mail_editorbody1_fixed,0,0,5);
  gtk_box_pack_start(GTK_BOX(mkt_mail_editorbody_boxh), mkt_mail_editorbody2_fixed,0,0,5);
  gtk_box_pack_start(GTK_BOX(mkt_mail_editorbody_boxh), mkt_mail_editorbody3_fixed,0,0,5);

  gtk_box_pack_start(GTK_BOX(mkt_mail_editorbody_boxv), mkt_mail_editorbody_boxh,0,0,5);

  gtk_container_add(GTK_CONTAINER(editor_corpo_scroll), mkt_mail_editorbody_boxv);

  mkt_mail_html_notebook = gtk_notebook_new();
  mkt_mail_editor_notebook = gtk_notebook_new();
  mkt_mail_geral_notebook = gtk_notebook_new();

  mkt_mail_concluir_button = gtk_button_new_with_label("Concluir");
  alterar_button = gtk_button_new_with_label("Alterar");
  cancelar_button = gtk_button_new_with_label("Cancelar");
  excluir_button = gtk_button_new_with_label("Excluir");
  visualiza_button = gtk_button_new_with_label("Visualizar");
  processa_button = gtk_button_new_with_label("Processar");
  opcoes_box = gtk_box_new(0,0);
  opcoes_fixed = gtk_fixed_new();
  gtk_box_pack_start(GTK_BOX(opcoes_box),mkt_mail_concluir_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box),alterar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box),cancelar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box),excluir_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box),visualiza_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box),processa_button,0,0,20);
  gtk_fixed_put(GTK_FIXED(opcoes_fixed),opcoes_box,10,10);

  mkt_mail_code_box = gtk_box_new(0,0);
  mkt_mail_html_box = gtk_box_new(0,0);
  mkt_mail_editor_box = gtk_box_new(0,0);

  mkt_mail_code_fixed = gtk_fixed_new();
  mkt_mail_html_fixed = gtk_fixed_new();
  mkt_mail_editor_fixed = gtk_fixed_new();

  mkt_mail_psq_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(mkt_mail_psq_button),gtk_image_new_from_file(IMG_PESQ));
  mkt_mail_code_entry = gtk_entry_new();
  mkt_mail_corpo_view = gtk_text_view_new();
  gtk_container_add(GTK_CONTAINER(html_corpo_scroll),mkt_mail_corpo_view);

  mkt_mail_header_view = gtk_text_view_new();
  gtk_container_add(GTK_CONTAINER(html_header_scroll),mkt_mail_header_view);

  mkt_mail_footer_view = gtk_text_view_new();
  gtk_container_add(GTK_CONTAINER(html_footer_scroll),mkt_mail_footer_view);

  gtk_entry_set_width_chars(GTK_ENTRY(mkt_mail_code_entry), 8);
  mkt_mail_nome_entry = gtk_entry_new();
  mkt_mail_nome_fixed = gtk_fixed_new();
  mkt_mail_nome_box = gtk_box_new(0,0);
  mkt_mail_nome_frame = gtk_frame_new("Nome");
  gtk_entry_set_width_chars(GTK_ENTRY(mkt_mail_nome_entry), 35);
  gtk_box_pack_start(GTK_BOX(mkt_mail_nome_box), mkt_mail_nome_entry,0,0,5);
  gtk_container_add(GTK_CONTAINER(mkt_mail_nome_frame), mkt_mail_nome_box);
  gtk_fixed_put(GTK_FIXED(mkt_mail_nome_fixed), mkt_mail_nome_frame,5,5);

  mkt_mail_tipo_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_tipo_combo), EMAIL_NEWSLETTER, "Newsletter");
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_tipo_combo), EMAIL_PROMO, "Promocional");
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_tipo_combo), EMAIL_SAZONAL, "Sazonal");
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_tipo_combo), EMAIL_CLI_INAT, "Clientes Inativos");
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_tipo_combo), EMAIL_FUNC_ALERT, "Alerta");
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_tipo_combo), EMAIL_FUNC_CROSS_SELL, "Cross selling"); // venda complementar ao produto
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_tipo_combo), EMAIL_FUNC_UPSELL, "Up Selling"); //upgrade de um produto
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_tipo_combo), EMAIL_FUNC_BOAVINDAS, "Boas-Vindas");
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_tipo_combo), EMAIL_GENERICO, "Genérico");
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_tipo_combo), EMAIL_FUNC_FEEDBACK, "Feedback");
  gtk_combo_box_set_active(GTK_COMBO_BOX(mkt_mail_tipo_combo),0);
  mkt_mail_tipo_frame = gtk_frame_new("Tipo");
  mkt_mail_tipo_box = gtk_box_new(0,0);
  gtk_box_pack_start(GTK_BOX(mkt_mail_tipo_box), mkt_mail_tipo_combo,0,0,5);
  gtk_container_add(GTK_CONTAINER(mkt_mail_tipo_frame), mkt_mail_tipo_box);

  mkt_mail_setor_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_setor_combo), SETOR_INDUSTRIAL, "Industrial");
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_setor_combo), SETOR_COMERCIAL, "Comercial");
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_setor_combo), SETOR_PREST_SERV, "Prestação Serviços");
  gtk_combo_box_set_active(GTK_COMBO_BOX(mkt_mail_setor_combo),0);
  mkt_mail_setor_frame = gtk_frame_new("Setor");
  mkt_mail_setor_box = gtk_box_new(0,0);
  gtk_box_pack_start(GTK_BOX(mkt_mail_setor_box), mkt_mail_setor_combo,0,0,5);
  gtk_container_add(GTK_CONTAINER(mkt_mail_setor_frame), mkt_mail_setor_box);

  gtk_box_pack_start(GTK_BOX(mkt_mail_code_box),mkt_mail_code_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(mkt_mail_code_box),mkt_mail_psq_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(mkt_mail_code_box), mkt_mail_modelos_button,0,0,5);

  gtk_box_pack_start(GTK_BOX(mkt_mail_html_box),mkt_mail_html_notebook,0,0,0);
  gtk_widget_set_size_request(mkt_mail_html_box,700,300);
  gtk_widget_set_size_request(mkt_mail_corpo_view,700,300);
  gtk_widget_set_size_request(html_corpo_scroll,700,300);

  gtk_box_pack_start(GTK_BOX(mkt_mail_editor_box),mkt_mail_editor_notebook,0,0,0);
  gtk_widget_set_size_request(mkt_mail_editor_box,700,300);
  gtk_widget_set_size_request(editor_corpo_scroll,700,300);

  mkt_mail_code_frame = gtk_frame_new("ID Email:");
  mkt_mail_html_frame = gtk_frame_new("Divisões");
  mkt_mail_editor_frame = gtk_frame_new("Editor");

  gtk_container_add(GTK_CONTAINER(mkt_mail_code_frame), mkt_mail_code_box);
  gtk_container_add(GTK_CONTAINER(mkt_mail_html_frame), mkt_mail_html_box);
  gtk_container_add(GTK_CONTAINER(mkt_mail_editor_frame), mkt_mail_editor_box);

  gtk_fixed_put(GTK_FIXED(mkt_mail_code_fixed), mkt_mail_code_frame,5,5);
  gtk_fixed_put(GTK_FIXED(mkt_mail_html_fixed), mkt_mail_html_frame,5,5);
  gtk_fixed_put(GTK_FIXED(mkt_mail_editor_fixed), mkt_mail_editor_frame,5,5);

  gtk_box_pack_start(GTK_BOX(mkt_mail_opt_box),mkt_mail_tipo_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(mkt_mail_opt_box),mkt_mail_setor_frame,0,0,5);

  gtk_notebook_append_page(GTK_NOTEBOOK(mkt_mail_html_notebook), html_header_scroll, gtk_label_new("Header"));
  gtk_notebook_append_page(GTK_NOTEBOOK(mkt_mail_html_notebook), html_corpo_scroll, gtk_label_new("Corpo"));
  gtk_notebook_append_page(GTK_NOTEBOOK(mkt_mail_html_notebook), html_footer_scroll, gtk_label_new("Footer"));

  gtk_notebook_append_page(GTK_NOTEBOOK(mkt_mail_editor_notebook), editor_header_scroll, gtk_label_new("Header"));
  gtk_notebook_append_page(GTK_NOTEBOOK(mkt_mail_editor_notebook), editor_corpo_scroll, gtk_label_new("Corpo"));
  gtk_notebook_append_page(GTK_NOTEBOOK(mkt_mail_editor_notebook), editor_footer_scroll, gtk_label_new("Footer"));

  gtk_notebook_append_page(GTK_NOTEBOOK(mkt_mail_geral_notebook), mkt_mail_editor_fixed, gtk_label_new("Editor"));
  gtk_notebook_append_page(GTK_NOTEBOOK(mkt_mail_geral_notebook), mkt_mail_html_fixed, gtk_label_new("HTML"));

  gtk_grid_attach(GTK_GRID(grid), mkt_mail_code_fixed,0,0,1,1);
  gtk_grid_attach(GTK_GRID(grid), mkt_mail_nome_fixed,0,1,1,1);
  gtk_grid_attach(GTK_GRID(grid), mkt_mail_opt_box,0,2,1,1);
  gtk_grid_attach(GTK_GRID(grid), mkt_mail_geral_notebook,0,3,1,1);
  gtk_grid_attach(GTK_GRID(grid), opcoes_fixed,0,4,1,1);

  gtk_widget_set_size_request(janela,700,400);
  gtk_container_add(GTK_CONTAINER(janela),  grid);

  g_signal_connect(mkt_mail_code_entry, "activate", G_CALLBACK(mkt_mail_code_fun), NULL);
  g_signal_connect(mkt_mail_nome_entry, "activate", G_CALLBACK(mkt_mail_nome_fun), NULL);
  g_signal_connect(mkt_mail_tipo_combo, "changed", G_CALLBACK(mkt_mail_tipo_fun), NULL);
  g_signal_connect(mkt_mail_setor_combo, "changed", G_CALLBACK(mkt_mail_setor_fun), NULL);

  g_signal_connect(mkt_mail_modelos_button, "clicked", G_CALLBACK(mkt_mail_modelpronto_fun), NULL);

  g_signal_connect(mkt_mail_concluir_button, "clicked", G_CALLBACK(mkt_mail_concluir_fun), NULL);
  g_signal_connect(alterar_button, "clicked", G_CALLBACK(mkt_mail_alterar_fun), NULL);
  g_signal_connect(processa_button, "clicked", G_CALLBACK(mkt_mail_montar_fun), NULL);
  g_signal_connect(cancelar_button, "clicked", G_CALLBACK(mkt_mail_cancelar_fun), NULL);
  g_signal_connect(excluir_button, "clicked", G_CALLBACK(mkt_mail_excluir_fun), NULL);

  g_signal_connect(visualiza_button, "clicked", G_CALLBACK(mkt_mail_visualizar_fun), NULL);

  mkt_mail_cancelar_fun();

  gtk_widget_show_all(janela);

  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_MODMAIL_WND]);

  return 0;
}
