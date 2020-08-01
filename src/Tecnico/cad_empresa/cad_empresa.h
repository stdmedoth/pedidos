#define EMP_CNPJ_COL 0
#define EMP_NOME_COL 1
#define EMP_CEP_COL 2
#define EMP_LOGR_COL 3
#define EMP_BAIR_COL 4
#define EMP_CID_COL 5
#define EMP_UF_COL 6
#define EMP_NRUA_COL 7
#define EMP_TRUA_COL 8
#define EMP_TEL_COL 9
#define EMP_CEL_COL 10
#define EMP_EMAIL_COL 11

GtkWidget *cad_emp_nome_entry,
*cad_emp_cpnj_entry,
*cad_emp_logr_entry,
*cad_emp_cep_entry,
*cad_emp_bairro_entry,
*cad_emp_cidade_entry,
*cad_emp_uf_entry,
*cad_emp_numrua_spin,
*cad_emp_tiporua_combo,
*cad_emp_telefone_entry,
*cad_emp_celular_entry,
*cad_emp_email_entry,
*cad_emp_img_init_entry,
*cad_emp_img_init_chooser;

static struct{
  char nome[MAX_NAME_LEN];
  char cnpj[CNPJ_S_LEN];
  char logr[MAX_LOGR_LEN];
  char cep[MAX_CEP_LEN];
  char bairro[MAX_BAIRRO_LEN];
  char cidade[MAX_CID_LEN];
  char uf[MAX_CID_LEN];
  int numrua;
  int tipo_rua;
  char telefone[MAX_TEL_LEN];
  char celular[MAX_TEL_LEN];
  char email[MAX_EMAIL_LEN];
  char init_image_path[MAX_PATH_LEN];
}cad_emp_strc;

int cadastro_empresa();

int cad_emp_recebe();
GtkWidget *cad_emp_notebook;
static int cad_emp_prim=0,person_tecn_prim=0;
