#define MAX_ICO_QNT 24
#define LINE_ICO_QNT 2
#define ICOL 5
#define CAD_ICO_QNT 8
#define EST_ICO_QNT 3
#define VND_ICO_QNT 1
#define CMP_ICO_QNT 4
#define REL_ICO_QNT 3

//cadastros 
GtkWidget *prd_ico, *prd_lbl; //produtos
GtkWidget *ter_ico, *ter_lbl; //terceiros
GtkWidget *opr_ico, *opr_lbl; //operadores
GtkWidget *trs_ico, *trs_lbl; //transacoes
GtkWidget *und_ico, *und_lbl; //unidades
GtkWidget *ftr_ico, *ftr_lbl; //fatores
GtkWidget *vin_ico, *vin_lbl; //vinculos
GtkWidget *grp_ico, *grp_lbl; //grupos
GtkWidget *crel_ico,*crel_lbl; //grupos

//estoque
GtkWidget *est_ico, *est_lbl; //estoques
GtkWidget *ent_ico, *ent_lbl; //entrada
GtkWidget *sai_ico, *sai_lbl; //saida
GtkWidget *sld_ico, *sld_lbl; //saldo

//vendas
GtkWidget *orc_ico, *orc_lbl;
GtkWidget *ped_ico, *ped_lbl;

//compras
GtkWidget *sol_ico, *sol_lbl;
GtkWidget *cot_ico, *cot_lbl;
GtkWidget *ord_ico, *ord_lbl;
GtkWidget *ent_nfe_ico, *ent_nfe_lbl;

//relatorios
GtkWidget *rel_prd_ico, *rel_prd_lbl;
GtkWidget *rel_ter_ico, *rel_ter_lbl;
GtkWidget *rel_est_ico, *rel_est_lbl;

GtkWidget *cad_box[CAD_ICO_QNT];
GtkWidget *est_box[EST_ICO_QNT];
GtkWidget *vnd_box[VND_ICO_QNT];
GtkWidget *cmp_box[CMP_ICO_QNT];
GtkWidget *rel_box[REL_ICO_QNT];

GtkWidget **principall;
GtkWidget **cadastrosl;
GtkWidget **comprasl;
GtkWidget **faturamentol;
GtkWidget **estoquel;
GtkWidget **financeirol;
GtkWidget **relatoriosl;


