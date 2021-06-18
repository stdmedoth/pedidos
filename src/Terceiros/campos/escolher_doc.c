int mover_para_doc()
{
	int opcao=0;
	opcao = gtk_combo_box_get_active(GTK_COMBO_BOX(doc_combo));
	switch(opcao)
	{
		case 1:
			gtk_frame_set_label(GTK_FRAME(code_frame),"Razão");
			break;
		case 2:
			gtk_frame_set_label(GTK_FRAME(code_frame),"Nome");
			break;
		case 3:
			gtk_frame_set_label(GTK_LABEL(code_frame),"Nome");
			break;
	}
	gtk_widget_grab_focus(doc_ter_field);
	return 0;
}

static int ter_tipo_ter_ver_avisado = 0;
int escolha_doc()
{
	int opcao;
	opcao = gtk_combo_box_get_active(GTK_COMBO_BOX(doc_combo));
	doc_ter = (gchar *) gtk_entry_get_text(GTK_ENTRY(doc_ter_field));
	if(strlen(doc_ter) && !ter_tipo_ter_ver_avisado){
		popup(NULL,"Está tentando inserir documento? verifique o tipo de Pessoa.");
		ter_tipo_ter_ver_avisado = 1;
		return 1;
	}

	switch(opcao)
	{
		case 0:
			tipo_doc = 0;
			if(terceiros.criticar.tipodoc==0)
			{
				doc_ter = strdup("");
				gtk_entry_set_text(GTK_ENTRY(doc_ter_field), "");
				gtk_widget_grab_focus(inscr_ter_field);
				return 0;
			}
			popup(NULL,"Você deve escolher um tipo de documento");
			gtk_widget_grab_focus(doc_combo);
			return 1;
		case 1:
			tipo_doc = 1;
			if(cnpj_terc()!=0)
				return 1;
			break;
		case 2:
			tipo_doc = 2;
			if(cpf_terc()!=0)
				return 1;
			break;
		case 3:
			tipo_doc = 3;
			doc_ter = malloc(MAX_CODE_LEN);
			strcpy(doc_ter,"");
			gtk_widget_grab_focus(inscr_ter_field);
			break;
	}
	return 0;
}
