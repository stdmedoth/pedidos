int tipo_doc,tipo_log;

static GtkWidget *doc_combo;
static GtkWidget *rua_combo;
static GtkWidget *frete_pago_box;
static GtkWidget *frete_pago_flag;
static GtkWidget *frete_pago_frame;
static GtkWidget *frete_pago_entry;

static GtkWidget *vinc_transporte_flag;

static GtkWidget *contatos_box, *contatos_treeview;

static GtkWidget *ter_img_image,
*ter_img_button_inserir,
*ter_img_button_retirar;

static GtkWidget *ter_notebook,
*ter_principal_box,
*ter_contatos_box,
*ter_entrega_box,
*ter_financeiro_box,
*ter_outros_box;

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
*observacoes_frame,
*prazo_ter_label;

static GtkWidget *code_ter_field,
*code_ter_nfe_field,
*doc_ter_field,
*inscr_ter_field,
*name_ter_field,
*address_ter_field,
*complmt_ter_field,
*bairro_ter_field,
*address_num_field,
*cidade_ter_field,
*uf_ter_field,
*cep_ter_field,
*type_ter_field,
*prod_ter_field,
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

static GtkWidget *campo_nome_cond_ter,*campo_nome_prod_ter;
static GtkWidget *psq_ter_transp_button, *psq_ter_cep_button, *psq_ter_transpcep_button;
static GtkWidget *psq_ter_transp_img, *psq_ter_cep_img, *psq_ter_transpcep_img;
static GtkWidget *psq_ter_transp_box, *psq_ter_cep_box, *psq_ter_transpcep_box;
static GtkWidget *psq_ter_cond_button,*psq_ter_prod_button;
static GtkWidget *ter_trsp_label,*ter_trsp_entry;
static GtkWidget *win_tipo_ter;

static int vinc_transporte_int=0;

static gchar *codigos_ter=NULL,
*codigos_ter_nfe=NULL,
*doc_ter=NULL,
*inscr_ter=NULL,
*nomes_ter=NULL,
*endereco_ter=NULL,
*bairro_ter=NULL,
*address_num=NULL,
*complmt_ter=NULL,
*cidade_ter=NULL,
*uf_ter=NULL,
*cep_ter=NULL,
*tipo_ter=NULL,
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

struct _titulo titulos_cadter;
