int gerar_orcs(struct _orc *orc){
  carregar_navimps();

	if(!imps_qnt && !navs_qnt){
		popup(NULL,"Não há impressoras ou navegadores configurados!");
		return 1;
	}
  char *gerando_file = malloc(MAX_PATH_LEN);
  char *formata_float = malloc(MAX_PRECO_LEN); //desconto
	char *formata_float2 = malloc(MAX_PRECO_LEN); //quantidade
	char *formata_float3 = malloc(MAX_PRECO_LEN); //preco
  char *familia_char = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO-1);
	char *source = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO);
	char *dest = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO);
  char *query = malloc(MAX_QUERY_LEN);
  MYSQL_RES *res;
  MYSQL_ROW row;

  sprintf(gerando_file,"%simp%s.html",ORC_PATH,codigo_orc_gchar);





  return 0;
}
