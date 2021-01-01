#define TRANSP_CODE_COL 0
#define TRANSP_TRSP_COL 1
#define TRANSP_CLI_COL 2
#define TRANSP_CEP1_COL 3
#define TRANSP_CEP2_COL 4
#define TRANSP_NUM_COL 5
#define TRANSP_ORC_COL 6
#define TRANP_VLR_COL 7
#define TRANP_VLR_DESC_COL 8
#define TRANP_OBS_COL 9

static int orc_com_entrega=0, alterando_transp=0;
int orc_transp_frete_pago_int=0;
float orc_transp_frete_pago_vlr=0;
int orc_transp_frete_pago_mudado=0;
static gchar *orc_transp_codigo=NULL,
*orc_transp_nome=NULL,
*orc_transp_num=NULL,
*orc_transp_logradouro=NULL,
*orc_transp_bairro=NULL,
*orc_transp_cidade=NULL,
*orc_transp_estado=NULL,
*orc_transp_cep=NULL,
*orc_transp_telefone=NULL,
*orc_transp_cnpj=NULL,
*orc_transp_ie=NULL,
*orc_transp_obs=NULL,
*orc_transp_valor=NULL,
*orc_transp_desconto=NULL;

static GtkWidget *orc_transp_codigo_entry,
*orc_transp_nome_entry,
*orc_transp_cnpj_entry,
*orc_transp_ie_entry,
*orc_transp_num_entry,
*orc_transp_logradouro_entry,
*orc_transp_bairro_entry,
*orc_transp_frete_pago_button,
*orc_transp_cidade_entry,
*orc_transp_estado_entry,
*orc_transp_cep_entry,
*orc_transp_telefone_entry,
*orc_transp_obs_entry,
*orc_transp_valor_frete_entry,
*orc_transp_desconto_frete_entry;

GtkWidget *psq_ter_orc_transp_button, *psq_ter_orc_transp_img, *psq_ter_orc_transp_box, *psq_ter_orc_transpcep_box;

int orc_transp_desconto_frete();
int orc_transp_valor_frete();
int orc_transp_frete_pago_fun();
