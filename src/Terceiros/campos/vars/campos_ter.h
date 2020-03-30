gchar *codigos_ter=NULL;
gchar *doc_ter=NULL;
gchar *nomes_ter=NULL;
gchar *endereco_ter=NULL;
gchar *cep_ter=NULL;
gchar *tipo_ter=NULL;
gchar *celular_ter=NULL;
gchar *telefone_ter=NULL;
gchar *contatot_ter=NULL;
gchar *contatoc_ter=NULL;
gchar *email_ter=NULL;
gchar *contatoe_ter=NULL;
gchar *observacoes_ter=NULL;

int tipo_doc;
GtkWidget *doc_combo;

GtkWidget *code_label, *doc_label, 
*name_label, *address_label, *cep_ter_label,
*type_label, *telefone_label, *contatot_label, 
*celular_label, *contatoc_label, *email_label, 
*contatoe_label, *observacoes_label;

GtkWidget *code_ter_field, 
*doc_ter_field, *name_ter_field, 
*address_ter_field, *cep_ter_field, 
*type_ter_field,
*telefone_ter_field, *contatot_ter_field, 
*celular_ter_field, *contatoc_ter_field, 
*email_ter_field, *contatoe_ter_field, 
*observacoes_ter_field;

GtkWidget *win_tipo_ter;
