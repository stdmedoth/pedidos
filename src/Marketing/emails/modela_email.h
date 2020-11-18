int mkt_email_models();

GtkWidget *mkt_mail_psq_button;
GtkWidget *mkt_mail_code_entry;

GtkWidget *mkt_mail_nome_entry;
GtkWidget *mkt_mail_tipo_combo;
GtkWidget *mkt_mail_setor_combo;

GtkWidget *mkt_mail_headerimg_entry;
GtkWidget *mkt_mail_title_entry;
GtkWidget *mkt_mail_body_entry;
GtkWidget *mkt_mail_footer_entry;
GtkWidget *mkt_mail_backimg_entry;

GtkWidget *mkt_mail_text_view;

gchar *mkt_mail_code_gchar;

int mkt_email_code();

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
