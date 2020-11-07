#include "../../etc/basic_headers.h"

char *wp_all_prod_query = "SELECT p.ID, p.post_title 'nome', p.post_content 'descrição', GROUP_CONCAT(cat.name SEPARATOR ' | ') 'Category', MAX(CASE WHEN meta.meta_key = '_sku' THEN meta.meta_value END) 'SKU', MAX(CASE WHEN meta.meta_key = '_price' THEN meta.meta_value END) 'Price', MAX(CASE WHEN meta.meta_key = '_weight' THEN meta.meta_value END) 'Weight', MAX(CASE WHEN meta.meta_key = '_stock' THEN meta.meta_value END) 'Stock' FROM wp_posts AS p JOIN wp_postmeta AS meta ON p.ID = meta.post_ID LEFT JOIN ( SELECT pp.id, GROUP_CONCAT(t.name SEPARATOR ' > ') AS name FROM wp_posts AS pp JOIN wp_term_relationships tr ON pp.id = tr.object_id JOIN wp_term_taxonomy tt ON tr.term_taxonomy_id = tt.term_taxonomy_id JOIN wp_terms t ON tt.term_id = t.term_id || tt.parent = t.term_id WHERE tt.taxonomy = 'product_cat' GROUP BY pp.id, tt.term_id ) cat ON p.id = cat.id WHERE (p.post_type = 'product' OR p.post_type = 'product_variation') AND meta.meta_key IN ('_sku', '_price', '_weight', '_stock') AND meta.meta_value is not null GROUP BY p.ID" ;

struct _WC_Product{
  int ID;
  char *nome;
  char *descricao;
  char *Category;
  char *SKU;
  float Price;
  float Weight;
  float Stock;
};

struct _WC_Product **get_wc_produtos();

int enviar_wc_produtos(struct _WC_Product **produtos);
