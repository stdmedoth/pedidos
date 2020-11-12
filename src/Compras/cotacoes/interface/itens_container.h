int cotat_itens_prod_fun(GtkEntry *entry, int pos);
int cotat_itens_qnt_fun(GtkEntry *entry, int pos);
int cotat_itens_prc_fun(GtkEntry *entry, int pos);

int contac_get_ult_pos();

GtkWidget *cotac_scroll;

int *cotac_pPos, *cotac_ativo;
int cotac_produto_inserido[MAX_COTAC_ITENS];
int cotac_container_exists[MAX_VETOR_POSCODE];

GtkWidget *cotac_partc_itens;
GtkWidget **cotac_prod_frames;
GtkWidget *cotac_itens_grid;

int cotac_add_item();
int cotac_rem_item(GtkWidget *widget, int pos);

int cotac_get_livre_pos();

GtkWidget **cotac_prod_cod_entry, **cotac_prod_nome_entry, **cotac_psq_prod_button,
**cotac_prod_partc_entrys,
**cotac_prod_qnt_entry, **cotac_prod_prc_entry, **cotac_rem_button;

GtkWidget *cotac_add_button;

GtkWidget *cotac_get_itens_container(int cod);
