#include "campos/codigo.c"
#include "campos/modulos.c"
#include "campos/ativo.c"
#include "campos/vencimento.c"

#include "concluir.c"
#include "cancelar.c"
#include "alterar.c"

int contratos_get_modulos_qnt(){
  int qnt=0;
  if(ativar.cadastro)
    qnt++;
  if(ativar.compras)
    qnt++;
  if(ativar.faturamento)
    qnt++;
  if(ativar.estoque)
    qnt++;
  if(ativar.financeiro)
    qnt++;
  if(ativar.marketing)
    qnt++;
  if(ativar.relatorios)
    qnt++;
  if(ativar.tecnicos)
    qnt++;

  return qnt;
}

int cad_contratos(){

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  janelas_gerenciadas.vetor_janelas[REG_CAD_CNTRATS].reg_id = REG_CAD_CNTRATS;
	janelas_gerenciadas.vetor_janelas[REG_CAD_CNTRATS].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_CAD_CNTRATS]))
		return 1;

	gtk_widget_set_name(janela,"contratos");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Contratos");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"edit-paste");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
  gtk_widget_set_size_request(janela, 300,300);
	janelas_gerenciadas.vetor_janelas[REG_CAD_CNTRATS].janela_pointer = janela;
  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_CAD_CNTRATS]);

  GtkWidget *caixa, *caixa_opcoes;
  GtkWidget *grid, *scroll, *fixed;
  GtkWidget *cntrats_code_psq_button = gtk_button_new();
  GtkWidget *cntrats_code_box = gtk_box_new(0,0);
  GtkWidget *cntrats_code_frame = gtk_frame_new("Contrato");

  gtk_button_set_image(GTK_BUTTON(cntrats_code_psq_button), gtk_image_new_from_file(IMG_PESQ));

  cntrats_concluir_button = gtk_button_new_with_label("Concluir");
  cntrats_alterar_button = gtk_button_new_with_label("Alterar");
  cntrats_cancelar_button = gtk_button_new_with_label("Cancelar");

  fixed = gtk_fixed_new();
  caixa = gtk_box_new(1,0);
  caixa_opcoes = gtk_box_new(0,0);
  grid = gtk_grid_new();
  scroll = gtk_scrolled_window_new(NULL,NULL);

  gtk_box_pack_start(GTK_BOX(caixa_opcoes), cntrats_concluir_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(caixa_opcoes), cntrats_alterar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(caixa_opcoes), cntrats_cancelar_button,0,0,5);

  cntrats_code_entry = gtk_entry_new();
  cntrats_ativo_check = gtk_check_button_new_with_label("Ativo?");
  gtk_box_pack_start(GTK_BOX(cntrats_code_box), cntrats_code_entry,0,0,5);
  gtk_box_pack_start(GTK_BOX(cntrats_code_box), cntrats_code_psq_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(cntrats_code_box), cntrats_ativo_check,0,0,5);
  gtk_container_add(GTK_CONTAINER(cntrats_code_frame), cntrats_code_box);
  cntrats_cadastro_check = gtk_check_button_new_with_label("Módulo Cadastros");
  cntrats_compras_check = gtk_check_button_new_with_label("Módulo Compras");
  cntrats_faturamento_check = gtk_check_button_new_with_label("Módulo Faturamento");
  cntrats_estoque_check = gtk_check_button_new_with_label("Módulo Estoque");
  cntrats_financeiro_check = gtk_check_button_new_with_label("Módulo Financeiro");
  cntrats_marketing_check = gtk_check_button_new_with_label("Módulo Marketing");
  cntrats_relatorios_check = gtk_check_button_new_with_label("Módulo Relatórios");
  cntrats_vencimento_entry = gtk_entry_new();

  GtkWidget *cntrats_vencimento_frame = gtk_frame_new("Vencimento");
  GtkWidget *cntrats_vencimento_box = gtk_box_new(0,0);
  gtk_box_pack_start(GTK_BOX(cntrats_vencimento_box), cntrats_vencimento_entry,0,0,0);
  gtk_container_add(GTK_CONTAINER(cntrats_vencimento_frame), cntrats_vencimento_box);

  gtk_grid_attach(GTK_GRID(grid), cntrats_cadastro_check,0,0,1,1);
  gtk_grid_attach(GTK_GRID(grid), cntrats_compras_check,0,1,1,1);
  gtk_grid_attach(GTK_GRID(grid), cntrats_faturamento_check,0,2,1,1);
  gtk_grid_attach(GTK_GRID(grid), cntrats_estoque_check,0,3,1,1);
  gtk_grid_attach(GTK_GRID(grid), cntrats_financeiro_check,0,4,1,1);
  gtk_grid_attach(GTK_GRID(grid), cntrats_marketing_check,0,5,1,1);
  gtk_grid_attach(GTK_GRID(grid), cntrats_relatorios_check,0,6,1,1);
  gtk_grid_attach(GTK_GRID(grid), cntrats_vencimento_frame,0,7,1,1);

  gtk_box_pack_start(GTK_BOX(caixa), cntrats_code_frame,0,0,10);
  gtk_box_pack_start(GTK_BOX(caixa), grid,0,0,10);
  gtk_box_pack_start(GTK_BOX(caixa), caixa_opcoes,0,0,10);

  gtk_fixed_put(GTK_FIXED(fixed), caixa, 20,20);


  g_signal_connect(cntrats_code_psq_button, "clicked", G_CALLBACK(psq_cntrat), cntrats_code_entry);
  g_signal_connect(cntrats_code_entry, "activate", G_CALLBACK(cntrats_code_fun), NULL);
  g_signal_connect(cntrats_vencimento_entry, "activate", G_CALLBACK(cntrats_vencimento_fun), NULL);

  g_signal_connect(cntrats_concluir_button, "clicked", G_CALLBACK(cntrats_concluir_fun), NULL);
  g_signal_connect(cntrats_alterar_button, "clicked", G_CALLBACK(cntrats_alterar_fun), NULL);
  g_signal_connect(cntrats_cancelar_button, "clicked", G_CALLBACK(cntrats_cancelar_fun), NULL);

  gtk_container_add(GTK_CONTAINER(janela)  , fixed);
  cntrats_cancelar_fun();
  gtk_widget_show_all(janela);

  return 0;
}
