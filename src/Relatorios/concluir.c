int cad_relat_concluir()
{
	char list_campos[MAX_QUERY_LEN*MAX_RELAT_CAMPOS+MAX_RELAT_CAMPOS];
	int cont=1;
	
	if(cad_relat_code()!=0)
		return 1;
	
	if(cad_relat_nome()!=0)
		return 1;
	
	if(cad_rel_tabel_fun()!=0)
		return 1;
	
	if(relat_struct.qnt_campos==0)
	{
		popup(NULL,"Sem campos no relatorio");
		return 1;
	}
	
	while(cont<=MAX_RELAT_CAMPOS)
	{
		if(relat_struct.status[cont] == TRUE)
		{
			if(alterando_cad_rel==0)
			{
				sprintf(list_campos,"insert into criador_relat(code, nome, tabela, campos) values(%s,'%s', %i, %i)",
				cad_rel_code_gchar,
				cad_rel_nome_gchar,
				cad_rel_tabel_int,
				relat_struct.campos_code[cont]);
			}
			else
			{
				if(relat_struct.status[cont] == TRUE)
				{
					if(relat_struct.campos_code_bkp[cont]!=0)
					{
						sprintf(list_campos,"update criador_relat set code = %s, nome = '%s', tabela = %i, campos = %i where campos = %i",
						cad_rel_code_gchar,
						cad_rel_nome_gchar,
						cad_rel_tabel_int,
						relat_struct.campos_code_bkp[cont],
						relat_struct.campos_code[cont]);
					}
					else
					{
						sprintf(list_campos,"insert into criador_relat(code, nome, tabela, campos) values(%s,'%s', %i, %i)",
						cad_rel_code_gchar,
						cad_rel_nome_gchar,
						cad_rel_tabel_int,
						relat_struct.campos_code[cont]);
					}	
				}
			}
			if(enviar_query(list_campos)!=0)
			{
				popup(NULL,"Erro ao inserir dados na criação do relatório");
				return 1;
			}
		}
		cont++;
	}
	if(alterando_cad_rel==0)
		popup(NULL,"Relatório criado com sucesso!");
	else
		popup(NULL,"Relatório atualizado com sucesso!");
	cad_relat_cancelar();
	return 0;
}
