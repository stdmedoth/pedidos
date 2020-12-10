#include "campos/codigo.c"
#include "campos/nome.c"
#include "campos/adicionar_pessoa.c"
#include "campos/remover_pessoa.c"

#include "alterar.c"
#include "excluir.c"
#include "cancelar.c"
#include "concluir.c"

int mkt_cad_distrib_fun(){

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name(janela,"Distribuicao");
  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_title(GTK_WINDOW(janela),"Lista de Distribuicao");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"mail-reply-all");
  gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
  gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
  //gtk_widget_set_size_request(janela,);

  janelas_gerenciadas.vetor_janelas[REG_MAILDSTRB_WND].reg_id = REG_MAILDSTRB_WND;
  janelas_gerenciadas.vetor_janelas[REG_MAILDSTRB_WND].aberta = 1;
  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_MAILDSTRB_WND]))
    return 1;
  janelas_gerenciadas.vetor_janelas[REG_MAILDSTRB_WND].janela_pointer = janela;

  GtkWidget *distrib_code_frame;
  GtkWidget *distrib_nome_frame;
  GtkWidget *distrib_code_box;
  GtkWidget *distrib_nome_box;
  GtkWidget *distrib_pessoas_box, *distrib_pessoas_scroll, *distrib_pessoas_fixed, *distrib_pessoas_frame;
  GtkWidget *distrib_pessoas_add_fixed;
  GtkWidget *linha1, *linha2, *opcoes_box;
  GtkWidget *box;

  enum{
    ID,
    NOME,
    EMAIL,
    CELULAR,
    TELEFONE,
    N_COLS
  };

  box = gtk_box_new(1,0);
  linha1 = gtk_box_new(0,0);
  linha2 = gtk_box_new(0,0);
  opcoes_box = gtk_box_new(0,0);

  distrib_code_entry = gtk_entry_new();
  distrib_code_frame = gtk_frame_new("Código");
  distrib_code_psq_button = gtk_button_new();
  gtk_entry_set_width_chars(GTK_ENTRY(distrib_code_entry), 8);
  gtk_button_set_image(GTK_BUTTON(distrib_code_psq_button), gtk_image_new_from_file(IMG_PESQ));
  distrib_code_box = gtk_box_new(0,0);
  distrib_nome_entry = gtk_entry_new();
  distrib_pessoacode_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(distrib_nome_entry), 30);
  distrib_nome_box = gtk_box_new(0,0);
  distrib_nome_frame = gtk_frame_new("Nome");
  distrib_pessoas_add_fixed = gtk_fixed_new();

  distrib_pessoas_box = gtk_box_new(0,0);
  distrib_pessoas_scroll = gtk_scrolled_window_new(NULL,NULL);
  distrib_pessoas_fixed = gtk_fixed_new();
  distrib_pessoas_frame = gtk_frame_new("Destinos");

  gtk_box_pack_start(GTK_BOX(distrib_code_box), distrib_code_entry,0,0,5);
  gtk_box_pack_start(GTK_BOX(distrib_code_box), distrib_code_psq_button,0,0,5);

  gtk_container_add(GTK_CONTAINER(distrib_code_frame), distrib_code_box);

  gtk_box_pack_start(GTK_BOX(distrib_nome_box), distrib_nome_entry,0,0,5);
  gtk_container_add(GTK_CONTAINER(distrib_nome_frame), distrib_nome_box);

  gtk_box_pack_start(GTK_BOX(linha1), distrib_code_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(linha1), distrib_nome_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(linha1), distrib_pessoacode_entry,0,0,5);

  distrib_pessoas_treeview = gtk_tree_view_new();
  distrib_pessoas_add_button = gtk_button_new_with_label("Adicionar");
  gtk_widget_set_size_request(distrib_pessoas_treeview, 500, 400);
  gtk_widget_set_size_request(distrib_pessoas_scroll, 500, 400);
  gtk_button_set_image(GTK_BUTTON(distrib_pessoas_add_button), gtk_image_new_from_file(IMG_MAIS));
  gtk_fixed_put(GTK_FIXED(distrib_pessoas_add_fixed), distrib_pessoas_add_button, 20,20);

  gtk_box_pack_start(GTK_BOX(distrib_pessoas_box), distrib_pessoas_treeview,0,0,5);
  gtk_container_add(GTK_CONTAINER(distrib_pessoas_scroll), distrib_pessoas_box);
  gtk_container_add(GTK_CONTAINER(distrib_pessoas_frame), distrib_pessoas_scroll);
  gtk_fixed_put(GTK_FIXED(distrib_pessoas_fixed), distrib_pessoas_frame, 5, 5);

  GtkTreeStore *distrib_pessoas_model = gtk_tree_store_new(N_COLS, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING);
  GtkCellRenderer *distrib_pessoas_idcell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *distrib_pessoas_idcol = gtk_tree_view_column_new_with_attributes("Id", distrib_pessoas_idcell, "text", ID, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( distrib_pessoas_treeview ), distrib_pessoas_idcol, ID);
  GtkCellRenderer *distrib_pessoas_nomecell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *distrib_pessoas_nomecol = gtk_tree_view_column_new_with_attributes("Nome", distrib_pessoas_nomecell, "text", NOME, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( distrib_pessoas_treeview ), distrib_pessoas_nomecol, NOME);
  GtkCellRenderer *distrib_pessoas_emailcell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *distrib_pessoas_emailcol = gtk_tree_view_column_new_with_attributes("Email", distrib_pessoas_emailcell, "text", EMAIL, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( distrib_pessoas_treeview ), distrib_pessoas_emailcol, EMAIL);
  GtkCellRenderer *distrib_pessoas_celularcell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *distrib_pessoas_celularcol = gtk_tree_view_column_new_with_attributes("Celular", distrib_pessoas_celularcell, "text", CELULAR, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( distrib_pessoas_treeview ), distrib_pessoas_celularcol, CELULAR);
  GtkCellRenderer *distrib_pessoas_telefonecell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *distrib_pessoas_telefonecol = gtk_tree_view_column_new_with_attributes("Telefone" , distrib_pessoas_telefonecell, "text", TELEFONE, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( distrib_pessoas_treeview ), distrib_pessoas_telefonecol, TELEFONE);
  gtk_tree_view_column_set_visible(distrib_pessoas_idcol, FALSE);

  gtk_tree_view_set_model(GTK_TREE_VIEW( distrib_pessoas_treeview ), GTK_TREE_MODEL( distrib_pessoas_model ));

  gtk_box_pack_start(GTK_BOX(linha2), distrib_pessoas_fixed,0,0,5);
  gtk_box_pack_start(GTK_BOX(linha2), distrib_pessoas_add_fixed,0,0,5);

  distrib_confirmar_button = gtk_button_new_with_label("Confirmar");
  distrib_alterar_button = gtk_button_new_with_label("Alterar");
  distrib_cancelar_button = gtk_button_new_with_label("Cancelar");
  distrib_excluir_button = gtk_button_new_with_label("Excluir");

  gtk_box_pack_start(GTK_BOX(opcoes_box), distrib_confirmar_button, 0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box), distrib_alterar_button, 0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box), distrib_cancelar_button, 0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box), distrib_excluir_button, 0,0,5);

  gtk_box_pack_start(GTK_BOX(box), linha1, 0,0,5);
  gtk_box_pack_start(GTK_BOX(box), linha2, 0,0,5);
  gtk_box_pack_start(GTK_BOX(box), opcoes_box, 0,0,5);

  gtk_container_add(GTK_CONTAINER(janela), box);

  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_MAILDSTRB_WND]);

  g_signal_connect(distrib_code_entry,"activate",G_CALLBACK(mkt_cad_distrib_code_fun),NULL);
  g_signal_connect(distrib_nome_entry,"activate",G_CALLBACK(mkt_cad_distrib_nome_fun),NULL);
  g_signal_connect(distrib_pessoacode_entry,"activate",G_CALLBACK(mkt_cad_distrib_add_fun),NULL);

  g_signal_connect(distrib_pessoas_add_button,"clicked",G_CALLBACK(psq_ter),distrib_pessoacode_entry);

  g_signal_connect(distrib_code_psq_button,"clicked",G_CALLBACK(psq_maildistrib),distrib_code_entry);

  g_signal_connect(distrib_pessoas_treeview,"row-activated",G_CALLBACK(mkt_cad_distrib_rem_fun),NULL);

  g_signal_connect(distrib_confirmar_button,"clicked",G_CALLBACK(mkt_cad_distrib_concluir_fun),NULL);
  g_signal_connect(distrib_alterar_button,"clicked",G_CALLBACK(mkt_cad_distrib_alterar_fun),NULL);
  g_signal_connect(distrib_cancelar_button,"clicked",G_CALLBACK(mkt_cad_distrib_cancelar_fun),NULL);
  g_signal_connect(distrib_excluir_button,"clicked",G_CALLBACK(mkt_cad_distrib_excluir_fun),NULL);


  mkt_cad_distrib_cancelar_fun();
  gtk_widget_show_all(janela);
  gtk_widget_hide(distrib_pessoacode_entry);

  return 0;
}
