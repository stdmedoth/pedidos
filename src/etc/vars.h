#define SERVER "localhost"
#define USER "petitto"
#define PASS "1234"
#define DATABASE "erp"
#ifdef WIN32
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

#define PROD_CAD_QUERY "insert into produtos(nome,preco,peso,unidade,fornecedor,grupo,marca,observacoes) values('%s',%s,%s,(select code from unidades where sigla = '%s'),%s,'%s','%s','%s');"
#define ARGS_PROD_CAD_QUERY nomes_prod, precos_prod, pesos_prod, unidades_prod, fornecedores_prod, grupos_prod, marcas_prod, observacoes_prod
#define PROD_UPD_QUERY "update produtos set nome = '%s', preco = %s, peso = '%s', unidade = %s, fornecedor = '%s', grupo = '%s', marca = '%s', observacoes = '%s'"

