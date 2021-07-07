int check_updated(){
	FILE *tmp_updt_fp = fopen(ATUALIZA_VERTMP,"r");
    if(!tmp_updt_fp){
      return 0;
    }

    return 1;
}