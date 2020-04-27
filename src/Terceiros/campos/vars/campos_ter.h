#define COD_TER_COL 0
#define RAZ_TER_COL 1
#define DOC_TER_COL 2
#define IE_TER_COL 3
#define TDOC_TER_COL 4
#define TIPC_TER_COL 5
#define TIPI_TER_COL 6
#define CEP_TER_COL 7
#define END_TER_COL 8
#define CID_TER_COL 9
#define UF_TER_COL 10
#define REND_TER_COL 11
#define TRUA_TER_COL 12
#define TEL_TER_COL 13
#define CTEL_TER_COL 14
#define CEL_TER_COL 15
#define CCEL_TER_COL 16
#define EMAIl_TER_COL 17
#define CEMAIL_TER_COL 18
#define TRSP_NOME_COL 19
#define TRSP_CNPJ_COL 20
#define TRSP_IE_COL 21
#define TRSP_LOGR_COL 22
#define TRSP_NUM_COL 23
#define TRSP_CID_COL 24
#define TRSP_UF_COL 25
#define VLR_MIN_FRT_PAG_COL 26
#define PRAZ_TER_COL 27
#define OBS_TER_COL 28

int tipo_doc,tipo_log;
GtkWidget *doc_combo;
GtkWidget *rua_combo;

GtkWidget *frete_pago_box;
GtkWidget *frete_pago_flag;
GtkWidget *frete_pago_frame;
GtkWidget *frete_pago_entry;

GtkWidget *ter_img_image, 
*ter_img_button_inserir, 
*ter_img_button_retirar;

GtkWidget *ter_notebook,
*ter_principal_box, 
*ter_contatos_box, 
*ter_entrega_box, 
*ter_outros_box,
*ter_principal_label, 
*ter_contatos_label, 
*ter_entrega_label, 
*ter_outros_label;

GtkWidget *code_label, 
*doc_label, 
*inscr_label,
*name_label, 
*address_label,
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
*seguimento_label,
*observacoes_label,
*prazo_ter_label;

GtkWidget *code_ter_field, 
*doc_ter_field, 
*inscr_ter_field,
*name_ter_field, 
*address_ter_field, 
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
*seguimento_ter_field,
*observacoes_ter_field,
*prazo_ter_field;

GtkWidget *transp_codigo_entry, 
*transp_nome_entry, 
*transp_cnpj_entry, 
*transp_ie_entry, 
*transp_num_entry, 
*transp_logradouro_entry, 
*transp_cidade_entry, 
*transp_estado_entry, 
*transp_cep_entry, 
*transp_telefone_entry, 
*transp_obs_entry;	

GtkWidget *ter_trsp_label,*ter_trsp_entry;

GtkWidget *win_tipo_ter;

gchar *codigos_ter=NULL;
gchar *doc_ter=NULL;
gchar *inscr_ter=NULL;
gchar *nomes_ter=NULL;
gchar *endereco_ter=NULL;
gchar *address_num=NULL;
gchar *cidade_ter=NULL;
gchar *uf_ter=NULL;
gchar *cep_ter=NULL;
gchar *tipo_ter=NULL;
gchar *celular_ter=NULL;
gchar *telefone_ter=NULL;
gchar *contatot_ter=NULL;
gchar *contatoc_ter=NULL;
gchar *email_ter=NULL;
gchar *contatoe_ter=NULL;
gchar *observacoes_ter=NULL;
gchar *prazo_ter=NULL;

gchar *transp_codigo=NULL,
*transp_nome=NULL, 
*transp_num=NULL, 
*transp_logradouro=NULL, 
*transp_cidade=NULL, 
*transp_estado=NULL, 
*transp_cep=NULL, 
*transp_telefone=NULL, 
*transp_cnpj=NULL, 
*transp_ie=NULL, 
*transp_obs=NULL;

char *tip_logds[] = {"Rua","Avenida","Praça","Estrada","Alameda","Travessia","Rodovia"};
