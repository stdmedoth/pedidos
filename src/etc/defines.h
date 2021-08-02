#ifndef PEDIDOS_DEFINES
#define PEDIDOS_DEFINES
#define APP_NAME "pedidos"

#define PEDIDOS_DEVELOP_ENV
//#define PEDIDOS_PRODUCTION_ENV

#ifdef WIN32
#define TEMA_PATH	   "../share/themes/"
#define PDF_GEN            APP_DIRNAME "/files/impressao/wkhtmltopdf.exe"
#define COPY_PROG          APP_DIRNAME "/files/impressao/cp.exe"
#define APP_BINS_DIR       APP_DIRNAME "/bin"
#define APP_DIRNAME  "C:/" APP_NAME
#define MIGRATE_BIN_NAME  "/migrate.exe"
#endif

#ifdef __linux__
#define TEMA_PATH	        "/usr/share/themes/"
#define PDF_GEN           "/usr/bin/wkhtmltopdf"
#define COPY_PROG         "/usr/bin/cp"
//#define APP_BINS_DIR    "/usr/bin" //real
#define APP_BINS_DIR      APP_DIRNAME "/bin"
#define APP_DIRNAME       "/usr/share/" APP_NAME
#define MIGRATE_BIN_NAME  "/migrate"
#endif


#ifdef PEDIDOS_DEVELOP_ENV
#define MIGRATE_FOLDER     "data/sql_scripts/migrates"
#endif

#ifdef PEDIDOS_PRODUCTION_ENV
#define MIGRATE_FOLDER     APP_DIRNAME "/files/sql_scripts/migrates"
#endif

#define MIGRATE_BIN        APP_BINS_DIR MIGRATE_BIN_NAME

#define BKP_PTH_CACHE      APP_DIRNAME "/files/cache/backup_path"
#define EXP_PTH_CACHE      APP_DIRNAME "/files/cache/backup_path"

#define APP_TRACELOG       APP_DIRNAME "/files/trace_log.log"
#define LOADING_GIF        APP_DIRNAME "/files/gen_imgs/carregando.gif"
#define SERVER_CONF        APP_DIRNAME "/files/server.xml"
#define ORC_PATH           APP_DIRNAME "/files/impressao/orcs/"
#define COT_RES_PATH       APP_DIRNAME "/files/impressao/cots"
#define IMG_REC            APP_DIRNAME "/files/opcoes_padrao/recarregar.png"
#define IMG_MONEY          APP_DIRNAME "/files/opcoes_padrao/cash-outline.png"
#define IMG_OK             APP_DIRNAME "/files/opcoes_padrao/ok.png"
#define IMG_IMP            APP_DIRNAME "/files/opcoes_padrao/impressao.png"
#define IMG_GERA           APP_DIRNAME "/files/opcoes_padrao/geracao.png"
#define IMG_PESQ           APP_DIRNAME "/files/opcoes_padrao/pesquisar.png"
#define IMG_PROCR          APP_DIRNAME "/files/opcoes_padrao/procurar.png"
#define IMG_EXCLUI         APP_DIRNAME "/files/opcoes_padrao/excluir.png"
#define IMG_ALTER          APP_DIRNAME "/files/opcoes_padrao/alterar.png"
#define IMG_CANCEL         APP_DIRNAME "/files/opcoes_padrao/cancelar.png"
#define IMG_MAIS           APP_DIRNAME "/files/opcoes_padrao/mais.png"
#define IMG_MENOS          APP_DIRNAME "/files/opcoes_padrao/menos.png"
#define IMG_REC            APP_DIRNAME "/files/opcoes_padrao/recarregar.png"
#define LOGGER             APP_DIRNAME "/files/logger.log"
#define ICO                APP_DIRNAME "/files/ico.ico"
#define MSG_PRINC          APP_DIRNAME "/files/msg"
#define LOGO               APP_DIRNAME "/files/logo.png"
#define LOGO_PEQUENA       APP_DIRNAME "/files/logo_pequena.png"
#define LOGO_MEDIA         APP_DIRNAME "/files/logo_media.png"
#define LOGO_PDF           APP_DIRNAME "/files/logo_pdf.png"
#define BACKUP             APP_DIRNAME "/files/backup"
#define DESKTOP            APP_DIRNAME "/files/desktop.png"
#define DESKTOP1           APP_DIRNAME "/files/desktop/desktop1.png"
#define DESKTOP2           APP_DIRNAME "/files/desktop/desktop2.png"
#define DESKTOP3           APP_DIRNAME "/files/desktop/desktop3.png"
#define DESKTOP4           APP_DIRNAME "/files/desktop/desktop4.png"
#define DESKTOP5           APP_DIRNAME "/files/desktop/desktop5.png"
#define DESKTOP6           APP_DIRNAME "/files/desktop/desktop6.png"
#define THUMBDESKTOP1      APP_DIRNAME "/files/thumbs/thumbdesktop1.png"
#define THUMBDESKTOP2      APP_DIRNAME "/files/thumbs/thumbdesktop2.png"
#define THUMBDESKTOP3      APP_DIRNAME "/files/thumbs/thumbdesktop3.png"
#define THUMBDESKTOP4      APP_DIRNAME "/files/thumbs/thumbdesktop4.png"
#define THUMBDESKTOP5      APP_DIRNAME "/files/thumbs/thumbdesktop5.png"
#define THUMBDESKTOP6      APP_DIRNAME "/files/thumbs/thumbdesktop6.png"
#define GOD_DESKTOP_IMG    APP_DIRNAME "/files/desktop/god.png"
#define OPER_DESKTOP_IMG   APP_DIRNAME "/files/desktop/oper.png"
#define DESKTOP_STYLE      APP_DIRNAME "/files/desktop/style.css"
#define MAIN_STYLE         APP_DIRNAME "/files/assets/main.css"
#define KANBAN_STYLE       APP_DIRNAME "/files/assets/kanban.css"
#define PDV_SHORTCUTS      APP_DIRNAME "/files/pdv/atalhos.css"
#define PDV_STYLE          APP_DIRNAME "/files/assets/pdv.css"
#define LOGO_HEADER        APP_DIRNAME "/files/assets/logo_header.png"
#define PDV_LOGO           APP_DIRNAME "/files/assets/pdv_logo.png"
#define INI_LOGO           APP_DIRNAME "/files/assets/logo.png"
#define BANNER             APP_DIRNAME "/files/princ_imgs/banner.png"
#define BARRA_IMG          APP_DIRNAME "/files/princ_imgs/barra.png"
#define BOTAO_MENU         APP_DIRNAME "/files/princ_imgs/botao_menu.png"
#define ORC_IMG		         APP_DIRNAME "/files/icones_opc/orcamentos.png"
#define PED_IMG		         APP_DIRNAME "/files/icones_opc/pedidos.png"
#define GRP_IMG            APP_DIRNAME "/files/icones_opc/grupos.png"
#define PROD_IMG           APP_DIRNAME "/files/icones_opc/produtos.png"
#define TERC_IMG           APP_DIRNAME "/files/icones_opc/terceiros.png"
#define REL_IMG            APP_DIRNAME "/files/icones_opc/cad_relat.png"
#define ADD_SALDO          APP_DIRNAME "/files/icones_opc/add_saldo.png"
#define REM_SALDO          APP_DIRNAME "/files/icones_opc/rem_saldo.png"
#define ESTO_IMG           APP_DIRNAME "/files/icones_opc/estoques.png"
#define SALD_IMG           APP_DIRNAME "/files/icones_opc/saldo.png"
#define OPR_IMG            APP_DIRNAME "/files/icones_opc/operadores.png"
#define CX_IMG             APP_DIRNAME "/files/icones_opc/caixa.png"
#define CX_BAR_IMG         APP_DIRNAME "/files/icones_opc/caixa2.png"
#define TRS_IMG            APP_DIRNAME "/files/icones_opc/transacoes.png"
#define SOL_IMG            APP_DIRNAME "/files/icones_opc/solicitacoes.png"
#define PRC_IMG            APP_DIRNAME "/files/icones_opc/preco.png"
#define COT_IMG            APP_DIRNAME "/files/icones_opc/cotacao.png"
#define ORD_IMG            APP_DIRNAME "/files/icones_opc/ordem_cmp.png"
#define ENT_IMG            APP_DIRNAME "/files/icones_opc/entradas.png"
#define LMB_IMG            APP_DIRNAME "/files/icones_opc/lembrete.png"
#define UND_IMG            APP_DIRNAME "/files/icones_opc/unidade.png"
#define PAG_IMG            APP_DIRNAME "/files/icones_opc/datas.png"
#define CHEQ_IMG           APP_DIRNAME "/files/icones_opc/cheque.png"
#define ANLS_MKT_IMG       APP_DIRNAME "/files/icones_opc/analise_marketing.png"
#define MODELMAIL_IMG      APP_DIRNAME "/files/icones_opc/modelos_email.png"
#define MAILILIST_IMG      APP_DIRNAME "/files/icones_opc/mailing_list.png"
#define ENVMAIL_IMG        APP_DIRNAME "/files/icones_opc/envia_emails.png"
#define REC_TIT_IMG        APP_DIRNAME "/files/icones_opc/descendente.png"
#define PAG_TIT_IMG        APP_DIRNAME "/files/icones_opc/ascendente.png"
#define BX_PAG_TIT_IMG     APP_DIRNAME "/files/icones_opc/baixas_pagar.png"
#define BX_REC_TIT_IMG     APP_DIRNAME "/files/icones_opc/baixas_receber.png"
#define FATOR_IMG          APP_DIRNAME "/files/icones_opc/fatores.png"
#define PRMT_IMG           APP_DIRNAME "/files/icones_opc/parametros.png"
#define CAD_EMP_IMG        APP_DIRNAME "/files/icones_opc/company.png"
#define CAD_CONTR_IMG      APP_DIRNAME "/files/icones_opc/contratos.png"
#define ATL_PROD_IMG       APP_DIRNAME "/files/icones_opc/atualiza_prod_nomes.png"
#define VINC_IMG           APP_DIRNAME "/files/icones_opc/vinculos.png"
#define BANCOS_IMG         APP_DIRNAME "/files/icones_opc/bancos.png"
#define TRSP_IMG           APP_DIRNAME "/files/icones_opc/transportes.png"
#define CAD_CEP_IMG        APP_DIRNAME "/files/icones_opc/search_cep.png"
#define CAD_LOGS_IMG       APP_DIRNAME "/files/icones_opc/logs.png"
#define REL_PLANL_IMG      APP_DIRNAME "/files/icones_opc/planilhas.png"
#define REL_PROD_IMG       APP_DIRNAME "/files/icones_opc/relatorio_prod.png"
#define REL_PLANL_PROD_IMG APP_DIRNAME "/files/icones_opc/planilha_prods.png"
#define REL_PLANL_FINP_IMG APP_DIRNAME "/files/icones_opc/planilha_pagar.png"
#define REL_PLANL_FLUX_IMG APP_DIRNAME "/files/icones_opc/planilha_fluxo.png"
#define REL_PLANL_FINR_IMG APP_DIRNAME "/files/icones_opc/planilha_rec.png"
#define REL_FIX_PROD_IMG   APP_DIRNAME "/files/icones_opc/relatorio_fixos_produtos.png"
#define REL_FIX_TER_IMG    APP_DIRNAME "/files/icones_opc/relatorio_fixos_terceiros.png"
#define REL_FIX_VND_IMG    APP_DIRNAME "/files/icones_opc/relatorio_fixos_vendas.png"
#define REL_FIX_EST_IMG    APP_DIRNAME "/files/icones_opc/relatorio_fixos_movestoque.png"
#define REL_PLANL_MOV_IMG  APP_DIRNAME "/files/icones_opc/planilha_movimentos.png"
#define REL_TER_IMG        APP_DIRNAME "/files/icones_opc/relatorio_ter.png"
#define REL_PLANL_TER_IMG  APP_DIRNAME "/files/icones_opc/planilha_terceiros.png"
#define REL_SLD_IMG        APP_DIRNAME "/files/icones_opc/relatorio_est.png"
#define REL_ORC_PROD_IMG   APP_DIRNAME "/files/icones_opc/relatorio_orc_prod.png"
#define REL_FIX_VND_PATH   APP_DIRNAME "/files/impressao/relatorios/fixos/vendas"
#define REL_FIX_MOV_PATH   APP_DIRNAME "/files/impressao/relatorios/fixos/movimentos"
#define REL_FIX_FIN_PATH   APP_DIRNAME "/files/impressao/relatorios/fixos/financeiros/"
#define PAG_CONT_FIX       APP_DIRNAME "/files/impressao/conta_fixa.html"
#define ORC_TXTPOS         APP_DIRNAME "/files/impressao/orc_text_positions.xml"
#define ORD_CMP_PDF_FILE   APP_DIRNAME "/files/impressao/ord_cmp.pdf"
#define ORC_PDF_FILE       APP_DIRNAME "/files/impressao/ord_cmp.pdf"
#define ORC_MODEL          APP_DIRNAME "/files/impressao/modelo-de-orçamento.png"
#define REL_FIX_FINREC_IMG APP_DIRNAME "/files/icones_opc/relatorio_fixos_finanrec.png"
#define REL_FIX_FINPAG_IMG APP_DIRNAME "/files/icones_opc/relatorio_fixos_finanpag.png"
#define IMPRT_TIT_IMG      APP_DIRNAME "/files/icones_opc/import_tits.png"
#define EXIT_IMG           APP_DIRNAME "/files/icones_opc/sair.png"
#define CUPONS_XMLS_DIR    APP_DIRNAME "/files/xmls/cupom/"
#define CACHE_DIR          APP_DIRNAME "/files/cache/"
#define ATUALIZA_VERTMP    APP_DIRNAME "/files/tmp/update_pend"
#define TMPDIR_PATH        APP_DIRNAME "/files/tmp/"
#define TMPFILE_PATH       APP_DIRNAME "/files/tmp/tempfile.tmp"
#define ENCER_FINE_PATH    APP_DIRNAME "/files/tmp/encerr_fine"
#define CHANGELOG_FILES    APP_DIRNAME "/files/files_changelog.txt"

#define IMG_ENVIA           APP_DIRNAME "/files/opcoes_padrao/enviar.png"
#define ICON_PATH           APP_DIRNAME "/files/opcoes_padrao/icones/"
#define TER_RELAT_FILE      APP_DIRNAME "/files/impressao/relatorios/terceiros/"
#define PROD_RELAT_FILE     APP_DIRNAME "/files/impressao/relatorios/produtos/"
#define VND_RELAT_FILE      APP_DIRNAME "/files/impressao/relatorios/vendas/"
#define EST_RELAT_FILE      APP_DIRNAME "/files/impressao/relatorios/estoque/"
#define MOV_RELAT_FILE      APP_DIRNAME "/files/impressao/relatorios/movimentos/"
#define ORC_PROD_RELAT_FILE APP_DIRNAME "/files/impressao/relatorios/orc_prod/"
#define MAILMKT_RELAT_PATH  APP_DIRNAME "/files/impressao/relatorios/mailmkt/"
#define SCRPT_TER_INFOS_ENV APP_DIRNAME "/files/scripts/files/dados_emissor.xml"
#define SCRPT_TER_INFOS_RET APP_DIRNAME "/files/scripts/files/dados_retorno.xml"
#define SCRPT_NFE_INFOS     APP_DIRNAME "/files/scripts/files/dados_nfe.xml"
#define IMG_IMP_LOGO        APP_DIRNAME "/files/impressao/imgs/logo.png"
#define BACKUP_QUERY_FILE   APP_DIRNAME "/files/backup_querys"
#define MOZ_CERT            APP_DIRNAME "/files/cacert.pem"
#define EMBLEM_GENERIC      APP_DIRNAME "/files/icones_opc/emblem_generic.png"
#define SUP_XML             APP_DIRNAME "/files/suporte.xml"
#define ORC_PARAMS          APP_DIRNAME "/files/orc_params.xml"
#define PROD_PARAMS         APP_DIRNAME "/files/prod_params.xml"
#define INTEGR_PARAMS       APP_DIRNAME "/files/integr_params.xml"
#define PRINT_SETTING_FILE  APP_DIRNAME "/files/impressao/print.settings"
#define PRINT_SETUP_FILE    APP_DIRNAME "/files/impressao/page_setup.settings"
#define DB_TABLES_LIST_FILE APP_DIRNAME "/files/db_tables_list"

#define CSS_ORC       "orcamento.css"
#define IMG_IMP_CLI   "imgs/cliente.png"
#define IMG_IMP_PROD  "imgs/produto.png"
#define IMG_IMP_LOCAL "imgs/localidade.png"
#define IMG_IMP_EMAIL "imgs/simb_email.png"
#define IMG_IMP_TEL   "imgs/telefone.png"
#define IMG_IMP_CEL   "imgs/celular.png"
#define IMG_IMP_QNT   "imgs/quantidade.png"

#define SEM_EMAIL "email_vazio"

#define MAX_DATE_LEN 15
#define MAX_TEMA_LEN 50
#define MAX_TEMA_QNT 50
#define MAX_PATH_LEN 1000
#define MAX_EMAIL_LEN 200
#define MAX_OBS_LEN 550
#define MAX_PROD 990
#define CONECT_QNT 1
#define CODE_LEN 15
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
#define MAX_CODE_LEN 15
#define MAX_NAME_LEN 400
#define MAX_RAZ_LEN 400
#define MAX_PRECO_LEN 15
#define MAX_UND_LEN 10
#define MAX_GRP_LEN 100
#define MAX_MRC_LEN 20
#define MAX_FOR_LEN 100
#define MAX_SIGLA 10
#define MAX_GRP 20
#define MAX_ADR_LEN 300
#define MAX_BAIRRO_LEN 100
#define MAX_CID_LEN 50
#define MAX_EST_LEN 50
#define MAX_TEL_LEN 20
#define MAX_CEL_LEN 20
#define MAX_LOGR_LEN 300
#define MAX_URI_LEN 300
#define MAX_PARAM_LEN 20
#define MAX_TIPO_LEN 20
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
#define MAX_FETCH_ROW 3000
#define MAX_SUBGRUPO 30
#define MAX_EST_NOME 20
#define MAX_RELAT_NOME 30
#define MAX_CAMPO_NOME 30
#define MAX_RELAT_CAMPOS 15
#define MAX_PARCELAS_QNT 20
#define MAX_PARC_QNT 20
#define MAX_NIVEL_GER_QNT 10
#define MAX_NIVEL_GER_NOME 50
#define MAX_LOG_DESC 2000
#define MAX_TIPOS_TER 20
#define MAX_TIPO_TER 50
#define MAX_UF_QNT 100
#define MAX_UF_LEN 3
#define MAX_SERVER_LEN 50
#define MAX_COMPLMNTO_LEN 20
#define MAX_URL_LEN 400

#define MAX_FORMPG_CAD 100

#define SESSAO_MAX_INATIVIDADE 10
#define SESSAO_EXP_MIN 30
#define S_ANON_EXP_MIN 5

#define MAX_QUERY_LEN 3000
#define MAX_ROW_LEN (MAX_QUERY_LEN/5)
#define MAX_LINHAS (sizeof(GtkBox*)*ROWS_QNT)*TERC_QNT

#define MAX_POST_QNT 100
#define MAX_SUP_TITLE_LEN 100
#define MAX_SUP_DESC_LEN 1000
#define MAX_SUP_STATUS_LEN 50
#define MAX_SUP_TIPO_LEN 50

#define MAX_TABLE_LEN 20
#define MAX_TABLE_QNT 100

#define MAX_DIF_VLR 0.4

#define PAG_FAT 1
#define PAG_VIST 2

enum{
  VLR_ORIG_NUL,
  VLR_ORIG_PROD,
  VLR_ORIG_CLI,
  VLR_ORIG_OPER,
  VLR_ORIG_DEFAULT
};


enum TIPO_OPERACOES{
  OPER_ENTRADA,
  OPER_SAIDA
};

enum ICMS_INTERSTADUAL_COL{
  INTERICMS_CODE_COL,
  INTERICMS_ORIGEM_COL,
  INTERICMS_DESTINO_COL,
  INTERICMS_ALIQ_COL
};

//id das operacoes
enum ID_OPERACOES{
  VENDA,
  DEV_VENDA,
  COMPRA,
  DEV_COMPRA,
  OUTRAS_OPERACOES
};

#define PEDIDOS_APP_URL_FILES "https://calistupedidos.000webhostapp.com"
#define LAST_VERSION_INFO_URL PEDIDOS_APP_URL_FILES"/last_version.php"
#define VERSIONS_INFO_URL     PEDIDOS_APP_URL_FILES"/list_all_version.php"
#define MAX_VERSION_QNT 20
#define MAX_VERSION_ASSETS 10

#define APP_CONSULT_DOC_URL "https://www.receitaws.com.br/v1/cnpj"

#define NIVEL_TECNICO_THEME "Adwaita"
#endif
