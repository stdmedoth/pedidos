static void criar_janela_princ();

int default_user_code = 1;
GtkWidget  *janela_principal;
GtkWidget *imagem_desktop;

GtkWidget *superior, *superior_1, *superior_2;
GtkWidget *inferior, *inferior_1, *inferior_2;
GtkWidget *area_de_trabalho;
GtkWidget *barra;

GtkWidget *imagem_barra,*layout_barra;


int monitor_width=0, monitor_heigth=0;
int desktop_width=0, desktop_heigth=0;

int desktop();

GtkApplication *app;

GtkWidget  *sessao_criacao_label, *sessao_expiracao_label, *sessao_inatividade_label;
GtkWidget  *fixed_razao, *fixed_endereco, *fixed_cnpj;
GtkWidget  *razao,*endereco,*cnpj, *caixa_infos;
GtkWidget *janela_inicializacao;
