void est_cad_concluir()
{
	char query[MAX_QUERY_LEN];

	if(est_cad_code()!=0)
		return ;

	if(est_cad_nome()!=0)
		return ;

	if(est_cad_alterando==0)
		sprintf(query,"insert into estoques(code,nome) values(%s,'%s')",est_cad_cod_gchar, est_cad_nome_gchar);
	else
		sprintf(query,"update estoques set nome = '%s' where code = %s",est_cad_nome_gchar,est_cad_cod_gchar);

	if(enviar_query(query)!=0){
		popup(NULL,"Erro ao cadastrar estoque");
		return ;
	}

	gtk_widget_grab_focus(est_nome_entry);
	if(est_cad_alterando==0)
		popup(NULL,"Estoque criado com sucesso");
	else
		popup(NULL,"Estoque atualizado com sucesso");

	est_cad_cancelar();

	return ;
}
