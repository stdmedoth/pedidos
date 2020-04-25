#define COD_TER_COL 0
#define RAZ_TER_COL 1
#define DOC_TER_COL 2
#define TDOC_TER_COL 3
#define TIPC_TER_COL 4
#define TIPI_TER_COL 5
#define CEP_TER_COL 6
#define END_TER_COL 7
#define CID_TER_COL 8
#define UF_TER_COL 9
#define REND_TER_COL 10
#define TRUA_TER_COL 11
#define TEL_TER_COL 12
#define CTEL_TER_COL 13
#define CEL_TER_COL 14
#define CCEL_TER_COL 15
#define EMAIl_TER_COL 16
#define CEMAIL_TER_COL 17
#define PRAZ_TER_COL 18
#define OBS_TER_COL 19

int tipo_doc,tipo_log;
GtkWidget *doc_combo;
GtkWidget *rua_combo;

GtkWidget *ter_img_image, *ter_img_box, *ter_img_frame, *ter_img_button_inserir, *ter_img_button_retirar, *ter_img_buttons_box;
GtkWidget *ter_entrega_frame,*ter_endereco_frame;

GtkWidget *ter_notebook,
*ter_principal_box, *ter_contatos_box, *ter_entrega_box, *ter_outros_box,
*ter_principal_label, *ter_contatos_label, *ter_entrega_label, *ter_outros_label;

GtkWidget *code_label, *doc_label, *insc_label,
*name_label, *address_label,*address_num_label,*cidade_label, *uf_label,
*cep_label, *type_label, *telefone_label, *contatot_label, 
*celular_label, *contatoc_label, *email_label, 
*contatoe_label, *seguimento_label,*observacoes_label,
*prazo_ter_label;

GtkWidget *code_ter_field, 
*doc_ter_field, *insc_ter_field,*name_ter_field, 
*address_ter_field, *address_num_field, *cidade_ter_field, *uf_ter_field,
*cep_ter_field, *type_ter_field,
*telefone_ter_field, *contatot_ter_field, 
*celular_ter_field, *contatoc_ter_field, 
*email_ter_field, *contatoe_ter_field, 
*seguimento_ter_field,*observacoes_ter_field,
*prazo_ter_field;

GtkWidget *ter_trsp_label,*ter_trsp_entry;

GtkWidget *win_tipo_ter;

gchar *codigos_ter=NULL;
gchar *doc_ter=NULL;
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

char *tip_logds[] = {"Rua","Avenida","Praça","Estrada","Alameda","Travessia","Rodovia"};
