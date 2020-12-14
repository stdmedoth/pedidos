enum{
  CTTO_ID_COL,
  CTTO_TER_COL,
  CTTO_NOME_COL,
  CTTO_CEL_COL,
  CTTO_TEL_COL,
  CTTO_EMAIL_COL
};

typedef struct _Contato
{
  gint   id;
  gint ativo;
  gchar *nome;
  gchar *celular;
  gchar *telefone;
  gchar *email;
}Contato;

#define MAX_CNTTS_QNT 20

static int contatos_ter=0;
static int contatos_qnt=0;
static int cntt_exists[MAX_CNTTS_QNT];

struct _Contato cntts[MAX_CNTTS_QNT];

enum
{
  COLUMN_CTTO_ID,
  COLUMN_CTTO_NOME,
  COLUMN_CTTO_CEL,
  COLUMN_CTTO_TEL,
  COLUMN_CTTO_EMAIL,
  NUM_ITEM_COLUMNS
};

enum
{
  COLUMN_NUMBER_TEXT,
  NUM_NUMBER_COLUMNS
};

static GArray *cont_lis = NULL;

static GtkTreeModel *create_items_model (void);

static void add_items (int terceiro);

static void add_item (GtkWidget *button, gpointer data);

static GtkTreeModel *create_numbers_model (void);

int contatos_update();

GtkWidget *do_editable_cells ();

static void add_columns (GtkTreeView  *treeview, GtkTreeModel *items_model, GtkTreeModel *numbers_model);

static void cell_edited (GtkCellRendererText *cell, const gchar         *path_string, const gchar         *new_text, gpointer             data);
