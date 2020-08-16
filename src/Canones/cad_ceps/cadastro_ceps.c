int cad_cep(){
  GtkWidget *janela;
  janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_title(GTK_WINDOW(janela),"Cadastro CEPs");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"mark-location");
  if(personalizacao.janela_keep_above==1)
    gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
  gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

  GtkWidget *linha1,*linha2,*linha3,*linha4,*colunas;
  GtkWidget *caixa_opcoes, *frame_opcoes;
  GtkWidget *cad_ceps_code_frame, *cad_ceps_code_fixed, *cad_ceps_code_box;
  GtkWidget *cad_ceps_cep_frame, *cad_ceps_cep_fixed, *cad_ceps_cep_box;
  GtkWidget *cad_ceps_descr_frame, *cad_ceps_descr_fixed, *cad_ceps_descr_box;
  GtkWidget *cad_ceps_tipo_frame, *cad_ceps_tipo_fixed, *cad_ceps_tipo_box;
  GtkWidget *cad_ceps_uf_frame, *cad_ceps_uf_fixed, *cad_ceps_uf_box;
  GtkWidget *cad_ceps_bairro_frame, *cad_ceps_bairro_fixed, *cad_ceps_bairro_box;
  GtkWidget *cad_ceps_cid_code_frame, *cad_ceps_cid_code_fixed, *cad_ceps_cid_code_box;

  GtkWidget *psq_cep_button, *psq_cid_button;

  MYSQL_RES *res;
  MYSQL_ROW row;
  int cont=0;
  char query[MAX_QUERY_LEN],*code_task;

  cad_ceps_alterando=0;
  cad_ceps_concluindo=0;
  cad_ceps_uf_qnt=0;
  code_task = malloc(MAX_CODE_LEN);
  caixa_opcoes = gtk_box_new(0,0);
  frame_opcoes = gtk_frame_new("Opções");
  psq_cep_button = gtk_button_new();
  psq_cid_button = gtk_button_new();

  cad_cep_confirma_button = gtk_button_new_with_label("Confirmar");
  cad_cep_cancela_button = gtk_button_new_with_label("Cancelar");
  cad_cep_altera_button = gtk_button_new_with_label("Alterar");
  cad_cep_exclui_button = gtk_button_new_with_label("Excluir");

  gtk_button_set_image(GTK_BUTTON(psq_cep_button),gtk_image_new_from_file(IMG_PESQ));
  gtk_button_set_image(GTK_BUTTON(psq_cid_button),gtk_image_new_from_file(IMG_PESQ));
  gtk_button_set_image(GTK_BUTTON(cad_cep_confirma_button),gtk_image_new_from_file(IMG_OK));
  gtk_button_set_image(GTK_BUTTON(cad_cep_cancela_button),gtk_image_new_from_file(IMG_CANCEL));
  gtk_button_set_image(GTK_BUTTON(cad_cep_altera_button),gtk_image_new_from_file(IMG_ALTER));
  gtk_button_set_image(GTK_BUTTON(cad_cep_exclui_button),gtk_image_new_from_file(IMG_EXCLUI));

  gtk_box_pack_start(GTK_BOX(caixa_opcoes),cad_cep_confirma_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(caixa_opcoes),cad_cep_cancela_button,0,0,5);
  //gtk_box_pack_start(GTK_BOX(caixa_opcoes),cad_cep_altera_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(caixa_opcoes),cad_cep_exclui_button,0,0,5);

  gtk_container_add(GTK_CONTAINER(frame_opcoes),caixa_opcoes);

  cad_ceps_code_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_ceps_code_entry),8);
  cad_ceps_cep_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_ceps_cep_entry),15);
  cad_ceps_descr_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_ceps_descr_entry),30);
  cad_ceps_bairro_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_ceps_bairro_entry),20);
  cad_ceps_cid_code_entry = gtk_entry_new();
  cad_ceps_cid_descr_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_ceps_cid_code_entry),8);
  gtk_entry_set_width_chars(GTK_ENTRY(cad_ceps_cid_descr_entry),20);

  cad_ceps_uf_combo = gtk_combo_box_text_new();
  cont=0;
  sprintf(query,"select distinct uf from cidade");
  if(!(res=consultar(query))){
    popup(NULL,"Não foi possivel obter UFs");
  }
  else
  while((row=mysql_fetch_row(res))){
      gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(cad_ceps_uf_combo),cad_ceps_uf_qnt,row[0]);
      strcpy(uf_list[cad_ceps_uf_qnt],row[0]);
      cad_ceps_uf_qnt++;
      if(cad_ceps_uf_qnt>=MAX_UF_QNT)
        break;
  }
  if(!cad_ceps_uf_qnt){
    gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(cad_ceps_uf_combo),0,"Vazio");
    popup(NULL,"Não Há Estados cadastrados");
    return 1;
  }
  gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(cad_ceps_uf_combo),3);
  gtk_combo_box_set_active(GTK_COMBO_BOX(cad_ceps_uf_combo),0);

  cad_ceps_tipo_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_ceps_tipo_combo),"0",(tip_logds[0]));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_ceps_tipo_combo),"1",(tip_logds[1]));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_ceps_tipo_combo),"2",(tip_logds[2]));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_ceps_tipo_combo),"3",(tip_logds[3]));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_ceps_tipo_combo),"4",(tip_logds[4]));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_ceps_tipo_combo),"5",(tip_logds[5]));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_ceps_tipo_combo),"6",(tip_logds[6]));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_ceps_tipo_combo),"7",("Outros"));
  gtk_combo_box_set_active(GTK_COMBO_BOX(cad_ceps_tipo_combo),0);

  cad_ceps_code_fixed = gtk_fixed_new();
  cad_ceps_cep_fixed = gtk_fixed_new();
  cad_ceps_descr_fixed = gtk_fixed_new();
  cad_ceps_tipo_fixed = gtk_fixed_new();
  cad_ceps_uf_fixed = gtk_fixed_new();
  cad_ceps_bairro_fixed = gtk_fixed_new();
  cad_ceps_cid_code_fixed = gtk_fixed_new();

  cad_ceps_code_box = gtk_box_new(0,0);
  cad_ceps_cep_box = gtk_box_new(0,0);
  cad_ceps_descr_box = gtk_box_new(0,0);
  cad_ceps_tipo_box = gtk_box_new(0,0);
  cad_ceps_uf_box = gtk_box_new(0,0);
  cad_ceps_bairro_box = gtk_box_new(0,0);
  cad_ceps_cid_code_box = gtk_box_new(0,0);

  cad_ceps_code_frame = gtk_frame_new("Código");
  cad_ceps_cep_frame = gtk_frame_new("CEP:");
  cad_ceps_descr_frame = gtk_frame_new("Descrição");
  cad_ceps_tipo_frame = gtk_frame_new("Tipo");
  cad_ceps_uf_frame = gtk_frame_new("UF:");
  cad_ceps_bairro_frame = gtk_frame_new("Bairro:");
  cad_ceps_cid_code_frame = gtk_frame_new("Cidade:");

  gtk_box_pack_start(GTK_BOX(cad_ceps_code_box),cad_ceps_code_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_ceps_code_box),psq_cep_button,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_ceps_cep_box),cad_ceps_cep_entry,0,0,0);

  gtk_box_pack_start(GTK_BOX(cad_ceps_descr_box),cad_ceps_descr_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_ceps_tipo_box),cad_ceps_tipo_combo,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_ceps_uf_box),cad_ceps_uf_combo,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_ceps_bairro_box),cad_ceps_bairro_entry,0,0,0);

  gtk_box_pack_start(GTK_BOX(cad_ceps_cid_code_box),cad_ceps_cid_code_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_ceps_cid_code_box),psq_cid_button,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_ceps_cid_code_box),cad_ceps_cid_descr_entry,0,0,0);

  gtk_container_add(GTK_CONTAINER(cad_ceps_code_frame),cad_ceps_code_box);
  gtk_container_add(GTK_CONTAINER(cad_ceps_cep_frame),cad_ceps_cep_box);
  gtk_container_add(GTK_CONTAINER(cad_ceps_descr_frame),cad_ceps_descr_box);
  gtk_container_add(GTK_CONTAINER(cad_ceps_tipo_frame),cad_ceps_tipo_box);
  gtk_container_add(GTK_CONTAINER(cad_ceps_uf_frame),cad_ceps_uf_box);
  gtk_container_add(GTK_CONTAINER(cad_ceps_bairro_frame),cad_ceps_bairro_box);
  gtk_container_add(GTK_CONTAINER(cad_ceps_cid_code_frame),cad_ceps_cid_code_box);

  gtk_fixed_put(GTK_FIXED(cad_ceps_code_fixed),cad_ceps_code_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_ceps_cep_fixed),cad_ceps_cep_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_ceps_descr_fixed),cad_ceps_descr_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_ceps_tipo_fixed),cad_ceps_tipo_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_ceps_uf_fixed),cad_ceps_uf_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_ceps_bairro_fixed),cad_ceps_bairro_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_ceps_cid_code_fixed),cad_ceps_cid_code_frame,20,20);

  linha1 = gtk_box_new(0,0);
  linha2 = gtk_box_new(0,0);
  linha3 = gtk_box_new(0,0);
  linha4 = gtk_box_new(0,0);
  colunas = gtk_box_new(1,0);

  gtk_box_pack_start(GTK_BOX(linha1),cad_ceps_code_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha1),cad_ceps_cep_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha2),cad_ceps_descr_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha2),cad_ceps_tipo_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha3),cad_ceps_uf_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha3),cad_ceps_bairro_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha4),cad_ceps_cid_code_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(colunas),linha1,0,0,5);
  gtk_box_pack_start(GTK_BOX(colunas),linha2,0,0,5);
  gtk_box_pack_start(GTK_BOX(colunas),linha3,0,0,5);
  gtk_box_pack_start(GTK_BOX(colunas),linha4,0,0,5);
  gtk_box_pack_start(GTK_BOX(colunas),frame_opcoes,0,0,20);

  sprintf(query,"select MAX(id_logradouro)+1 from logradouro");
  if(!(res=consultar(query))){
    popup(NULL,"Não foi possivel receber task do logradouro");
    return 1;
  }
  if(!(row = mysql_fetch_row(res)))
    strcpy(code_task,"1");
  else
    strcpy(code_task,row[0]);

  gtk_entry_set_text(GTK_ENTRY(cad_ceps_code_entry),code_task);

  g_signal_connect(psq_cep_button,"clicked",G_CALLBACK(psq_cep),cad_ceps_cep_entry);
  g_signal_connect(psq_cid_button,"clicked",G_CALLBACK(psq_cidd),cad_ceps_cid_code_entry);

  g_signal_connect(cad_cep_confirma_button,"clicked",G_CALLBACK(cad_ceps_concluir_fun),NULL);
  g_signal_connect(cad_cep_altera_button,"clicked",G_CALLBACK(cad_ceps_alterar_fun),NULL);
  g_signal_connect(cad_cep_cancela_button,"clicked",G_CALLBACK(cad_ceps_cancelar_fun),NULL);
  g_signal_connect(cad_cep_exclui_button,"clicked",G_CALLBACK(cad_ceps_excluir_fun),NULL);

  g_signal_connect(cad_ceps_code_entry,"activate",G_CALLBACK(cad_ceps_code_fun),NULL);
  g_signal_connect(cad_ceps_cep_entry,"activate",G_CALLBACK(cad_ceps_cep_fun),NULL);
  g_signal_connect(cad_ceps_descr_entry,"activate",G_CALLBACK(cad_ceps_descr_fun),NULL);
  g_signal_connect(cad_ceps_bairro_entry,"activate",G_CALLBACK(cad_ceps_bairro_fun),NULL);
  g_signal_connect(cad_ceps_cid_code_entry,"activate",G_CALLBACK(cad_ceps_cid_code_fun),NULL);

  gtk_container_add(GTK_CONTAINER(janela),colunas);
  gtk_widget_show_all(janela);
  return 0;
}
