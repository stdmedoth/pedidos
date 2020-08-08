#define COD_TER_COL 0
#define COD_TER_NFE_COL 1
#define RAZ_TER_COL 2
#define DOC_TER_COL 3
#define IE_TER_COL 4
#define TDOC_TER_COL 5
#define TIPC_TER_COL 6
#define TIPI_TER_COL 7
#define CEP_TER_COL 8
#define END_TER_COL 9
#define BAIR_TER_COL 10
#define CID_TER_COL 11
#define UF_TER_COL 12
#define REND_TER_COL 13
#define TRUA_TER_COL 14
#define TEL_TER_COL 15
#define CTEL_TER_COL 16
#define CEL_TER_COL 17
#define CCEL_TER_COL 18
#define EMAIL_TER_COL 19
#define CEMAIL_TER_COL 20

#define TRSP_COD_COL 21
#define TRSP_LOGR_COL 22
#define TRSP_NUM_COL 23
#define TRSP_BAIR_COL 24
#define TRSP_CID_COL 25
#define TRSP_UF_COL 26
#define TRSP_CEP_COL 27
#define TRSP_TEL_COL 28
#define TRSP_OBS_COL 29

#define FLAG_MIN_FRT_PAG_COL 30
#define VLR_MIN_FRT_PAG_COL 31

#define PRAZ_TER_COL 32
#define OBS_TER_COL 33

int tipo_doc,tipo_log;

static GtkWidget *doc_combo;
static GtkWidget *rua_combo;
static GtkWidget *frete_pago_box;
static GtkWidget *frete_pago_flag;
static GtkWidget *frete_pago_frame;
static GtkWidget *frete_pago_entry;

static GtkWidget *ter_img_image,
*ter_img_button_inserir,
*ter_img_button_retirar;

static GtkWidget *ter_notebook,
*ter_principal_box,
*ter_contatos_box,
*ter_entrega_box,
*ter_outros_box,
*ter_principal_label,
*ter_contatos_label,
*ter_entrega_label,
*ter_outros_label;

static GtkWidget *code_label,
*code_ter_nfe_label,
*doc_label,
*inscr_label,
*name_label,
*address_label,
*bairro_label,
*address_num_label,
*cidade_label,
*uf_label,
*cep_label,
*type_label,
*telefone_label,
*contatot_label,
*celular_label,
*contatoc_label,
*email_label,
*contatoe_label,
*observacoes_label,
*prazo_ter_label;

static GtkWidget *code_ter_field,
*code_ter_nfe_field,
*doc_ter_field,
*inscr_ter_field,
*name_ter_field,
*address_ter_field,
*bairro_ter_field,
*address_num_field,
*cidade_ter_field,
*uf_ter_field,
*cep_ter_field,
*type_ter_field,
*telefone_ter_field,
*contatot_ter_field,
*celular_ter_field,
*contatoc_ter_field,
*email_ter_field,
*contatoe_ter_field,
*prod_ter_field,
*subgrp_ter_field,
*observacoes_ter_field,
*prazo_ter_field;

static GtkWidget *transp_codigo_entry,
*transp_nome_entry,
*transp_cnpj_entry,
*transp_ie_entry,
*transp_num_entry,
*transp_logradouro_entry,
*transp_bairro_entry,
*transp_cidade_entry,
*transp_estado_entry,
*transp_cep_entry,
*transp_telefone_entry,
*transp_obs_entry;

GtkWidget *cnst_cad_button;

static GtkWidget *campo_nome_cond_ter,*campo_nome_prod_ter, *campo_nome_subgrp_ter;
static GtkWidget *psq_ter_transp_button, *psq_ter_cep_button, *psq_ter_transpcep_button;
static GtkWidget *psq_ter_transp_img, *psq_ter_cep_img, *psq_ter_transpcep_img;
static GtkWidget *psq_ter_transp_box, *psq_ter_cep_box, *psq_ter_transpcep_box;
static GtkWidget *psq_ter_cond_button,*psq_ter_prod_button, *psq_ter_subgrp_button;
static GtkWidget *ter_trsp_label,*ter_trsp_entry;
static GtkWidget *win_tipo_ter;

static gchar *codigos_ter=NULL,
*codigos_ter_nfe=NULL,
*doc_ter=NULL,
*inscr_ter=NULL,
*nomes_ter=NULL,
*endereco_ter=NULL,
*bairro_ter=NULL,
*address_num=NULL,
*cidade_ter=NULL,
*uf_ter=NULL,
*cep_ter=NULL,
*tipo_ter=NULL,
*celular_ter=NULL,
*telefone_ter=NULL,
*contatot_ter=NULL,
*contatoc_ter=NULL,
*email_ter=NULL,
*contatoe_ter=NULL,
*grupos_ter=NULL,
*prods_ter=NULL,
*observacoes_ter=NULL;

static gchar *transp_codigo=NULL,
*transp_nome=NULL,
*transp_cnpj=NULL,
*transp_ie=NULL,
*transp_num=NULL,
*transp_logradouro=NULL,
*transp_bairro=NULL,
*transp_cidade=NULL,
*transp_estado=NULL,
*transp_cep=NULL,
*transp_telefone=NULL,
*transp_obs=NULL;

static gchar *prazo_ter=NULL;
static int concluindo_ter=0;
static int ter_com_entrega = 0;
