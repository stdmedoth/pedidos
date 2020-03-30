#define SERVER "localhost"
#define USER "petitto"
#define PASS "1234"
#define DATABASE "erp"
#ifdef WIN32
#define IMG_MONEY     "/petitto/files/opcoes_padrao/cash-outline.png"
#define IMG_OK        "/petitto/files/opcoes_padrao/ok.png"
#define IMG_CANCEL    "/petitto/files/opcoes_padrao/cancelar.png"
#define IMG_MAIS      "/petitto/files/opcoes_padrao/mais.png"
#define LOGGER        "/petitto/files/logger.log"
#define ICO           "/petitto/files/ico.ico"
#define MSG_PRINC     "/petitto/files/msg"
#define LOGO          "/petitto/files/logo.png"
#define INIT_IMAGE    "/petitto/files/init.jpg"
#define BACKUP        "/petitto/files/backup"
#define DESKTOP       "/petitto/files/desktop.png"
#define DESKTOP_STYLE "/petitto/files/desktop/style.css"
#define BANNER        "/petitto/files/princ_imgs/banner.png"
#define BARRA_IMG     "/petitto/files/princ_imgs/barra.png"
#define BOTAO_MENU    "/petitto/files/princ_imgs/botao_menu.png"  
#define PROD_IMG      "/petitto/files/icones_opc/produtos.png"
#define TERC_IMG      "/petitto/files/icones_opc/terceiros.png"  
#define ESTO_IMG      "/petitto/files/icones_opc/estoques.png"  
#define OPR_IMG       "/petitto/files/icones_opc/operadores.png"  
#define TRS_IMG       "/petitto/files/icones_opc/transacoes.png"  
#define SOL_IMG       "/petitto/files/icones_opc/solicitacoes.png"  
#define COT_IMG       "/petitto/files/icones_opc/cotacao.png"  
#define ORD_IMG       "/petitto/files/icones_opc/ordem_cmp.png"  
#define ENT_IMG       "/petitto/files/icones_opc/entradas.png"  
#define LMB_IMG       "/petitto/files/icones_opc/lembrete.png"  
#define UND_IMG       "/petitto/files/icones_opc/unidade.png"  
#endif
#ifdef __linux__
#define DESKTOP_STYLE "/usr/share/petitto/files/desktop/style.css"
#define DESKTOP       "/usr/share/petitto/files/desktop.png"
#define ICO           "/usr/share/petitto/files/ico.ico"
#define INIT_IMAGE    "/usr/share/petitto/files/init.jpg"
#define LOGGER        "/usr/share/petitto/files/logger"
#define BACKUP        "/usr/share/petitto/files/backup"
#define BANNER        "/usr/share/petitto/files/princ_imgs/banner.png"
#define MSG_PRINC     "/usr/share/petitto/files/msg"
#define BARRA_IMG     "/usr/share/petitto/files/princ_imgs/barra.png"
#define BOTAO_MENU    "/usr/share/petitto/files/princ_imgs/botao_menu.png"  
#define PROD_IMG      "/usr/share/petitto/files/icones_opc/produtos.png"
#define TERC_IMG      "/usr/share/petitto/files/icones_opc/terceiros.png"  
#define ESTO_IMG      "/usr/share/petitto/files/icones_opc/estoques.png"  
#define OPR_IMG       "/usr/share/petitto/files/icones_opc/operadores.png"  
#define TRS_IMG       "/usr/share/petitto/files/icones_opc/transacoes.png"  
#define SOL_IMG       "/usr/share/petitto/files/icones_opc/solicitacoes.png"  
#define COT_IMG       "/usr/share/petitto/files/icones_opc/cotacao.png"  
#define ORD_IMG       "/usr/share/petitto/files/icones_opc/ordem_cmp.png"  
#define ENT_IMG       "/usr/share/petitto/files/icones_opc/entradas.png"  
#define LMB_IMG       "/usr/share/petitto/files/icones_opc/lembrete.png"  
#define UND_IMG       "/usr/share/petitto/files/icones_opc/unidade.png"  
#define IMG_OK        "/usr/share/petitto/files/opcoes_padrao/ok.png"
#define IMG_CANCEL    "/usr/share/petitto/files/opcoes_padrao/cancelar.png"
#define IMG_MAIS      "/usr/share/petitto/files/opcoes_padrao/mais.png"
#define IMG_MONEY      "/usr/share/petitto/files/opcoes_padrao/cash-outline.png"
#endif
#define MAX_EMAIL_LEN 100
#define MAX_OBS_LEN 500
#define CAMPOS_QNT 16
#define MAX_PROD 100
#define MAX_QUERY_LEN 1000
#define CONECT_QNT 1
#define CODE_LEN 10
#define CNPJ_N_LEN 14
#define CNPJ_S_LEN 18
#define CPF_N_LEN 11
#define CPF_S_LEN 14
#define INSERT_QUERY 96
#define VLR_MAX_LEN 15
#define TERC_QNT  10000
#define PROD_QNT  10000
#define ROWS_QNT 16
#define MAX_PRECO_LEN 10
#define MAX_CODE_LEN 10
#define MAX_NAME_LEN 100
#define MAX_RAZ_LEN 100	
#define MAX_PRECO_LEN 10
#define MAX_UND_LEN 10
#define MAX_GRP_LEN 20
#define MAX_MRC_LEN 20
#define MAX_FOR_LEN 100
#define MAX_OBS_LEN 500
#define MAX_SIGLA 10
#define MAX_GRP 20
#define MAX_LINHAS (sizeof(GtkBox*)*ROWS_QNT)*TERC_QNT
#define ENTRADA 200
#define MARGEM_D 10

char **vet_codigos;
int cont=0,pos=0;
int alterando=0;
// **separadoresh
GtkWidget *lista_ter;

//terceiros
int codigos_ter_prod[MAX_PROD];
int *codigo_preco;
GtkWidget *lista_prod_label;
GtkWidget **produto_label,
**preco_entry, 
**precos_caixas, 
**atualizar_preco, 
**remover_preco,
*precos_scroll_caixa,
*precos_scroll_window,
**imagem_ok,
**imagem_cancel,
**imagem_dinheiro,
**juncao_preco_img;

int tipo_doc;
GtkWidget **evento;
GtkWidget **separadoresv[30];
GtkWidget *doc_combo;

GtkWidget *code_ter_field, 
*doc_ter_field, *name_ter_field, 
*address_ter_field, *cep_ter_field, 
*type_ter_field,
*telefone_ter_field, *contatot_ter_field, 
*celular_ter_field, *contatoc_ter_field, 
*email_ter_field, *contatoe_ter_field, 
*observacoes_ter_field;

GtkWidget *janela;
GtkWidget *acao_atual,*acao_atual2;
GtkWidget *win_tipo_ter;

//lista terceiros
GtkWidget *colunas;
GtkWidget **codigo,**nome,**doc,
**tipodoc,**type,**address,
**cep,**telefone,**contatot,
**celular,**contatoc,**email,
**contatoe,**_obs;

GtkWidget *lista_scroll_caixah, 
*lista_scroll_caixav, *lista_scroll_windowv, 
*lista_scroll_windowh, *lista_ter_label;

char **vet_codigos;
MYSQL_RES *vetor;
MYSQL_ROW campos;
GtkWidget *filas;

//produtos
GtkWidget *codigo_prod_field, *nome_prod_field, 
*preco_prod_field,  *peso_prod_field, *unidade_prod_field,
*fornecedor_prod_field, *grupo_prod_field, 
*marca_prod_field, *observacao_prod_field;
GtkWidget *code_prod_label,  *nome_prod_label, 
*preco_prod_label, *peso_prod_label , *unidade_prod_label,
*fornecedor_prod_label, *grupo_prod_label, 
*marca_prod_label,  *observacao_prod_label;
GtkWidget *botao_mais;
GtkWidget *imagem_mais;
GtkWidget *campo_nome_fornecedor,
*campo_nome_grupo;

int *codigo_preco;

//lista terceiros
GtkWidget **preco,**peso,**unidade,**fornecedor,**grupo,**marca,**observacoes;
GtkWidget *lista_scroll_caixah, *lista_scroll_caixav, *lista_scroll_windowv, *lista_scroll_windowh, *lista_ter_label;
GtkWidget *lista_prod;
GtkWidget *pesquisa;
GtkWidget *code_label, *doc_label, *name_label, *address_label, *cep_ter_label,*type_label,
*telefone_label, *contatot_label, *celular_label, *contatoc_label, 
*email_label, *contatoe_label, *observacoes_label;

#define PROD_CAD_QUERY "insert into produtos(nome,preco,peso,unidade,fornecedor,grupo,marca,observacoes) values( '%s', %s, %s, (select code from unidades where sigla = '%s'), %s, %s, '%s', '%s');"
#define ARGS_PROD_CAD_QUERY nomes_prod, precos_prod, pesos_prod, unidades_prod, fornecedores_prod, grupos_prod, marcas_prod, observacoes_prod
#define PROD_UPD_QUERY "update produtos set nome = '%s', preco = %s, peso = '%s', unidade = (select code from unidades where sigla = '%s'), fornecedor = '%s', grupo = '%s', marca = '%s', observacoes = '%s'"

