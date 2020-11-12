#include "add_item.c"
#include "rem_item.c"

GtkWidget *cotac_get_itens_container(int cod){
  GtkWidget *container = gtk_box_new(0,0);
  char *nome_item = malloc(20);
  sprintf(nome_item,"Item do fornecedor: %i",cod);
  GtkWidget *frame = gtk_frame_new(nome_item);
  cotac_scroll = gtk_scrolled_window_new(NULL,NULL);
  cotac_itens_grid = gtk_grid_new();
  gtk_widget_set_size_request(cotac_itens_grid,700,300);
  gtk_widget_set_size_request(frame,700,300);
  gtk_widget_set_size_request(cotac_scroll,700,300);
  gtk_widget_set_size_request(container,700,300);

  cotac_pPos = malloc(sizeof(int*)*MAX_COTAC_ITENS);
  cotac_ativo = malloc(sizeof(int*)*MAX_COTAC_ITENS);

  for(int cont=0;cont<MAX_COTAC_ITENS;cont++){
    cotac_ativo[cont] = 0;
    cotac_pPos[cont] = 0;
    cotac_produto_inserido[cont] = 0;
  }

  gtk_container_add (GTK_CONTAINER(cotac_scroll), cotac_itens_grid);
  gtk_box_pack_start (GTK_BOX(container), cotac_scroll,0,0,5);
  gtk_container_add (GTK_CONTAINER(frame), container);

  cotac_prod_cod_entry = malloc(sizeof(GtkWidget *) *MAX_COTAC_ITENS);
  cotac_psq_prod_button = malloc(sizeof(GtkWidget *) *MAX_COTAC_ITENS);
  cotac_prod_nome_entry = malloc(sizeof(GtkWidget *) *MAX_COTAC_ITENS);
  cotac_prod_qnt_entry = malloc(sizeof(GtkWidget *) *MAX_COTAC_ITENS);
  cotac_prod_prc_entry = malloc(sizeof(GtkWidget *) *MAX_COTAC_ITENS);
  cotac_rem_button = malloc(sizeof(GtkWidget *) *MAX_COTAC_ITENS);
  cotac_prod_frames = malloc(sizeof(GtkWidget *) *MAX_COTAC_ITENS);

  cotac_add_item();

  return frame;
}
