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
#define EMP_SMTP_COL 11
#define EMP_SMTP_PORT_COL 12
#define EMP_EMAIL_COL 13
#define EMP_EMAILSEN_COL 14

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
*cad_emp_smtp_entry,
*cad_emp_smtp_port_entry,
*cad_emp_email_entry,
*cad_emp_emailsenha_entry,
*cad_emp_img_init_entry,
*cad_emp_img_init_chooser,
*cad_emp_script_path_entry,
*cad_emp_script_path_chooser;

static struct{
  char xNome[MAX_NAME_LEN];
  char IE[15];
  int CRT ; // 3
  char CNPJ[CNPJ_S_LEN];

  char xLgr[MAX_LOGR_LEN];
  int nro;
  char xBairro[MAX_BAIRRO_LEN];
  int cMun; //Código de município precisa ser válido e igual o  cMunFG
  char xMun[MAX_CID_LEN];
  char UF[3];
  char CEP[MAX_CEP_LEN];
  int cPais;
  char xPais[MAX_NAME_LEN];

  int tipo_rua;
  char telefone[MAX_TEL_LEN];
  char celular[MAX_TEL_LEN];

  char smtp[MAX_EMAIL_LEN];
  int smtp_port;
  char url_smtp[MAX_EMAIL_LEN];
  char email[MAX_EMAIL_LEN];
  char email_senha[100];

  char init_image_path[MAX_PATH_LEN];
  char script_bin_path[MAX_PATH_LEN];
}cad_emp_strc;

int cadastro_empresa();

int cad_emp_recebe();
GtkWidget *cad_emp_notebook;
static int cad_emp_prim=0,person_tecn_prim=0;
