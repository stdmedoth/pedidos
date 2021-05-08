struct _banco *get_banco(int bnc_code){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  struct _banco *banco = malloc(sizeof(struct _banco));
  sprintf(query, "select * from bancos where code = %i", bnc_code);
  if(!(res = consultar(query))){
    return NULL;
  }
  if(!(row = mysql_fetch_row(res))){
    return NULL;
  }

  banco->code = atoi(row[BNC_CODE_COL]);
  banco->nome = strdup(row[BNC_NOME_COL]);
  banco->conta = strdup(row[BNC_CONTA_COL]);
  banco->tipo_conta = atoi(row[BNC_TTIPO_COL]);
  banco->agencia = strdup(row[BNC_AGNC_COL]);
  banco->nome_usuario = strdup(row[BNC_USER_COL]);
  banco->documento = strdup(row[BNC_DOC_COL]);
  banco->saldo = atof(row[BNC_SLD_COL]);

  return banco;
}

int cad_bancos_fun(){
  GtkWidget *cad_bancos_code_frame,
  *cad_bancos_nome_frame,
  *cad_bancos_conta_frame,
  *cad_bancos_agencia_frame,
  *cad_bancos_tipoconta_frame,
  *cad_bancos_saldoini_frame,
  *cad_bancos_usuario_frame,
  *cad_bancos_doc_frame;

  GtkWidget *cad_bancos_code_box,
  *cad_bancos_nome_box,
  *cad_bancos_conta_box,
  *cad_bancos_agencia_box,
  *cad_bancos_tipoconta_box,
  *cad_bancos_saldoini_box,
  *cad_bancos_usuario_box,
  *cad_bancos_doc_box;

  GtkWidget *cad_bancos_code_fixed,
  *cad_bancos_nome_fixed,
  *cad_bancos_conta_fixed,
  *cad_bancos_agencia_fixed,
  *cad_bancos_tipoconta_fixed,
  *cad_bancos_saldoini_fixed,
  *cad_bancos_usuario_fixed,
  *cad_bancos_doc_fixed;

  GtkWidget *campo_opcoes, *caixa_grande, *linha1,
  *linha2,
  *linha3,
  *linha4,
  *linha5,
  *linha6,
  *coluna1;

  char task[MAX_CODE_LEN];
  sprintf(task,"%i",tasker("bancos"));

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_title(GTK_WINDOW(janela),"Cadastro de Bancos");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"document-edit");
  gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
  gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

  janelas_gerenciadas.vetor_janelas[CAD_BANCOS_WND].reg_id = CAD_BANCOS_WND;
  janelas_gerenciadas.vetor_janelas[CAD_BANCOS_WND].aberta = 1;
  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[CAD_BANCOS_WND]))
    return 1;
  janelas_gerenciadas.vetor_janelas[CAD_BANCOS_WND].janela_pointer = janela;

  cad_bancos_code_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bancos_code_entry),5);
  cad_bancos_nome_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bancos_nome_entry),25);
  cad_bancos_conta_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bancos_conta_entry),15);
  cad_bancos_tipoconta_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(cad_bancos_tipoconta_combo),"Conta Corrente");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(cad_bancos_tipoconta_combo),"Conta Poupança");
  gtk_combo_box_set_active(GTK_COMBO_BOX(cad_bancos_tipoconta_combo),0);
  cad_bancos_agencia_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bancos_agencia_entry),10);
  cad_bancos_usuario_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bancos_usuario_entry),25);
  cad_bancos_doc_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bancos_doc_entry),15);
  cad_bancos_saldoini_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bancos_code_entry),8);

  cad_bnc_code_psq_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(cad_bnc_code_psq_button),gtk_image_new_from_file(IMG_PESQ));

  cad_bancos_code_frame = gtk_frame_new("Código");
  cad_bancos_nome_frame = gtk_frame_new("Nome Banco");
  cad_bancos_conta_frame = gtk_frame_new("Número/DV Conta");
  cad_bancos_tipoconta_frame = gtk_frame_new("Tipo");
  cad_bancos_agencia_frame = gtk_frame_new("Agência");
  cad_bancos_usuario_frame = gtk_frame_new("Usuário");
  cad_bancos_doc_frame = gtk_frame_new("CNPJ/CPF: ");
  cad_bancos_saldoini_frame = gtk_frame_new("Saldo");

  cad_bancos_code_fixed = gtk_fixed_new();
  cad_bancos_nome_fixed = gtk_fixed_new();
  cad_bancos_conta_fixed = gtk_fixed_new();
  cad_bancos_tipoconta_fixed = gtk_fixed_new();
  cad_bancos_usuario_fixed = gtk_fixed_new();
  cad_bancos_agencia_fixed = gtk_fixed_new();
  cad_bancos_doc_fixed = gtk_fixed_new();
  cad_bancos_saldoini_fixed = gtk_fixed_new();

  cad_bancos_code_box = gtk_box_new(0,0);
  cad_bancos_nome_box = gtk_box_new(0,0);
  cad_bancos_conta_box = gtk_box_new(0,0);
  cad_bancos_tipoconta_box = gtk_box_new(0,0);
  cad_bancos_usuario_box = gtk_box_new(0,0);
  cad_bancos_agencia_box = gtk_box_new(0,0);
  cad_bancos_doc_box = gtk_box_new(0,0);
  cad_bancos_saldoini_box = gtk_box_new(0,0);

  gtk_box_pack_start(GTK_BOX(cad_bancos_code_box),cad_bancos_code_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_bancos_code_box),cad_bnc_code_psq_button,0,0,0);
  gtk_container_add(GTK_CONTAINER(cad_bancos_code_frame),cad_bancos_code_box);
  gtk_fixed_put(GTK_FIXED(cad_bancos_code_fixed),cad_bancos_code_frame,5,5);

  gtk_box_pack_start(GTK_BOX(cad_bancos_nome_box),cad_bancos_nome_entry,0,0,0);
  gtk_container_add(GTK_CONTAINER(cad_bancos_nome_frame),cad_bancos_nome_box);
  gtk_fixed_put(GTK_FIXED(cad_bancos_nome_fixed),cad_bancos_nome_frame,5,5);

  gtk_box_pack_start(GTK_BOX(cad_bancos_conta_box),cad_bancos_conta_entry,0,0,0);
  gtk_container_add(GTK_CONTAINER(cad_bancos_conta_frame),cad_bancos_conta_box);
  gtk_fixed_put(GTK_FIXED(cad_bancos_conta_fixed),cad_bancos_conta_frame,5,5);

  gtk_box_pack_start(GTK_BOX(cad_bancos_agencia_box),cad_bancos_agencia_entry,0,0,0);
  gtk_container_add(GTK_CONTAINER(cad_bancos_agencia_frame),cad_bancos_agencia_box);
  gtk_fixed_put(GTK_FIXED(cad_bancos_agencia_fixed),cad_bancos_agencia_frame,5,5);

  gtk_box_pack_start(GTK_BOX(cad_bancos_tipoconta_box),cad_bancos_tipoconta_combo,0,0,0);
  gtk_container_add(GTK_CONTAINER(cad_bancos_tipoconta_frame),cad_bancos_tipoconta_box);
  gtk_fixed_put(GTK_FIXED(cad_bancos_tipoconta_fixed),cad_bancos_tipoconta_frame,5,5);

  gtk_box_pack_start(GTK_BOX(cad_bancos_usuario_box),cad_bancos_usuario_entry,0,0,0);
  gtk_container_add(GTK_CONTAINER(cad_bancos_usuario_frame),cad_bancos_usuario_box);
  gtk_fixed_put(GTK_FIXED(cad_bancos_usuario_fixed),cad_bancos_usuario_frame,5,5);

  gtk_box_pack_start(GTK_BOX(cad_bancos_doc_box),cad_bancos_doc_entry,0,0,0);
  gtk_container_add(GTK_CONTAINER(cad_bancos_doc_frame),cad_bancos_doc_box);
  gtk_fixed_put(GTK_FIXED(cad_bancos_doc_fixed),cad_bancos_doc_frame,5,5);

  gtk_box_pack_start(GTK_BOX(cad_bancos_saldoini_box),cad_bancos_saldoini_entry,0,0,0);
  gtk_container_add(GTK_CONTAINER(cad_bancos_saldoini_frame),cad_bancos_saldoini_box);
  gtk_fixed_put(GTK_FIXED(cad_bancos_saldoini_fixed),cad_bancos_saldoini_frame,5,5);

  linha1 = gtk_box_new(0,0);
  linha2 = gtk_box_new(0,0);
  linha3 = gtk_box_new(0,0);
  linha4 = gtk_box_new(0,0);
  linha5 = gtk_box_new(0,0);
  linha6 = gtk_box_new(0,0);
  coluna1 = gtk_box_new(1,0);
  caixa_grande = gtk_box_new(1,0);
  campo_opcoes = gtk_box_new(0,0);

  cad_bancos_concluir_button = gtk_button_new_with_label("Concluir");
  gtk_button_set_image(GTK_BUTTON(cad_bancos_concluir_button),gtk_image_new_from_file(IMG_OK));
  cad_bancos_cancelar_button = gtk_button_new_with_label("Cancelar");
  gtk_button_set_image(GTK_BUTTON(cad_bancos_cancelar_button),gtk_image_new_from_file(IMG_CANCEL));
  cad_bancos_excluir_button = gtk_button_new_with_label("Excluir");
  gtk_button_set_image(GTK_BUTTON(cad_bancos_excluir_button),gtk_image_new_from_file(IMG_EXCLUI));
  cad_bancos_alterar_button = gtk_button_new_with_label("Alterar");
  gtk_button_set_image(GTK_BUTTON(cad_bancos_alterar_button),gtk_image_new_from_file(IMG_ALTER));

  gtk_box_pack_start(GTK_BOX(linha1),cad_bancos_code_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(linha1),cad_bancos_nome_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(linha2),cad_bancos_conta_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha2),cad_bancos_agencia_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(linha3),cad_bancos_tipoconta_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(linha4),cad_bancos_usuario_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha4),cad_bancos_doc_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(linha5),cad_bancos_saldoini_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(campo_opcoes),cad_bancos_concluir_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(campo_opcoes),cad_bancos_alterar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(campo_opcoes),cad_bancos_cancelar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(campo_opcoes),cad_bancos_excluir_button,0,0,5);

  gtk_box_pack_start(GTK_BOX(coluna1),linha1,0,0,5);
  gtk_box_pack_start(GTK_BOX(coluna1),linha2,0,0,5);
  gtk_box_pack_start(GTK_BOX(coluna1),linha3,0,0,5);
  gtk_box_pack_start(GTK_BOX(coluna1),linha4,0,0,5);
  gtk_box_pack_start(GTK_BOX(coluna1),linha5,0,0,5);
  gtk_box_pack_start(GTK_BOX(coluna1),linha6,0,0,5);

  gtk_box_pack_start(GTK_BOX(caixa_grande),coluna1,0,0,20);
  gtk_box_pack_start(GTK_BOX(caixa_grande),campo_opcoes,0,0,20);
  gtk_container_add(GTK_CONTAINER(janela),caixa_grande);
  gtk_entry_set_text(GTK_ENTRY(cad_bancos_code_entry),task);

  gtk_widget_show_all(janela);

  g_signal_connect(cad_bancos_code_entry,"activate",G_CALLBACK(cad_bancos_code_fun),NULL);
  g_signal_connect(cad_bancos_nome_entry,"activate",G_CALLBACK(cad_bancos_nome_fun),NULL);
  g_signal_connect(cad_bancos_conta_entry,"activate",G_CALLBACK(cad_bancos_conta_fun),NULL);
  g_signal_connect(cad_bancos_agencia_entry,"activate",G_CALLBACK(cad_bancos_agencia_fun),NULL);
  g_signal_connect(cad_bancos_usuario_entry,"activate",G_CALLBACK(cad_bancos_usuario_fun),NULL);
  g_signal_connect(cad_bancos_doc_entry,"activate",G_CALLBACK(cad_bancos_doc_fun),NULL);
  g_signal_connect(cad_bancos_saldoini_entry,"activate",G_CALLBACK(cad_bancos_saldoini_fun),NULL);

  g_signal_connect(cad_bnc_code_psq_button,"clicked",G_CALLBACK(psq_bnc),cad_bancos_code_entry);
  g_signal_connect(cad_bancos_concluir_button,"clicked",G_CALLBACK(cad_bancos_concluir_fun),NULL);
  g_signal_connect(cad_bancos_alterar_button,"clicked",G_CALLBACK(cad_bancos_alterar_fun),NULL);
  g_signal_connect(cad_bancos_cancelar_button,"clicked",G_CALLBACK(cad_bancos_cancelar_fun),NULL);
  g_signal_connect(cad_bancos_excluir_button,"clicked",G_CALLBACK(cad_bancos_excluir_fun),NULL);

  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[CAD_BANCOS_WND]);
  return 0;
}
