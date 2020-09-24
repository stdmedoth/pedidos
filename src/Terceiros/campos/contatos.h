static GtkTreeModel *create_items_model (void);

static void add_items (int terceiro);

static void add_item (GtkWidget *button, gpointer data);

static GtkTreeModel *create_numbers_model (void);

int contatos_update();

GtkWidget *do_editable_cells ();

static void add_columns (GtkTreeView  *treeview, GtkTreeModel *items_model, GtkTreeModel *numbers_model);

static void cell_edited (GtkCellRendererText *cell, const gchar         *path_string, const gchar         *new_text, gpointer             data);
