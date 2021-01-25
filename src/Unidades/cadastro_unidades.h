gchar *codigos_und;
gchar *nomes_und;
gchar *sigla_und;
gchar *mult_und;

GtkWidget *code_und_label,   *code_und_field, *code_und_frame;
GtkWidget *name_und_label,   *name_und_field, *name_und_frame;
GtkWidget *sigla_und_label,  *sigla_und_field, *sigla_und_frame;
GtkWidget *mult_und_label,   *mult_und_field, *mult_und_frame;
GtkWidget *medida_und_combo_box;
int medidas_und=0;

GtkWidget *psq_cad_und_button, *psq_cad_und_img, *psq_cad_und_box;

int altera_und();
int alterando_und=0;
int concluindo_und=0;

GtkWidget *und_concluir_button, *und_alterar_button, *und_excluir_button, *und_cancelar_button;

int  cad_und();

int multiplo_und();

int deleta_und();

int concluido_und();

int und_cancelar_fun();

struct _und *cad_und_get_und(int und_code);

enum{
  UND_CODE_COL,
  UND_NOME_COL,
  UND_SIGLA_COL,
  UND_MULTIPLO_COL,
  UND_MEDIDA_COL
};

struct _und{
  int code;
  char *nome;
  char *sigla;
  float multiplo;
  int medida;
};
