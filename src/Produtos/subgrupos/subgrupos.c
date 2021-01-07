#include "campos/code.c"
#include "campos/nome.c"
#include "campos/pai.c"

#include "concluir.c"
#include "cancelar.c"
#include "excluir.c"
#include "alterar.c"

int cad_subgrupo()
{
	GtkWidget *caixa_grande;
	GtkWidget *nome_subgrp_pai_fixed, *nome_subgrp_pai_frame, *nome_subgrp_pai_box;
	GtkWidget *cod_subgrp_frame, *cod_subgrp_box, *cod_subgrp_fixed;
	GtkWidget *nome_subgrp_box, *nome_subgrp_fixed, *nome_subgrp_frame;
	GtkWidget *opcoes_box, *opcoes_fixed, *opcoes_frame;
	GtkWidget *psq_subgrp_img, *psq_subgrp_box;
	GtkWidget *psq_subgrp_pai_button, *psq_subgrp_pai_img;
	char query[MAX_QUERY_LEN];
	char label_pai[MAX_GRP_LEN+strlen("Grupo Pai")];
	char code[8];
	MYSQL_RES *res;
	MYSQL_ROW row;

	subgrpcode = malloc(MAX_CODE_LEN);
	janela_subgrupo = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(janela_subgrupo),3);
	gtk_widget_set_size_request(janela_subgrupo,500,350);
	gtk_window_set_keep_above(GTK_WINDOW(janela_subgrupo),TRUE);

	caixa_grande = gtk_box_new(1,0);

	campo_nome_subgrg = gtk_entry_new();
	campo_nome_subgrg_pai = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(campo_nome_subgrg_pai),"Nome");
	gtk_widget_set_sensitive(campo_nome_subgrg,FALSE);
	gtk_widget_set_sensitive(campo_nome_subgrg_pai,FALSE);

	nome_subgrp_pai_fixed = gtk_fixed_new();
	nome_subgrp_pai_frame = gtk_frame_new("Grupo Pai");
	cod_subgrp_pai_entry = gtk_entry_new();

	psq_subgrp_pai_button = gtk_button_new();
	psq_subgrp_pai_img = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(psq_subgrp_pai_button),psq_subgrp_pai_img);

	psq_subgrpo_button = gtk_button_new();
	psq_subgrp_img = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(psq_subgrpo_button),psq_subgrp_img);

	nome_subgrp_pai_box = gtk_box_new(1,0);
	psq_subgrp_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(psq_subgrp_box),cod_subgrp_pai_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_subgrp_box),psq_subgrp_pai_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(nome_subgrp_pai_box),campo_nome_subgrg_pai,0,0,0);
	gtk_box_pack_start(GTK_BOX(nome_subgrp_pai_box),psq_subgrp_box,0,0,0);
	gtk_container_add(GTK_CONTAINER(nome_subgrp_pai_frame),nome_subgrp_pai_box);
	gtk_fixed_put(GTK_FIXED(nome_subgrp_pai_fixed),nome_subgrp_pai_frame,30,20);

	cod_subgrp_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(cod_subgrp_entry),"Cód. subgrupo");
	cod_subgrp_frame = gtk_frame_new("Código do Subgrupo");
	cod_subgrp_box = gtk_box_new(0,0);
	cod_subgrp_fixed = gtk_fixed_new();
	cod_subgrp_entry = gtk_entry_new();

	gtk_entry_set_width_chars(GTK_ENTRY(cod_subgrp_entry),15);

	gtk_box_pack_start(GTK_BOX(cod_subgrp_box),cod_subgrp_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(cod_subgrp_box),psq_subgrpo_button,0,0,0);
	gtk_container_add(GTK_CONTAINER(cod_subgrp_frame),cod_subgrp_box);
	gtk_fixed_put(GTK_FIXED(cod_subgrp_fixed),cod_subgrp_frame,30,10);

	nome_subgrp_entry = gtk_entry_new();
	nome_subgrp_box = gtk_box_new(0,0);
	nome_subgrp_frame = gtk_frame_new("Nome Subgrupo");
	nome_subgrp_fixed = gtk_fixed_new();

	gtk_box_pack_start(GTK_BOX(nome_subgrp_box),nome_subgrp_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(nome_subgrp_frame),nome_subgrp_box);
	gtk_fixed_put(GTK_FIXED(nome_subgrp_fixed),nome_subgrp_frame,30,10);

	opcoes_box = gtk_box_new(0,0);
	opcoes_fixed = gtk_fixed_new();
	opcoes_frame = gtk_frame_new("Opcões");

	confirma_subgrp_button = gtk_button_new_with_label("Concluir");
	altera_subgrp_button = gtk_button_new_with_label("Alterar");
	cancela_subgrp_button = gtk_button_new_with_label("Cancelar");
	exclui_subgrp_button = gtk_button_new_with_label("Excluir");

	gtk_box_pack_start(GTK_BOX(opcoes_box),confirma_subgrp_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_box),altera_subgrp_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_box),cancela_subgrp_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_box),exclui_subgrp_button,0,0,5);
	gtk_container_add(GTK_CONTAINER(opcoes_frame),opcoes_box);
	gtk_fixed_put(GTK_FIXED(opcoes_fixed),opcoes_frame,30,10);


	gtk_box_pack_start(GTK_BOX(caixa_grande),cod_subgrp_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),nome_subgrp_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),nome_subgrp_pai_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),opcoes_fixed,0,0,0);

	sprintf(code,"%i",tasker("grupos"));
	gtk_entry_set_text(GTK_ENTRY(cod_subgrp_entry),code);
	gtk_widget_grab_focus(nome_subgrp_entry);

	gtk_container_add(GTK_CONTAINER(janela_subgrupo),caixa_grande);

	g_signal_connect(confirma_subgrp_button,"clicked",G_CALLBACK(conclui_subgrupo),NULL);
	g_signal_connect(altera_subgrp_button,"clicked",G_CALLBACK(altera_subgrupo),NULL);
	g_signal_connect(cancela_subgrp_button,"clicked",G_CALLBACK(cancela_subgrupo),NULL);
	g_signal_connect(exclui_subgrp_button,"clicked",G_CALLBACK(exclui_subgrupo),NULL);

	g_signal_connect(cod_subgrp_entry,"activate",G_CALLBACK(cod_subgrp),NULL);
	g_signal_connect(nome_subgrp_entry,"activate",G_CALLBACK(nome_subgrp),NULL);
	g_signal_connect(cod_subgrp_pai_entry,"activate",G_CALLBACK(pai_subgrp),NULL);

	g_signal_connect(psq_subgrpo_button,"clicked",G_CALLBACK(pesquisa_subgrp_todos),cod_subgrp_entry);
	g_signal_connect(psq_subgrp_pai_button,"clicked",G_CALLBACK(pesquisa_subgrp_todos),cod_subgrp_pai_entry);
	gtk_widget_show_all(janela_subgrupo);
	return 0;
}
