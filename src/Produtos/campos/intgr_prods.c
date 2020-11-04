int intgr_puxar_produtos(int code){

		int cont=0;
		char query[MAX_QUERY_LEN];
		MYSQL_RES *res;
		MYSQL_ROW row;
		struct _WC_Product **produtos = get_wc_produtos();
		int importado=0;
		if(produtos){
			while(produtos[cont]){
				sprintf(query,"select * from produtos where code = %i",produtos[cont]->ID);
				if(!(res = consultar(query))){
					popup(NULL,"Não foi possível consultar produto");
					return 1;
				}
				if( !code || code == produtos[cont]->ID ){

					if((row = mysql_fetch_row(res))){
						sprintf(query,"update produtos set nome = '%s', peso = %.2f,preco = %.2f, observacoes = '%s' where code = %i",
						produtos[cont]->nome,
						produtos[cont]->Weight,
						produtos[cont]->Price,
						produtos[cont]->descricao,
						produtos[cont]->ID);
						if(enviar_query(query)){
							popup(NULL,"Não foi possível atualizar produtos");
							return 1;
						}
					}else{
						sprintf(query,"insert into produtos(code,nome,peso,preco,observacoes) values(%i, '%s', %.2f, %.2f, '%s')",
						produtos[cont]->ID,
						produtos[cont]->nome,
						produtos[cont]->Weight,
						produtos[cont]->Price,
						produtos[cont]->descricao);
						if(enviar_query(query)){
							popup(NULL,"Não foi possível cadastrar produtos");
							return 1;
						}
					}
					importado++;
				}
				cont++;
			}
			if(!importado){
				popup(NULL,"Nenhum produto importado");
				return 1;
			}
		}
    return 0;
}

int intgr_prods(){
  if(code_prod())
    return 1;

  if(!intgr_puxar_produtos(atoi(codigos_prod)) && !altera_prod())
    popup(NULL,"Integrado com sucesso");
		
  return 0;
}
