#include "campos/codigo.c"

int mkt_email_models(){

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *grid = gtk_grid_new();
  GtkWidget *scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_name(janela,"Modelos de Emails");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Modelos de Emails");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"system-software-install");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

	janelas_gerenciadas.vetor_janelas[REG_MODMAIL_PROD].reg_id = REG_CAD_PROD;
	janelas_gerenciadas.vetor_janelas[REG_MODMAIL_PROD].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_MODMAIL_PROD]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_MODMAIL_PROD].janela_pointer = janela;

  GtkWidget *mkt_mail_code_frame, *mkt_mail_text_frame;
  GtkWidget *mkt_mail_code_box, *mkt_mail_text_box;
  GtkWidget *mkt_mail_code_fixed, *mkt_mail_text_fixed;
  GtkWidget *opcoes_box, *opcoes_fixed, *concluir_button, *cancelar_button, *excluir_button, *alterar_button;
  GtkWidget *mkt_mail_nome_frame, *mkt_mail_nome_box, *mkt_mail_nome_fixed;
  GtkWidget *mkt_mail_tipo_frame, *mkt_mail_tipo_box;
  GtkWidget *mkt_mail_setor_frame, *mkt_mail_setor_box;
  GtkWidget *mkt_mail_opt_box = gtk_box_new(0,0);

  concluir_button = gtk_button_new_with_label("Concluir");
  alterar_button = gtk_button_new_with_label("Alterar");
  cancelar_button = gtk_button_new_with_label("Cancelar");
  excluir_button = gtk_button_new_with_label("Excluir");
  opcoes_box = gtk_box_new(0,0);
  opcoes_fixed = gtk_fixed_new();
  gtk_box_pack_start(GTK_BOX(opcoes_box),concluir_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box),alterar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box),cancelar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box),excluir_button,0,0,5);
  gtk_fixed_put(GTK_FIXED(opcoes_fixed),opcoes_box,10,10);

  mkt_mail_code_box = gtk_box_new(0,0);
  mkt_mail_text_box = gtk_box_new(0,0);

  mkt_mail_code_fixed = gtk_fixed_new();
  mkt_mail_text_fixed = gtk_fixed_new();

  mkt_mail_psq_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(mkt_mail_psq_button),gtk_image_new_from_file(IMG_PESQ));
  mkt_mail_code_entry = gtk_entry_new();
  mkt_mail_text_view = gtk_text_view_new();
  gtk_container_add(GTK_CONTAINER(scroll),mkt_mail_text_view);
  gtk_entry_set_width_chars(GTK_ENTRY(mkt_mail_code_entry), 10);
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
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_tipo_combo), EMAIL_FUNC_FEEDBACK, "Feedback"); //upgrade de um produto
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mkt_mail_tipo_combo), EMAIL_GENERICO, "Genérico");
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

  gtk_box_pack_start(GTK_BOX(mkt_mail_text_box),scroll,0,0,0);
  gtk_widget_set_size_request(mkt_mail_text_box,700,300);
  gtk_widget_set_size_request(mkt_mail_text_view,700,300);
  gtk_widget_set_size_request(scroll,700,300);

  mkt_mail_code_frame = gtk_frame_new("ID Email:");
  mkt_mail_text_frame = gtk_frame_new("Conteúdo");

  gtk_container_add(GTK_CONTAINER(mkt_mail_code_frame), mkt_mail_code_box);
  gtk_container_add(GTK_CONTAINER(mkt_mail_text_frame), mkt_mail_text_box);

  gtk_fixed_put(GTK_FIXED(mkt_mail_code_fixed), mkt_mail_code_frame,5,5);
  gtk_fixed_put(GTK_FIXED(mkt_mail_text_fixed), mkt_mail_text_frame,5,5);

  gtk_box_pack_start(GTK_BOX(mkt_mail_opt_box),mkt_mail_tipo_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(mkt_mail_opt_box),mkt_mail_setor_frame,0,0,5);

  gtk_grid_attach(GTK_GRID(grid), mkt_mail_code_fixed,0,0,1,1);
  gtk_grid_attach(GTK_GRID(grid), mkt_mail_nome_fixed,0,1,1,1);
  gtk_grid_attach(GTK_GRID(grid), mkt_mail_opt_box,0,2,1,1);
  gtk_grid_attach(GTK_GRID(grid), mkt_mail_text_fixed,0,3,1,1);
  gtk_grid_attach(GTK_GRID(grid), opcoes_fixed,0,4,1,1);

  gtk_widget_set_size_request(janela,700,400);
  gtk_container_add(GTK_CONTAINER(janela),  grid);

  g_signal_connect(mkt_mail_code_entry, "activate", G_CALLBACK(mkt_email_code_fun), NULL);

  gtk_widget_show_all(janela);
  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_MODMAIL_PROD]);

  return 0;
}
