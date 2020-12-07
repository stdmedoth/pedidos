int mkt_mail_cancelar_fun();
int mkt_mail_alterar_fun();
int mkt_mail_concluir_fun();
int mkt_mail_visualizar_fun();
int mkt_mail_montar_fun();
int mkt_mail_excluir_fun();
int mkt_mail_modelpronto_fun();

int mkt_email_models();

int mkt_mail_code_fun();
int mkt_mail_nome_fun();
int mkt_mail_tipo_fun();
int mkt_mail_header_fun();
int mkt_mail_body_fun();
int mkt_mail_footer_fun();
int mkt_envia_emails();

static int mkt_email_alterando =0, mkt_email_concluindo =0, mkt_email_visualizando =0  ;

GtkWidget *mkt_mail_psq_button;
GtkWidget *mkt_mail_code_entry;
GtkWidget *mkt_mail_modelos_button;

GtkWidget *mkt_mail_nome_entry;
GtkWidget *mkt_mail_assunto_entry;
GtkWidget *mkt_mail_tipo_combo;
GtkWidget *mkt_mail_setor_combo;

GtkWidget *mkt_mail_css_path_choose;
GtkWidget *mkt_mail_title_entry;
GtkWidget *mkt_mail_editorbody1_view;
GtkWidget *mkt_mail_editorbody2_view;
GtkWidget *mkt_mail_editorbody3_view;
GtkWidget *mkt_mail_editorfooter_view;
GtkWidget *mkt_mail_headerimg_path_choose;
GtkWidget *mkt_mail_backimg_path_choose;

GtkWidget *mkt_mail_header_view;
GtkWidget *mkt_mail_header_color;
GtkWidget *mkt_mail_corpo_color;
GtkWidget *mkt_mail_corpo_view;
GtkWidget *mkt_mail_footer_view;
GtkWidget *mkt_mail_footer_color;

GtkWidget *mkt_mail_html_notebook;
GtkWidget *mkt_mail_editor_notebook;
GtkWidget *mkt_mail_geral_notebook;

GtkWidget *mkt_mail_concluir_button;

gchar *mkt_mail_code_gchar, *mkt_mail_nome_gchar, *mkt_mail_assunto_gchar;
gchar *mkt_mail_header_gchar, *mkt_mail_body_gchar, *mkt_mail_footer_gchar;
gint mkt_mail_tipo_int, mkt_mail_setor_int;

int mkt_email_code();

enum EMAIL_HEADER_COLS{
  EMLHEADER_CODE,
  EMLHEADER_CONTEUDO,
  EMLHEADER_EMAILID
};

enum EMAIL_BODY_COLS{
  EMLBODY_CODE,
  EMLBODY_CONTEUDO,
  EMLBODY_EMAILID
};

enum EMAIL_FOOTER_COLS{
  EMLFOOTER_CODE,
  EMLFOOTER_CONTEUDO,
  EMLFOOTER_EMAILID
};


enum EMAIL_MODEL_COLS{
  EMAILMODEL_CODE_COL,
  EMAILMODEL_NOME_COL,
  EMAILMODEL_ASSUNTO_COL,
  EMAILMODEL_TIPO_COL,
  EMAILMODEL_SETOR_COL
};

enum EMAIL_TIPOS{
  EMAIL_NEWSLETTER,
  EMAIL_PROMO,
  EMAIL_SAZONAL,
  EMAIL_CLI_INAT,
  EMAIL_FUNC_ALERT,
  EMAIL_FUNC_CROSS_SELL,
  EMAIL_FUNC_UPSELL,
  EMAIL_FUNC_BOAVINDAS,
  EMAIL_FUNC_FEEDBACK,
  EMAIL_GENERICO
};

#define MODEL_SERVER_URL "http://localhost/email_models/"
