int gerar_orcs( int code_orc ){

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

  struct _orc orc;
  orc.infos.code = code_orc;

	orc.valores.valor_prds = 0.000;
	orc.valores.valor_total = 0.000;
	orc.valores.desconto_total = 0.000;
	orc.valores.valor_prds_desc = 0.000;
	orc.valores.valor_prds_liquido = 0.000;
	orc.valores.valor_frete_liquido = 0.000;

  orc.parcelas.condpag.parcelas_qnt = 0;

  sprintf(gerando_file,"%simp%i.html",ORC_PATH,orc.infos.code);

  FILE *orc_file = fopen(gerando_file,"w");
  if(orc_file==NULL)
  {
    popup(NULL,"Não está sendo possivel gerar o arquivo\n\tFeche o navegador");
    return 1;
  }

  if(!rec_orc_infos(&orc)){
    popup(NULL,"Erro ao receber dados do orcamento");
    return 1;
  }

  gerar_orc_header(orc_file);

  gerar_orc_infosheader(orc_file, &orc);

  fprintf(orc_file,"<body>\n");

  gerar_orc_cli(orc_file, &orc);

  gerar_orc_itens(orc_file, &orc);


  gerar_orc_transporte(orc_file, &orc);

  rec_orc_datas( &orc );
  if(orc.parcelas.condpag.tipo_parc != CONDPAG_S_FIN)
    gerar_orc_titulos(orc_file, &orc);

  gerar_orc_observacao(orc_file, &orc);

	fprintf(orc_file,"</body>\n");
	fprintf(orc_file,"</html>\n");

  fclose(orc_file);

  if(escolher_finalizacao(gerando_file)){
    popup(NULL,"Erro na finalizacao");
		return 1;
	}
  
  return 0;
}
