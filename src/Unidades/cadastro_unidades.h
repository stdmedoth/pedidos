static gchar *codigos_und;
static gchar *nomes_und;
static gchar *sigla_und;
static gchar *mult_und;

static GtkWidget *code_und_label,   *code_und_field, *code_und_frame;
static GtkWidget *name_und_label,   *name_und_field, *name_und_frame;
static GtkWidget *sigla_und_label,  *sigla_und_field, *sigla_und_frame;
static GtkWidget *mult_und_label,   *mult_und_field, *mult_und_frame;
static GtkWidget *medida_und_combo_box;
static int medidas_und=0;
static GtkWidget *psq_cad_und_button, *psq_cad_und_img, *psq_cad_und_box;

static int altera_und();
static int alterando_und=0;
static int concluindo_und=0;

#include "codigo.c"
#include "nome.c"
#include "sigla.c"
#include "multiplo.c"
#include "medida.c"
