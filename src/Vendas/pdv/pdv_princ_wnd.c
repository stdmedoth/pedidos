#include "itens.c"
#include "shortcuts.c"
#include "acoes/adicionar_item.c"
#include "acoes/pesquisar_item.c"
#include "acoes/remover_item.c"
#include "acoes/fechar_cupom.c"

int pdv_princ_wnd(){

  if(!caixas_qnt()){
    if(janela_criar_caixa())
      return 1;
  }

  struct _maquina *maquina_atual = maquinas_get_atual();
  if(!maquina_atual){
    return 1;
  }

  struct _caixa *caixa = caixa_get_aberto(maquina_atual);
  if(!caixa){
    return 1;
  }

  if(caixa->status == CAIXA_FECHADO){
    if(janela_abrir_caixa(maquina_atual, caixa))
      return 1;

    struct _caixa *caixa = caixa_get_aberto(maquina_atual);
  }

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN], nome_oper[40];
  strcpy(nome_oper, "");
  sprintf(query,"select nome from operadores where code = %i",caixa->operador);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível receber informação do operador");
  }else{
    if(!(row = mysql_fetch_row(res))){
      popup(NULL,"Operador não encontrado");
    }else{
      strcpy(nome_oper,row[0]);
    }
  }

  if(caixa->operador != sessao_oper.code){
    gchar *msg = malloc(100);
    sprintf(msg,"Caixa já aberto para operador %s", nome_oper);
    popup(NULL,msg);
    return 1;
  }

  pdv_venda_atual = malloc(sizeof(struct _pdv_venda_atual));
  pdv_venda_atual->operacao_atual = PDV_NULL_OPER;
  pdv_venda_atual->status_atual = PDV_SEM_VENDA;
  pdv_venda_atual->caixa_atual = caixa;
  pdv_venda_atual->cupom_atual = malloc(sizeof(struct _CFe));
  pdv_venda_atual->pdv_item_atual = malloc(sizeof(struct _pdv_item_atual));

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name(janela,"janela_pdv");
  gtk_widget_hide_on_delete(janela);
  gtk_window_maximize(GTK_WINDOW(janela));
  gtk_window_set_decorated(GTK_WINDOW(janela),FALSE);
  gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
  janelas_gerenciadas.vetor_janelas[REG_PDV_WND].reg_id = REG_PDV_WND;
  janelas_gerenciadas.vetor_janelas[REG_PDV_WND].aberta = 1;
  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_PDV_WND]))
    return 1;
  janelas_gerenciadas.vetor_janelas[REG_PDV_WND].janela_pointer = janela;

  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_PDV_WND]);

  GtkWidget *caixa_principal = gtk_box_new(1,0);
  GtkWidget *container_pdv_principal = gtk_box_new(0,0);
  GtkWidget *container_pdv_itens = gtk_box_new(1,0);
  GtkWidget *container_pdv_logo = gtk_box_new(0,0);
  GtkWidget *pdv_logo_img = gtk_image_new_from_file(PDV_LOGO);
  gtk_box_pack_start(GTK_BOX(container_pdv_logo),pdv_logo_img,0,0,0);
  gtk_box_pack_start(GTK_BOX(container_pdv_principal),container_pdv_logo,0,0,5);

  GtkWidget *logoheader_pdv = gtk_image_new_from_file(LOGO_HEADER);
  gtk_widget_set_name(logoheader_pdv,"logoheader");
  GtkWidget *header_layout = gtk_layout_new(NULL,NULL);
  GtkWidget *fechar_button = gtk_button_new();

  GtkWidget *info_caixa = gtk_label_new (NULL);
  char *str = malloc(300);

  sprintf(str,"%s : %s",caixa->nome, nome_oper);
  gtk_label_set_text(GTK_LABEL(info_caixa),str);
  gtk_widget_set_name(info_caixa,"infos_caixa");

  GtkWidget *encerrar_caixa = gtk_button_new_with_label("Encerrar Caixa");
  gtk_button_set_image(GTK_BUTTON(fechar_button),gtk_image_new_from_file(IMG_CANCEL));

  GtkWidget *container_pdv = gtk_box_new(1,0);
  gtk_box_pack_start(GTK_BOX(container_pdv_principal),container_pdv,0,0,5);

  GtkWidget *footer_pdv = gtk_box_new(0,0);
  GtkWidget *opcoes_header = gtk_box_new(0,0);
  gtk_box_pack_start(GTK_BOX(opcoes_header),encerrar_caixa,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_header),fechar_button,0,0,5);

  gtk_layout_put(GTK_LAYOUT(header_layout),logoheader_pdv,0,0);
  gtk_layout_put(GTK_LAYOUT(header_layout),info_caixa,25,25);
  gtk_layout_put(GTK_LAYOUT(header_layout),opcoes_header,1100,25);

  gtk_widget_set_size_request(header_layout,1366,90);

  pdv_prodcod_label = gtk_label_new("0");
  GtkWidget *line = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  GtkWidget *pdv_prodcod_box = gtk_box_new(1,0);
  GtkWidget *pdv_prodcod_frame = gtk_frame_new("Formulação:");
  GtkWidget *pdv_prodcod_fixed = gtk_fixed_new();
  pdv_acaoatual_label = gtk_label_new("Bem Vindo");
  gtk_frame_set_shadow_type(GTK_FRAME(pdv_prodcod_frame),GTK_SHADOW_NONE);
  gtk_widget_set_name(pdv_prodcod_frame,"code_prod");
  gtk_box_pack_start(GTK_BOX(pdv_prodcod_box),pdv_prodcod_label,0,0,10);
  gtk_box_pack_start(GTK_BOX(pdv_prodcod_box),line,0,0,0);
  gtk_box_pack_start(GTK_BOX(pdv_prodcod_box),pdv_acaoatual_label,0,0,0);
  gtk_container_add(GTK_CONTAINER(pdv_prodcod_frame),pdv_prodcod_box);
  gtk_fixed_put(GTK_FIXED(pdv_prodcod_fixed),pdv_prodcod_frame,20,20);
  gtk_widget_set_size_request(pdv_prodcod_box,700,100);
  gtk_widget_set_size_request(pdv_prodcod_frame,700,100);

  GtkWidget *vendas = get_pdv_itens_container();
  GtkWidget *pdv_itens_box = gtk_box_new(1,0);
  GtkWidget *pdv_itens_frame = gtk_frame_new("Itens:");
  GtkWidget *pdv_itens_fixed = gtk_fixed_new();
  gtk_widget_set_size_request(pdv_itens_box,700,360);
  gtk_widget_set_size_request(pdv_itens_frame,700,360);
  gtk_box_pack_start(GTK_BOX(pdv_itens_box),vendas,0,0,0);
  gtk_container_add(GTK_CONTAINER(pdv_itens_frame),pdv_itens_box);
  gtk_fixed_put(GTK_FIXED(pdv_itens_fixed),pdv_itens_frame,20,20);

  gtk_box_pack_start(GTK_BOX(container_pdv_itens),pdv_prodcod_fixed,0,0,10 );
  gtk_box_pack_start(GTK_BOX(container_pdv_itens),pdv_itens_fixed,0,0,10 );

  gtk_box_pack_start(GTK_BOX(container_pdv_principal),container_pdv_itens,0,0,10 );

  pdv_codprod_entry = gtk_entry_new();
  GtkWidget *pdv_psqcodprod_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(pdv_psqcodprod_button), gtk_image_new_from_file(IMG_PESQ));
  GtkWidget *pdv_codprod_box = gtk_box_new(0,0);
  GtkWidget *pdv_codprod_frame = gtk_frame_new("Produto");
  gtk_box_pack_start(GTK_BOX(pdv_codprod_box), pdv_codprod_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(pdv_codprod_box), pdv_psqcodprod_button,0,0,5);
  gtk_container_add(GTK_CONTAINER(pdv_codprod_frame), pdv_codprod_box);
  pdv_qntprod_entry = gtk_spin_button_new_with_range(0,100,0.05);
  GtkWidget *pdv_qntprod_frame = gtk_frame_new("Quantidade");
  gtk_container_add(GTK_CONTAINER(pdv_qntprod_frame), pdv_qntprod_entry);

  pdv_botoes_atalhos = gtk_box_new(0,0);
  pdv_add_item_button = gtk_button_new_with_label("Adicionar Item (A)");
  pdv_rem_item_button = gtk_button_new_with_label("Remover Item (R)");
  pdv_psq_item_button = gtk_button_new_with_label("Pesquisar Item (P)");
  pdv_fecha_cupom_button = gtk_button_new_with_label("Fechar Cupom (F)");
  gtk_box_pack_start(GTK_BOX(pdv_botoes_atalhos), pdv_add_item_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(pdv_botoes_atalhos), pdv_rem_item_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(pdv_botoes_atalhos), pdv_psq_item_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(pdv_botoes_atalhos), pdv_fecha_cupom_button,0,0,5);

  gtk_box_pack_start(GTK_BOX(footer_pdv), pdv_botoes_atalhos,0,0,5);
  gtk_box_pack_start(GTK_BOX(footer_pdv), pdv_codprod_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(footer_pdv), pdv_qntprod_frame,0,0,5);
  gtk_entry_set_width_chars(GTK_ENTRY(pdv_codprod_entry), 30);

  gtk_box_pack_start(GTK_BOX(caixa_principal),header_layout,0,0,0);
  gtk_box_pack_start(GTK_BOX(caixa_principal),container_pdv_principal,0,0,0);
  gtk_box_pack_start(GTK_BOX(caixa_principal),footer_pdv,0,0,0);

  gtk_container_add(GTK_CONTAINER(janela),caixa_principal);
  gtk_widget_show_all(janela);

  g_signal_connect(pdv_add_item_button,"clicked",G_CALLBACK(pdv_add_item_fun),NULL);
  g_signal_connect(pdv_rem_item_button,"clicked",G_CALLBACK(pdv_rem_item_fun),pdv_itens_treeview);
  g_signal_connect(pdv_psq_item_button,"clicked",G_CALLBACK(pdv_psq_item_fun),NULL);

  g_signal_connect(pdv_codprod_entry,"activate",G_CALLBACK(pdv_codprod_fun),NULL);
  g_signal_connect(pdv_psqcodprod_button,"clicked",G_CALLBACK(pdv_psq_item_fun),NULL);
  g_signal_connect(pdv_fecha_cupom_button,"clicked",G_CALLBACK(pdv_fecha_cupom_fun),NULL);
  g_signal_connect(janela,"key-press-event",G_CALLBACK(pdv_bind_atalhos),NULL);

  gtk_widget_set_name(pdv_add_item_button,"AddItemButton");
  gtk_widget_set_name(pdv_add_item_button,"AddItemButton");

  abrir_css(PDV_SHORTCUTS);

  gtk_widget_hide(pdv_qntprod_frame);

  g_signal_connect(encerrar_caixa,"clicked",G_CALLBACK(signal_caixa_encerramento),caixa);
  g_signal_connect(fechar_button,"clicked",G_CALLBACK(close_window_callback),janela);
  return 0;
}
