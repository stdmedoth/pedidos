int mover_para_doc()
{
	gtk_widget_grab_focus(doc_ter_field);
	return 0;
}
int escolha_doc()
{
	int opcao=0;
	opcao = gtk_combo_box_get_active(GTK_COMBO_BOX(doc_combo));
	switch(opcao)
	{
		case 0:
			tipo_doc = 0;
			popup(NULL,"Você deve escolher um tipo de documento");
			gtk_widget_grab_focus(doc_combo);
			break;
		case 1:
			tipo_doc = 1;
			cnpj_terc();
			break;
		case 2:
			tipo_doc = 2;
			cpf_terc();
			break;
		case 3:
			gtk_widget_grab_focus(name_ter_field);
			break;
	}
	return 0;
}
