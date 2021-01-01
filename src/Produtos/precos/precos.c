#include "campos/codigo.c"
#include "campos/nome.c"
#include "campos/produto.c"
#include "campos/vlr_faturado.c"
#include "campos/vlr_vista.c"

#include "concluir.c"
#include "alterar.c"
#include "cancelar.c"
#include "excluir.c"

int prod_precos_wnd(){

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name(janela,"precos");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Preços");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"system-software-install");
  if(janelas_gerenciadas.vetor_janelas[REG_CAD_PROD].aberta)
    gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janelas_gerenciadas.vetor_janelas[REG_CAD_PROD].janela_pointer));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

  janelas_gerenciadas.vetor_janelas[REG_PROD_PRC].reg_id = REG_PROD_PRC;
	janelas_gerenciadas.vetor_janelas[REG_PROD_PRC].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_PROD_PRC]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_PROD_PRC].janela_pointer = janela;

  GtkWidget *box, *linha1, *linha2, *linha3, *opcoes_box;

  box = gtk_box_new(1,0);
  linha1 = gtk_box_new(0,0);
  linha2 = gtk_box_new(0,0);
  linha3 = gtk_box_new(0,0);
  opcoes_box = gtk_box_new(0,0);

  GtkWidget *prod_prc_code_frame = gtk_frame_new("Código");
  GtkWidget *prod_prc_nome_frame = gtk_frame_new("Nome");
  GtkWidget *prod_prc_prodcode_frame = gtk_frame_new("Produto");
  GtkWidget *prod_prc_vlrfat_frame = gtk_frame_new("Faturado");
  GtkWidget *prod_prc_vlrvist_frame = gtk_frame_new("A Vista");
  GtkWidget *prod_prc_code_box = gtk_box_new(0,0);
  GtkWidget *prod_prc_prod_box = gtk_box_new(0,0);
  GtkWidget *prod_prc_tab_box = gtk_box_new(0,0);
  GtkWidget *prod_prc_vlrfat_box = gtk_box_new(0,0);
  GtkWidget *prod_prc_vlrvist_box = gtk_box_new(0,0);

  prod_prc_concluir_button = gtk_button_new_with_label("Concluir");
  gtk_button_set_image(GTK_BUTTON(prod_prc_concluir_button), gtk_image_new_from_file(IMG_OK));
  prod_prc_alterar_button = gtk_button_new_with_label("Alterar");
  gtk_button_set_image(GTK_BUTTON(prod_prc_alterar_button), gtk_image_new_from_file(IMG_ALTER));
  prod_prc_cancelar_button = gtk_button_new_with_label("Cancelar");
  gtk_button_set_image(GTK_BUTTON(prod_prc_cancelar_button), gtk_image_new_from_file(IMG_CANCEL));
  prod_prc_excluir_button = gtk_button_new_with_label("Excluir");
  gtk_button_set_image(GTK_BUTTON(prod_prc_excluir_button), gtk_image_new_from_file(IMG_EXCLUI));
  prod_prc_prodpsq_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(prod_prc_prodpsq_button), gtk_image_new_from_file(IMG_PESQ));
  prod_prc_codepsq_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(prod_prc_codepsq_button), gtk_image_new_from_file(IMG_PESQ));

  prod_prc_code_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(prod_prc_code_entry), 8);
  prod_prc_nome_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(prod_prc_nome_entry), 20);
  prod_prc_prodcode_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(prod_prc_prodcode_entry), 8);
  prod_prc_prodnome_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(prod_prc_prodnome_entry), 30);
  prod_prc_vlrfat_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(prod_prc_vlrfat_entry), 10);
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(prod_prc_vlrfat_entry), GTK_ENTRY_ICON_PRIMARY, "money");
  prod_prc_vlrvist_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(prod_prc_vlrvist_entry), 10);
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(prod_prc_vlrvist_entry), GTK_ENTRY_ICON_PRIMARY, "money");

  gtk_box_pack_start(GTK_BOX(prod_prc_code_box),prod_prc_code_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(prod_prc_code_box),prod_prc_codepsq_button,0,0,0);

  gtk_box_pack_start(GTK_BOX(prod_prc_prod_box),prod_prc_prodcode_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(prod_prc_prod_box),prod_prc_prodpsq_button,0,0,0);
  gtk_box_pack_start(GTK_BOX(prod_prc_prod_box),prod_prc_prodnome_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(prod_prc_tab_box),prod_prc_nome_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(prod_prc_vlrfat_box),prod_prc_vlrfat_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(prod_prc_vlrvist_box),prod_prc_vlrvist_entry,0,0,0);

  gtk_container_add(GTK_CONTAINER(prod_prc_code_frame), prod_prc_code_box );
  gtk_container_add(GTK_CONTAINER(prod_prc_prodcode_frame), prod_prc_prod_box );
  gtk_container_add(GTK_CONTAINER(prod_prc_nome_frame), prod_prc_tab_box );
  gtk_container_add(GTK_CONTAINER(prod_prc_vlrfat_frame), prod_prc_vlrfat_box );
  gtk_container_add(GTK_CONTAINER(prod_prc_vlrvist_frame), prod_prc_vlrvist_box );

  gtk_box_pack_start(GTK_BOX(linha1), prod_prc_code_frame,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha1), prod_prc_nome_frame,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha2), prod_prc_prodcode_frame,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha3), prod_prc_vlrfat_frame,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha3), prod_prc_vlrvist_frame,0,0,0);

  gtk_box_pack_start(GTK_BOX(opcoes_box), prod_prc_concluir_button,0,0,0);
  gtk_box_pack_start(GTK_BOX(opcoes_box), prod_prc_alterar_button,0,0,0);
  gtk_box_pack_start(GTK_BOX(opcoes_box), prod_prc_cancelar_button,0,0,0);
  gtk_box_pack_start(GTK_BOX(opcoes_box), prod_prc_excluir_button,0,0,0);

  gtk_box_pack_start(GTK_BOX(box), linha1,0,0,5);
  gtk_box_pack_start(GTK_BOX(box), linha2,0,0,5);
  gtk_box_pack_start(GTK_BOX(box), linha3,0,0,5);
  gtk_box_pack_start(GTK_BOX(box), opcoes_box,0,0,5);

  gtk_container_add(GTK_CONTAINER(janela), box);

  prod_precos_cancelar_fun();

  g_signal_connect(prod_prc_code_entry, "activate",  G_CALLBACK(prod_precos_code_fun),NULL);
  g_signal_connect(prod_prc_nome_entry, "activate",  G_CALLBACK(prod_precos_nome_fun),NULL);
  g_signal_connect(prod_prc_prodcode_entry, "activate",  G_CALLBACK(prod_precos_prod_fun),NULL);
  g_signal_connect(prod_prc_vlrfat_entry, "activate",  G_CALLBACK(prod_precos_vltfat_fun),NULL);
  g_signal_connect(prod_prc_vlrvist_entry, "activate",  G_CALLBACK(prod_precos_vlrvist_fun),NULL);

  g_signal_connect(prod_prc_codepsq_button, "clicked",  G_CALLBACK(psq_preco), prod_prc_code_entry);
  g_signal_connect(prod_prc_prodpsq_button, "clicked",  G_CALLBACK(psq_prod), prod_prc_prodcode_entry);

  g_signal_connect(prod_prc_concluir_button, "clicked",  G_CALLBACK(prod_precos_concluir_fun),NULL);
  g_signal_connect(prod_prc_alterar_button, "clicked",  G_CALLBACK(prod_precos_alterar_fun),NULL);
  g_signal_connect(prod_prc_cancelar_button, "clicked",  G_CALLBACK(prod_precos_cancelar_fun),NULL);
  g_signal_connect(prod_prc_excluir_button, "clicked",  G_CALLBACK(prod_precos_excluir_fun),NULL);
  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_PROD_PRC]);

  gtk_widget_show_all(janela);

  return 0;
}
