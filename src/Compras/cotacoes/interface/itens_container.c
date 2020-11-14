#include "add_item.c"
#include "rem_item.c"

GtkWidget *cotac_get_itens_container(int index){

  struct _Terceiros *terceiros = cotac_get_participantes();
  char *nome_item = malloc(500);
  for(int cont=0;cont<terceiros->qnt;cont++){
    if(terceiros->terceiro[cont].index == index)
      sprintf(nome_item,"Item do fornecedor: %s",terceiros->terceiro[cont].razao);
  }

  GtkWidget *container = gtk_box_new(0,0);
  GtkWidget *frame = gtk_frame_new(nome_item);
  cotac_scroll[index] = gtk_scrolled_window_new(NULL,NULL);
  cotac_itens_grid[index] = gtk_grid_new();
  gtk_widget_set_size_request(cotac_itens_grid[index],900,400);
  gtk_widget_set_size_request(cotac_scroll[index],900,400);
  gtk_widget_set_size_request(frame,900,400);
  gtk_widget_set_size_request(container,900,400);

  cotac_ativo[index] = malloc(sizeof(int) *MAX_COTAC_ITENS);
  cotac_pPos[index] = malloc(sizeof(int) *MAX_COTAC_ITENS);
  cotac_produto_inserido[index] = malloc(sizeof(int) *MAX_COTAC_ITENS);

  for(int cont=0;cont<MAX_COTAC_ITENS;cont++){
    g_print("zerando infos em fornecedor %s index %i posicao %i\n",cotac_partc_gchar, index, cont);
    cotac_ativo[index][cont] = 0;
    cotac_pPos[index][cont] = 0;
    cotac_produto_inserido[index][cont] = 0;
  }

  cotac_container_exists[index] = 1;
  gtk_container_add (GTK_CONTAINER(cotac_scroll[index]), cotac_itens_grid[index]);
  gtk_box_pack_start (GTK_BOX(container), cotac_scroll[index],0,0,5);
  gtk_container_add (GTK_CONTAINER(frame), container);

  cotac_prod_cod_entry[index] = malloc( sizeof( GtkWidget* ) *MAX_COTAC_ITENS );
  cotac_psq_prod_button[index] = malloc (sizeof( GtkWidget* ) *MAX_COTAC_ITENS );
  cotac_prod_nome_entry[index] = malloc (sizeof( GtkWidget* ) *MAX_COTAC_ITENS );
  cotac_prod_qnt_entry[index] = malloc( sizeof( GtkWidget* ) *MAX_COTAC_ITENS );
  cotac_prod_prc_entry[index] = malloc( sizeof( GtkWidget* ) *MAX_COTAC_ITENS );
  cotac_rem_button[index] = malloc( sizeof(GtkWidget* ) *MAX_COTAC_ITENS );
  cotac_prod_frames[index] = malloc( sizeof( GtkWidget* ) *MAX_COTAC_ITENS );
  cotacao_new->cotacao_itens[index] = malloc(sizeof(struct _contacao_itens *) *MAX_COTAC_ITENS );

  cotac_add_item(NULL,index);

  return frame;
}
