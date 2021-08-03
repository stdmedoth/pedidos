enum{
  CTTO_ID_COL,
  CTTO_TER_COL,
  CTTO_NOME_COL,
  CTTO_TEL_COL,
  CTTO_CEL_COL,
  CTTO_EMAIL_COL
};

typedef struct _Contato
{
  gint   id;
  gint ativo;
  gint exists;
  gchar *nome;
  gchar *celular;
  gchar *telefone;
  gchar *email;
}Contato;

#define MAX_CNTTS_QNT 20

int contatos_ter=0;

enum
{
  COLUMN_CTTO_ID,
  COLUMN_CTTO_NOME,
  COLUMN_CTTO_TEL,
  COLUMN_CTTO_CEL,
  COLUMN_CTTO_EMAIL,
  NUM_ITEM_COLUMNS
};

enum
{
  COLUMN_NUMBER_TEXT,
  NUM_NUMBER_COLUMNS
};

static int contato_add_item_filled(Contato *contato);

static GArray *cont_lis = NULL, *cont_rem_lis = NULL;

static GtkTreeModel *create_items_model (void);

static int add_items (int terceiro);

static void add_item (GtkWidget *button, gpointer data);

static GtkTreeModel *create_numbers_model (void);

int contatos_update();

GtkWidget *do_editable_cells ();

static void add_columns (GtkTreeView  *treeview, GtkTreeModel *items_model, GtkTreeModel *numbers_model);

static void cell_edited (GtkCellRendererText *cell, const gchar         *path_string, const gchar         *new_text, gpointer             data);

int ter_contatos_get_last();
