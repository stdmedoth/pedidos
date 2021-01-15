enum CAD_EMP_ENUM{
  EMP_CODE_COL,
  EMP_CNPJ_COL,
  EMP_NOME_COL,
  EMP_IE_COL,
  EMP_IM_COL,
  EMP_REGTRIB_COL,
  EMP_REGISSQN_COL,
  EMP_DIGCERTPATH_COL,
  EMP_DIGCERTPASS_COL,
  EMP_CEP_COL,
  EMP_LOGR_COL,
  EMP_BAIR_COL,
  EMP_CID_COL,
  EMP_UF_COL,
  EMP_NRUA_COL,
  EMP_TRUA_COL,
  EMP_TEL_COL,
  EMP_CEL_COL,
  EMP_SMTP_COL,
  EMP_SMTP_PORT_COL,
  EMP_EMAIL_COL,
  EMP_EMAILSEN_COL,
  EMP_SOBRE_COL,
};

enum REGTRIB{
  SIMPLES_NACIONAL=1,
  SIMPLES_NAC_EXCESSO=2,
  REGIME_NORMAL=3,
};

enum REGISSQN_ENUM{
  REGISSQN_MEMMUN,
  REGISSQN_ESTM,
  REGISSQN_SOCIPROF,
  REGISSQN_COOP,
  REGISSQN_MEI,
  REGISSQN_QNT
};

GtkWidget *cad_emp_code_entry,
*cad_emp_nome_entry,
*cad_emp_cpnj_entry,
*cad_emp_ie_entry,
*cad_emp_im_entry,
*cad_emp_regime_combo,
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
*cad_emp_sobre_text_view,
*cad_emp_img_init_entry,
*cad_emp_img_init_chooser,
*cad_emp_digcert_path_entry,
*cad_emp_digcert_pass_entry,
*cad_emp_digcert_path_chooser,
*cad_emp_script_path_entry,
*cad_emp_script_path_chooser;

static struct _cad_emp{
  char xNome[MAX_NAME_LEN];
  char IE[15];
  char IM[15];
  int CRT ; // 3
  char CNPJ[CNPJ_S_LEN];
  char RegTrib[12];
  int  RegTribInt;
  char cRegTribISSQN[12];
  char indRatISSQN[12]; /* S / N */

  char digcertpath[MAX_PATH_LEN];
  char digcertpass[20];

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

  char sobre[MAX_OBS_LEN];

  char init_image_path[MAX_PATH_LEN];
  char script_bin_path[MAX_PATH_LEN];
}cad_emp_strc;

static struct _cad_software_house{
  char xNome[MAX_NAME_LEN];
  char CNPJ[CNPJ_S_LEN];
  char signAC[345];
  char tpAmb[10];
}cad_software_house;

int cadastro_empresa();

int cad_emp_recebe();
GtkWidget *cad_emp_notebook;
static int cad_emp_prim=0,person_tecn_prim=0;
int cad_emp_alterando=0, cad_emp_cancelando=0, cad_emp_concluindo=0;

int cad_emp_exists_emails();

int cad_emp_alterar();

int cad_emp_concluir();
