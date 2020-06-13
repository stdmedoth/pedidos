#define SERVER "localhost"
#define USER "petitto"
#define PASS "1234"
#define DATABASE "erp"
#ifdef WIN32
#define CHROME_PATH     ""
#define FIREFOX_PATH    ""
#define TEMA_PATH	  "/gtk/share/themes/"
#define CT_CONF_PATH  "/petitto/files/criticas.conf"
#define ORC_PATH      "/petitto/files/impressao/"
#define IMG_REC       "/petitto/files/opcoes_padrao/recarregar.png"
#define IMG_MONEY     "/petitto/files/opcoes_padrao/cash-outline.png"
#define IMG_OK        "/petitto/files/opcoes_padrao/ok.png"
#define IMG_IMP       "/petitto/files/opcoes_padrao/impressao.png"
#define IMG_GERA      "/petitto/files/opcoes_padrao/geracao.png"
#define IMG_PESQ      "/petitto/files/opcoes_padrao/pesquisar.png"
#define IMG_PROCR     "/petitto/files/opcoes_padrao/procurar.png"
#define IMG_EXCLUI    "/petitto/files/opcoes_padrao/excluir.png"
#define IMG_ALTER     "/petitto/files/opcoes_padrao/alterar.png"
#define IMG_CANCEL    "/petitto/files/opcoes_padrao/cancelar.png"
#define IMG_MAIS      "/petitto/files/opcoes_padrao/mais.png"
#define IMG_MENOS     "/petitto/files/opcoes_padrao/menos.png"
#define IMG_REC       "/petitto/files/opcoes_padrao/recarregar.png"
#define LOGGER        "/petitto/files/logger.log"
#define ICO           "/petitto/files/ico.ico"
#define MSG_PRINC     "/petitto/files/msg"
#define LOGO          "/petitto/files/logo.png"
#define INIT_IMAGE    "/petitto/files/init.jpg"
#define BACKUP        "/petitto/files/backup"
#define DESKTOP       "/petitto/files/desktop.png"
#define DESKTOP1      "/petitto/files/desktop/desktop1.png"
#define DESKTOP2      "/petitto/files/desktop/desktop2.png"
#define DESKTOP3      "/petitto/files/desktop/desktop3.png"
#define DESKTOP4      "/petitto/files/desktop/desktop4.png"
#define DESKTOP5      "/petitto/files/desktop/desktop5.png"
#define DESKTOP6      "/petitto/files/desktop/desktop6.png"
#define THUMBDESKTOP1 "/petitto/files/thumbs/thumbdesktop1.png"
#define THUMBDESKTOP2 "/petitto/files/thumbs/thumbdesktop2.png"
#define THUMBDESKTOP3 "/petitto/files/thumbs/thumbdesktop3.png"
#define THUMBDESKTOP4 "/petitto/files/thumbs/thumbdesktop4.png"
#define THUMBDESKTOP5 "/petitto/files/thumbs/thumbdesktop5.png"
#define THUMBDESKTOP6 "/petitto/files/thumbs/thumbdesktop6.png"
#define OPER_DESKTOP  "/petitto/files/desktop/oper.png"
#define DESKTOP_STYLE "/petitto/files/desktop/style.css"
#define BANNER        "/petitto/files/princ_imgs/banner.png"
#define BARRA_IMG     "/petitto/files/princ_imgs/barra.png"
#define BOTAO_MENU    "/petitto/files/princ_imgs/botao_menu.png"
#define ORC_IMG		  "/petitto/files/icones_opc/orcamentos.png"
#define PED_IMG		  "/petitto/files/icones_opc/pedidos.png"
#define GRP_IMG       "/petitto/files/icones_opc/grupos.png"
#define PROD_IMG      "/petitto/files/icones_opc/produtos.png"
#define TERC_IMG      "/petitto/files/icones_opc/terceiros.png"
#define REL_IMG       "/petitto/files/icones_opc/cad_relat.png"
#define ADD_SALDO     "/petitto/files/icones_opc/add_saldo.png"
#define REM_SALDO     "/petitto/files/icones_opc/rem_saldo.png"
#define ESTO_IMG      "/petitto/files/icones_opc/estoques.png"
#define SALD_IMG      "/petitto/files/icones_opc/saldo.png"
#define OPR_IMG       "/petitto/files/icones_opc/operadores.png"
#define TRS_IMG       "/petitto/files/icones_opc/transacoes.png"
#define SOL_IMG       "/petitto/files/icones_opc/solicitacoes.png"
#define PRC_IMG       "/petitto/files/icones_opc/preco.png"
#define COT_IMG       "/petitto/files/icones_opc/cotacao.png"
#define ORD_IMG       "/petitto/files/icones_opc/ordem_cmp.png"
#define ENT_IMG       "/petitto/files/icones_opc/entradas.png"
#define LMB_IMG       "/petitto/files/icones_opc/lembrete.png"
#define UND_IMG       "/petitto/files/icones_opc/unidade.png"
#define FATOR_IMG     "/petitto/files/icones_opc/fatores.png"
#define PRMT_IMG      "/petitto/files/icones_opc/parametros.png"
#define VINC_IMG      "/petitto/files/icones_opc/vinculos.png"
#define REL_PROD_IMG  "/petitto/files/icones_opc/relatorio_prod.png"
#define REL_TER_IMG   "/petitto/files/icones_opc/relatorio_ter.png"
#define REL_SLD_IMG   "/petitto/files/icones_opc/relatorio_est.png"
#define EXIT_IMG      "/petitto/files/icones_opc/sair.png"
#define PDF_GEN       "/petitto/files/impressao/pdf.exe"
#define IMG_ENVIA     "/petitto/files/opcoes_padrao/enviar.png"
#define ICON_PATH     "/petitto/files/opcoes_padrao/icones/"
#define TER_RELAT_FILE    "/petitto/files/impressao/relatorios/terceiros/"
#define PROD_RELAT_FILE    "/petitto/files/impressao/relatorios/produtos/"
#define VND_RELAT_FILE    "/petitto/files/impressao/relatorios/vendas/"
#define EST_RELAT_FILE    "/petitto/files/impressao/relatorios/estoque/"
#define MOV_RELAT_FILE    "/petitto/files/impressao/relatorios/movimentos/"
#define IMG_IMP_LOGO      "/petitto/files/impressao/imgs/logo_livro_texto.png"
#endif

#ifdef __linux__
#define TEMA_PATH	  "/usr/share/themes/"
#define PDF_GEN       "/usr/bin/wkhtmltopdf"
#define CHROME_PATH   "/bin/chromium"
#define FIREFOX_PATH  "/bin/firefox"
#define CT_CONF_PATH  "/usr/share/petitto/files/criticas.conf"
#define ORC_PATH 	  "/usr/share/petitto/files/impressao/"
#define DESKTOP_STYLE "/usr/share/petitto/files/desktop/style.css"
#define DESKTOP       "/usr/share/petitto/files/desktop.png"
#define DESKTOP1      "/usr/share/petitto/files/desktop/desktop1.png"
#define DESKTOP2      "/usr/share/petitto/files/desktop/desktop2.png"
#define DESKTOP3      "/usr/share/petitto/files/desktop/desktop3.png"
#define DESKTOP4      "/usr/share/petitto/files/desktop/desktop4.png"
#define DESKTOP5      "/usr/share/petitto/files/desktop/desktop5.png"
#define DESKTOP6      "/usr/share/petitto/files/desktop/desktop6.png"
#define OPER_DESKTOP  "/usr/share/petitto/files/desktop/oper.png"
#define THUMBDESKTOP1 "/usr/share/petitto/files/thumbs/thumbdesktop1.png"
#define THUMBDESKTOP2 "/usr/share/petitto/files/thumbs/thumbdesktop2.png"
#define THUMBDESKTOP3 "/usr/share/petitto/files/thumbs/thumbdesktop3.png"
#define THUMBDESKTOP4 "/usr/share/petitto/files/thumbs/thumbdesktop4.png"
#define THUMBDESKTOP5 "/usr/share/petitto/files/thumbs/thumbdesktop5.png"
#define THUMBDESKTOP6 "/usr/share/petitto/files/thumbs/thumbdesktop6.png"
#define ICO           "/usr/share/petitto/files/ico.ico"
#define INIT_IMAGE    "/usr/share/petitto/files/init.jpg"
#define LOGGER        "/usr/share/petitto/files/logger"
#define BACKUP        "/usr/share/petitto/files/backup"
#define BANNER        "/usr/share/petitto/files/princ_imgs/banner.png"
#define MSG_PRINC     "/usr/share/petitto/files/msg"
#define BARRA_IMG     "/usr/share/petitto/files/princ_imgs/barra.png"
#define BOTAO_MENU    "/usr/share/petitto/files/princ_imgs/botao_menu.png"
#define FATOR_IMG     "/usr/share/petitto/files/icones_opc/fatores.png"
#define PRMT_IMG      "/usr/share/petitto/files/icones_opc/parametros.png"
#define EXIT_IMG      "/usr/share/petitto/files/icones_opc/sair.png"
#define ORC_IMG		  "/usr/share/petitto/files/icones_opc/orcamentos.png"
#define PED_IMG		  "/usr/share/petitto/files/icones_opc/pedidos.png"
#define PROD_IMG      "/usr/share/petitto/files/icones_opc/produtos.png"
#define GRP_IMG       "/usr/share/petitto/files/icones_opc/grupos.png"
#define TERC_IMG      "/usr/share/petitto/files/icones_opc/terceiros.png"
#define ESTO_IMG      "/usr/share/petitto/files/icones_opc/estoques.png"
#define REL_IMG       "/usr/share/petitto/files/icones_opc/cad_relat.png"
#define SALD_IMG      "/usr/share/petitto/files/icones_opc/saldo.png"
#define OPR_IMG       "/usr/share/petitto/files/icones_opc/operadores.png"
#define TRS_IMG       "/usr/share/petitto/files/icones_opc/transacoes.png"
#define SOL_IMG       "/usr/share/petitto/files/icones_opc/solicitacoes.png"
#define ADD_SALDO     "/usr/share/petitto/files/icones_opc/add_saldo.png"
#define REM_SALDO     "/usr/share/petitto/files/icones_opc/rem_saldo.png"
#define REL_PROD_IMG  "/usr/share/petitto/files/icones_opc/relatorio_prod.png"
#define REL_TER_IMG   "/usr/share/petitto/files/icones_opc/relatorio_ter.png"
#define REL_SLD_IMG   "/usr/share/petitto/files/icones_opc/relatorio_est.png"
#define COT_IMG       "/usr/share/petitto/files/icones_opc/cotacao.png"
#define ORD_IMG       "/usr/share/petitto/files/icones_opc/ordem_cmp.png"
#define ENT_IMG       "/usr/share/petitto/files/icones_opc/entradas.png"
#define LMB_IMG       "/usr/share/petitto/files/icones_opc/lembrete.png"
#define UND_IMG       "/usr/share/petitto/files/icones_opc/unidade.png"
#define VINC_IMG      "/usr/share/petitto/files/icones_opc/vinculos.png"
#define IMG_OK        "/usr/share/petitto/files/opcoes_padrao/ok.png"
#define IMG_REC       "/usr/share/petitto/files/opcoes_padrao/recarregar.png"
#define IMG_ENVIA     "/usr/share/petitto/files/opcoes_padrao/enviar.png"
#define IMG_GERA      "/usr/share/petitto/files/opcoes_padrao/geracao.png"
#define IMG_PROCR     "/usr/share/petitto/files/opcoes_padrao/procurar.png"
#define IMG_IMP       "/usr/share/petitto/files/opcoes_padrao/impressao.png"
#define IMG_ALTER     "/usr/share/petitto/files/opcoes_padrao/alterar.png"
#define IMG_CANCEL    "/usr/share/petitto/files/opcoes_padrao/cancelar.png"
#define IMG_PESQ      "/usr/share/petitto/files/opcoes_padrao/pesquisar.png"
#define IMG_EXCLUI    "/usr/share/petitto/files/opcoes_padrao/excluir.png"
#define IMG_MAIS      "/usr/share/petitto/files/opcoes_padrao/mais.png"
#define IMG_MENOS     "/usr/share/petitto/files/opcoes_padrao/menos.png"
#define IMG_MONEY     "/usr/share/petitto/files/opcoes_padrao/cash-outline.png"
#define ICON_PATH     "/usr/share/petitto/files/opcoes_padrao/icones/"
#define TER_RELAT_FILE  "/usr/share/petitto/files/impressao/relatorios/terceiros/"
#define PROD_RELAT_FILE "/usr/share/petitto/files/impressao/relatorios/produtos/"
#define VND_RELAT_FILE  "/usr/share/petitto/files/impressao/relatorios/vendas/"
#define EST_RELAT_FILE  "/usr/share/petitto/files/impressao/relatorios/estoque/"
#define MOV_RELAT_FILE  "/usr/share/petitto/files/impressao/relatorios/movimentos/"
#define IMG_IMP_LOGO  "/usr/share/petitto/files/impressao/imgs/logo_livro_texto.png"
#endif

#define CSS_ORC       "orcamento.css"
#define IMG_IMP_CLI   "imgs/cliente.png"
#define IMG_IMP_PROD  "imgs/produto.png"
#define IMG_IMP_LOCAL "imgs/localidade.png"
#define IMG_IMP_EMAIL "imgs/simb_email.png"
#define IMG_IMP_TEL   "imgs/telefone.png"
#define IMG_IMP_CEL   "imgs/celular.png"
#define IMG_IMP_QNT   "imgs/quantidade.png"

#define MAX_TEMA_LEN 50
#define MAX_TEMA_QNT 50
#define MAX_PATH_LEN 500
#define MAX_EMAIL_LEN 100
#define MAX_OBS_LEN 500
#define MAX_PROD 400
#define MAX_QUERY_ELM_LEN 300
#define MAX_QUERY_LEN (MAX_QUERY_ELM_LEN*50)
#define CONECT_QNT 1
#define CODE_LEN 10
#define CNPJ_N_LEN 14
#define CNPJ_S_LEN 18
#define MAX_INSC_LEN 20
#define CPF_N_LEN 11
#define CPF_S_LEN 14
#define INSERT_QUERY 96
#define VLR_MAX_LEN 15
#define TERC_QNT  10000
#define PROD_QNT  10000
#define ROWS_QNT 30
#define MAX_CODE_LEN 10
#define MAX_NAME_LEN 400
#define MAX_RAZ_LEN 400
#define MAX_PRECO_LEN 15
#define MAX_UND_LEN 10
#define MAX_GRP_LEN 20
#define MAX_MRC_LEN 20
#define MAX_FOR_LEN 100
#define MAX_OBS_LEN 500
#define MAX_SIGLA 10
#define MAX_GRP 20
#define MAX_CEP_LEN 10
#define CEP_LEN 8
#define MAX_ADR_LEN 300
#define MAX_CID_LEN 50
#define MAX_EST_LEN 50
#define MAX_LOGR_LEN 300
#define MAX_URI_LEN 300
#define MAX_PARAM_LEN 20
#define MAX_TIPO_LEN 20
#define MAX_LINHAS (sizeof(GtkBox*)*ROWS_QNT)*TERC_QNT
#define ENTRADA 300
#define MARGEM_D 10
#define WALLPAPERS_QNT 6
#define RAZ_ROW_POS 1
#define END_ROW_POS 7
#define TEL_ROW_POS 9
#define CEL_ROW_POS 11
#define EMAIL_ROW_POS 13
#define MAX_OPER_LEN 30
#define MAX_SEN_LEN 30
#define MAX_DATE_LEN 8
#define MAX_FETCH_ROW 3000
#define MAX_SUBGRUPO 20
#define MAX_EST_NOME 20
#define MAX_RELAT_NOME 30
#define MAX_CAMPO_NOME 30
#define MAX_RELAT_CAMPOS 8

GtkWidget *acao_atual,*acao_atual2;
GtkEntry *pesquisa_global_alvo;
GtkIconTheme *icone;
static int inicializando=0;
