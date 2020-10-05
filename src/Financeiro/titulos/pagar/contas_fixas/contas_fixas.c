#include "campos/titulo.c"
#include "campos/descricao.c"
#include "campos/fornecedor.c"
#include "campos/data_inicial.c"
#include "campos/data_final.c"
#include "campos/intervalo.c"
#include "campos/tipo.c"
#include "campos/valor.c"
#include "gerar.c"
#include "concluir.c"
#include "excluir.c"
#include "alterar.c"
#include "cancelar.c"

int cad_conta_fixa(){
  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_title(GTK_WINDOW(janela),"Contas Fixas");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"x-office-calendar");
  gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
  gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

  janelas_gerenciadas.vetor_janelas[CAD_CONT_FIX_WND].reg_id = CAD_CONT_FIX_WND;
  janelas_gerenciadas.vetor_janelas[CAD_CONT_FIX_WND].aberta = 1;
  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[CAD_CONT_FIX_WND]))
    return 1;
  janelas_gerenciadas.vetor_janelas[CAD_CONT_FIX_WND].janela_pointer = janela;

  GtkWidget *conta_fix_id_frame, *conta_fix_descr_frame, *conta_fix_forn_frame, *conta_fix_dtini_frame, *conta_fix_dtend_frame, *conta_fix_int_frame, *conta_fix_valor_frame;
  GtkWidget *conta_fix_id_box, *conta_fix_descr_box, *conta_fix_forn_box ,*conta_fix_dtini_box, *conta_fix_dtend_box, *conta_fix_int_box, *conta_fix_valor_box;
  GtkWidget *conta_fix_box, *opcoes_box, *conta_datas_int;
  gchar task[12];
  sprintf(task,"%i",tasker("titulos"));
  conta_fix_id_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(conta_fix_id_entry),5);
  conta_fix_descr_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(conta_fix_descr_entry),30);
  conta_fix_forn_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(conta_fix_forn_entry),5);
  conta_fix_nomeforn_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(conta_fix_nomeforn_entry),30);
  conta_fix_dtini_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(conta_fix_dtini_entry),10);
  conta_fix_dtend_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(conta_fix_dtend_entry),10);
  conta_fix_int_entry = gtk_spin_button_new_with_range(1,31,1);
  conta_fix_int_combo = gtk_combo_box_text_new();
  conta_fix_valor_entry = gtk_entry_new();

  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(conta_fix_int_combo),"Escolher Modelo");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(conta_fix_int_combo),"Intervalo/dias");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(conta_fix_int_combo),"Intervalo/Meses");
  gtk_combo_box_set_active(GTK_COMBO_BOX(conta_fix_int_combo),0);

  conta_fix_concluir_button = gtk_button_new_with_label("Confirmar");
  gtk_button_set_image(GTK_BUTTON(conta_fix_concluir_button),gtk_image_new_from_file(IMG_OK));
  conta_fix_alterar_button = gtk_button_new_with_label("Alterar");
  gtk_button_set_image(GTK_BUTTON(conta_fix_alterar_button),gtk_image_new_from_file(IMG_EXCLUI));
  conta_fix_deletar_button = gtk_button_new_with_label("Deletar");
  gtk_button_set_image(GTK_BUTTON(conta_fix_deletar_button),gtk_image_new_from_file(IMG_CANCEL));
  conta_fix_cancelar_button = gtk_button_new_with_label("Cancelar");
  gtk_button_set_image(GTK_BUTTON(conta_fix_cancelar_button),gtk_image_new_from_file(IMG_CANCEL));

  conta_fix_pesq_id = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(conta_fix_pesq_id),gtk_image_new_from_file(IMG_PESQ));
  conta_fix_pesq_forn = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(conta_fix_pesq_forn),gtk_image_new_from_file(IMG_PESQ));
  conta_fix_pesq_dtini = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(conta_fix_pesq_dtini),gtk_image_new_from_file(IMG_PESQ));
  conta_fix_pesq_dtend = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(conta_fix_pesq_dtend),gtk_image_new_from_file(IMG_PESQ));

  conta_fix_id_frame = gtk_frame_new("Id");
  conta_fix_descr_frame = gtk_frame_new("Descrição");
  conta_fix_forn_frame = gtk_frame_new("Fornecedor");
  conta_fix_dtini_frame = gtk_frame_new("Data Inicial");
  conta_fix_dtend_frame = gtk_frame_new("Data Final");
  conta_fix_int_frame = gtk_frame_new("Intervalo");
  conta_fix_valor_frame = gtk_frame_new("Valor");

  conta_fix_id_box = gtk_box_new(0,0);
  conta_fix_descr_box = gtk_box_new(0,0);
  conta_fix_forn_box = gtk_box_new(0,0);
  conta_fix_dtini_box = gtk_box_new(0,0);
  conta_fix_dtend_box = gtk_box_new(0,0);
  conta_fix_int_box = gtk_box_new(0,0);
  conta_fix_valor_box = gtk_box_new(0,0);

  conta_fix_box = gtk_box_new(1,0);
  conta_datas_int = gtk_box_new(0,0);
  opcoes_box = gtk_box_new(0,0);

  gtk_box_pack_start(GTK_BOX(conta_fix_id_box),conta_fix_id_entry,0,0,5);
  gtk_box_pack_start(GTK_BOX(conta_fix_id_box),conta_fix_pesq_id,0,0,5);

  gtk_box_pack_start(GTK_BOX(conta_fix_descr_box),conta_fix_descr_entry,0,0,5);

  gtk_box_pack_start(GTK_BOX(conta_fix_forn_box),conta_fix_forn_entry,0,0,5);
  gtk_box_pack_start(GTK_BOX(conta_fix_forn_box),conta_fix_pesq_forn,0,0,5);
  gtk_box_pack_start(GTK_BOX(conta_fix_forn_box),conta_fix_nomeforn_entry,0,0,5);

  gtk_box_pack_start(GTK_BOX(conta_fix_dtini_box),conta_fix_dtini_entry,0,0,5);
  gtk_box_pack_start(GTK_BOX(conta_fix_dtini_box),conta_fix_pesq_dtini,0,0,5);

  gtk_box_pack_start(GTK_BOX(conta_fix_dtend_box),conta_fix_dtend_entry,0,0,5);
  gtk_box_pack_start(GTK_BOX(conta_fix_dtend_box),conta_fix_pesq_dtend,0,0,5);

  gtk_box_pack_start(GTK_BOX(conta_fix_int_box),conta_fix_int_entry,0,0,5);
  gtk_box_pack_start(GTK_BOX(conta_fix_int_box),conta_fix_int_combo,0,0,5);

  gtk_box_pack_start(GTK_BOX(conta_fix_valor_box),conta_fix_valor_entry,0,0,5);

  gtk_box_pack_start(GTK_BOX(opcoes_box),conta_fix_concluir_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box),conta_fix_deletar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box),conta_fix_cancelar_button,0,0,5);

  gtk_container_add(GTK_CONTAINER(conta_fix_id_frame),conta_fix_id_box);
  gtk_container_add(GTK_CONTAINER(conta_fix_descr_frame),conta_fix_descr_box);
  gtk_container_add(GTK_CONTAINER(conta_fix_forn_frame),conta_fix_forn_box);
  gtk_container_add(GTK_CONTAINER(conta_fix_dtini_frame),conta_fix_dtini_box);
  gtk_container_add(GTK_CONTAINER(conta_fix_dtend_frame),conta_fix_dtend_box);
  gtk_container_add(GTK_CONTAINER(conta_fix_int_frame),conta_fix_int_box);
  gtk_container_add(GTK_CONTAINER(conta_fix_valor_frame),conta_fix_valor_box);

  gtk_box_pack_start(GTK_BOX(conta_datas_int),conta_fix_dtini_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(conta_datas_int),conta_fix_dtend_frame,0,0,5);

  gtk_box_pack_start(GTK_BOX(conta_fix_box),conta_fix_id_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(conta_fix_box),conta_fix_descr_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(conta_fix_box),conta_fix_forn_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(conta_fix_box),conta_datas_int,0,0,5);
  gtk_box_pack_start(GTK_BOX(conta_fix_box),conta_fix_int_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(conta_fix_box),conta_fix_valor_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(conta_fix_box),opcoes_box,0,0,5);

  conta_fixa_alterando=0, conta_fixa_concluindo=0;
  gtk_container_add(GTK_CONTAINER(janela),conta_fix_box);
  g_signal_connect(conta_fix_id_entry,"activate",G_CALLBACK(cad_conta_fixa_titulo),NULL);
  g_signal_connect(conta_fix_descr_entry,"activate",G_CALLBACK(cad_conta_fixa_descr),NULL);
  g_signal_connect(conta_fix_forn_entry,"activate",G_CALLBACK(cad_conta_fixa_fornecedor),NULL);
  g_signal_connect(conta_fix_dtini_entry,"activate",G_CALLBACK(cad_conta_fixa_dtinicial),NULL);
  g_signal_connect(conta_fix_dtend_entry,"activate",G_CALLBACK(cad_conta_fixa_dtfinal),NULL);
  g_signal_connect(conta_fix_int_entry,"activate",G_CALLBACK(cad_conta_fixa_intervalo),NULL);
  g_signal_connect(conta_fix_int_combo,"popdown",G_CALLBACK(cad_conta_fixa_tipo),NULL);
  g_signal_connect(conta_fix_valor_entry,"activate",G_CALLBACK(cad_conta_fixa_vlr),NULL);

  g_signal_connect(conta_fix_pesq_id,"clicked",G_CALLBACK(psq_fin_pag),conta_fix_id_entry);
  g_signal_connect(conta_fix_pesq_forn,"clicked",G_CALLBACK(psq_ter),conta_fix_forn_entry);
  g_signal_connect(conta_fix_pesq_dtini,"clicked",G_CALLBACK(psq_data),conta_fix_dtini_entry);
  g_signal_connect(conta_fix_pesq_dtend,"clicked",G_CALLBACK(psq_data),conta_fix_dtend_entry);

  g_signal_connect(conta_fix_concluir_button,"clicked",G_CALLBACK(cad_conta_fixa_concluir),NULL);
  g_signal_connect(conta_fix_deletar_button,"clicked",G_CALLBACK(cad_conta_fixa_deletar),NULL);
  g_signal_connect(conta_fix_alterar_button,"clicked",G_CALLBACK(cad_conta_fixa_alterar),NULL);
  g_signal_connect(conta_fix_cancelar_button,"clicked",G_CALLBACK(cad_conta_fixa_cancelar),NULL);

  gtk_entry_set_text(GTK_ENTRY(conta_fix_id_entry),task);
  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[CAD_CONT_FIX_WND]);
  gtk_widget_show_all(janela);
  return 0;
}
