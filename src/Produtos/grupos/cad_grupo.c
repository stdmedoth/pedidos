#include "campos/code.c"
#include "campos/nome.c"

#include "concluir.c"
#include "excluir.c"
#include "alterar.c"
#include "cancelar.c"

struct _grupo *grp_get_grupo(int code_grp){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	enum{
		GRP_CODE,
		GRP_NOME,
		PAI_CODE,
		PAI_NOME,
		COLS_QNT
	};

	struct _grupo *grupo = malloc(sizeof(struct _grupo));
	sprintf(query,"select b.code, b.nome, a.code, a.nome from grupos as a inner join grupos as b on a.code = b.pai where b.code = %i", code_grp);
	if(!(res = consultar(query))){
		return NULL;
	}

	if((row = mysql_fetch_row(res))){
		grupo->code = atoi(row[GRP_CODE]);
		grupo->nome = strdup(row[GRP_NOME]);
		grupo->pai = atoi(row[PAI_CODE]);
		grupo->pai_nome = strdup(row[GRP_NOME]);
	}

	return grupo;
}

GtkTreeStore *grp_get_tree(GtkTreeStore *modelo, int pai, GtkTreeIter *campo){

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	enum{
		GRP_CODE,
		GRP_NOME,
		PAI_NOME,
		COLS_QNT
	};

	sprintf(query,"select b.code, b.nome, a.nome from grupos as a inner join grupos as b on a.code = b.pai where b.pai = %i", pai);
	if(!(res = consultar(query))){
		return NULL;
	}

	while((row = mysql_fetch_row(res))){
		if(atoi(row[0])!=1){
			GtkTreeIter campo_novo;
			g_print("Inserindo codigo: %s nome: %s\n",row[0],row[1]);

			gtk_tree_store_append(modelo,&campo_novo, campo);
			gtk_tree_store_set(modelo,&campo_novo,
				GRP_CODE, row[GRP_CODE],
				GRP_NOME, row[GRP_NOME],
				PAI_NOME, row[PAI_NOME],
				-1);


			//pegar os grupos filhos
			if(!grp_get_tree(modelo, atoi(row[GRP_CODE]), &campo_novo))
				return modelo;
		}
	}

	return modelo;
}

int cad_grupo()
{
	enum {
    COLUMN0,
    COLUMN1,
    COLUMN2,
    N_COLUMNS
  };
	GtkWidget *visao_geral_grp_scroll, *visao_geral_grp_box, *visao_geral_grp_fixed, *visao_geral_grp_frame;
	GtkWidget *caixa_grande;
	GtkWidget *cod_grupo_frame, *cod_grupo_box, *cod_grupo_fixed;
	GtkWidget *nome_grupo_frame, *nome_grupo_box, *nome_grupo_fixed;
	GtkWidget *add_subgrp_fixed;
	GtkWidget *opcoes_grp_box, *opcoes_grp_frame, *opcoes_grp_fixed;
	GtkWidget *layout_janela_grupo;
	GtkWidget *psq_grp_img;
	GtkWidget *confirma_grp_img, *cancela_grp_img, *exclui_grp_img, *altera_grp_img;

	GtkTreeViewColumn *coluna1, *coluna2, *coluna3;
	GtkCellRenderer *celula1, *celula2, *celula3;
	GtkTreeStore *modelo;

	char code[8];

	janela_grupo = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_icon_name(GTK_WINDOW(janela_grupo),"emblem-documents");
	gtk_widget_set_size_request(janela_grupo,900,400);
	gtk_window_set_transient_for(GTK_WINDOW(janela_grupo),GTK_WINDOW(janela_principal));
	gtk_window_set_position(GTK_WINDOW(janela_grupo),3);

	janelas_gerenciadas.vetor_janelas[REG_CAD_GRP].reg_id = REG_CAD_GRP;
	janelas_gerenciadas.vetor_janelas[REG_CAD_GRP].aberta = 1;
	if(ger_janela_aberta(janela_grupo, &janelas_gerenciadas.vetor_janelas[REG_CAD_GRP]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_CAD_GRP].janela_pointer = janela_grupo;

	cad_grp_treeview = gtk_tree_view_new();
	coluna1 = gtk_tree_view_column_new();
	coluna2 = gtk_tree_view_column_new();
	coluna3 = gtk_tree_view_column_new();
	celula1 = gtk_cell_renderer_text_new();
	celula2 = gtk_cell_renderer_text_new();
	celula3 = gtk_cell_renderer_text_new();
	modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(cad_grp_treeview),TRUE);
	gtk_tree_view_set_headers_clickable(GTK_TREE_VIEW(cad_grp_treeview), TRUE);
	gtk_tree_view_set_headers_clickable(GTK_TREE_VIEW(cad_grp_treeview), TRUE);
	gtk_tree_view_set_headers_clickable(GTK_TREE_VIEW(cad_grp_treeview), TRUE);
	//gtk_tree_view_set_show_expanders(GTK_TREE_VIEW(cad_grp_treeview),TRUE);
	gtk_tree_view_column_set_title(coluna1,"Código");
	gtk_tree_view_column_pack_start(coluna1,celula1,TRUE);
	gtk_tree_view_column_add_attribute(coluna1,celula1,"text",0);

	gtk_tree_view_column_set_title(coluna2,"Nome");
	gtk_tree_view_column_pack_start(coluna2,celula2,TRUE);
	gtk_tree_view_column_add_attribute(coluna2,celula2,"text",1);

	gtk_tree_view_column_set_title(coluna3,"Pai");
	gtk_tree_view_column_pack_start(coluna3,celula3,TRUE);
	gtk_tree_view_column_add_attribute(coluna3,celula3,"text",2);

	gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(cad_grp_treeview),TRUE);
	gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(cad_grp_treeview),TRUE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(cad_grp_treeview),coluna1);
	gtk_tree_view_append_column(GTK_TREE_VIEW(cad_grp_treeview),coluna2);
	gtk_tree_view_append_column(GTK_TREE_VIEW(cad_grp_treeview),coluna3	);
	gtk_tree_view_set_level_indentation(GTK_TREE_VIEW(cad_grp_treeview),20);

	if(!grp_get_tree(modelo, 1, NULL))
		return 1;

	gtk_tree_view_column_set_visible(coluna1,FALSE);
	gtk_tree_view_column_set_visible(coluna3,FALSE);

	gtk_tree_view_set_model(GTK_TREE_VIEW(cad_grp_treeview),GTK_TREE_MODEL(modelo));
	gtk_tree_view_column_set_reorderable(coluna2, TRUE);
	gtk_widget_set_size_request(cad_grp_treeview,430,210);
	gtk_tree_view_expand_all(GTK_TREE_VIEW(cad_grp_treeview));
	g_object_unref(modelo);

	psq_grp_button = gtk_button_new();
	psq_grp_img = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(psq_grp_button),psq_grp_img);

	cod_grupo_frame = gtk_frame_new("Código do Grupo");
	cod_grupo_box = gtk_box_new(0,0);
	cod_grupo_fixed = gtk_fixed_new();
	cod_grp_entry = gtk_entry_new();

	gtk_entry_set_width_chars(GTK_ENTRY(cod_grp_entry),10);
	gtk_box_pack_start(GTK_BOX(cod_grupo_box),cod_grp_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(cod_grupo_box),psq_grp_button,0,0,0);
	gtk_container_add(GTK_CONTAINER(cod_grupo_frame),cod_grupo_box);
	gtk_fixed_put(GTK_FIXED(cod_grupo_fixed),cod_grupo_frame,50,20);

	nome_grupo_frame = gtk_frame_new("Nome do Grupo");
	nome_grupo_box = gtk_box_new(0,0);
	nome_grupo_fixed = gtk_fixed_new();
	nome_grp_entry = gtk_entry_new();

	gtk_entry_set_width_chars(GTK_ENTRY(nome_grp_entry),20);
	gtk_container_add(GTK_CONTAINER(nome_grupo_frame),nome_grp_entry);
	gtk_box_pack_start(GTK_BOX(nome_grupo_box),nome_grupo_frame,0,0,0);
	gtk_fixed_put(GTK_FIXED(nome_grupo_fixed),nome_grupo_box,50,40);

	visao_geral_grp_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(visao_geral_grp_scroll),GTK_SHADOW_ETCHED_IN);
	visao_geral_grp_box = gtk_box_new(1,0);

	visao_geral_grp_fixed = gtk_fixed_new();
	visao_geral_grp_frame = gtk_frame_new("Grupos:");
	gtk_container_set_border_width(GTK_CONTAINER(visao_geral_grp_box),10);

	gtk_box_pack_start(GTK_BOX(visao_geral_grp_box),cad_grp_treeview,0,0,0);

	gtk_container_add(GTK_CONTAINER(visao_geral_grp_scroll),visao_geral_grp_box);

	gtk_widget_set_size_request(visao_geral_grp_scroll,450,225);
	gtk_container_add(GTK_CONTAINER(visao_geral_grp_frame),visao_geral_grp_scroll);
	gtk_fixed_put(GTK_FIXED(visao_geral_grp_fixed),visao_geral_grp_frame,400,20);

	add_subgrp_button = gtk_button_new_with_label("Subgrupos");
	add_subgrp_fixed = gtk_fixed_new();
	gtk_fixed_put(GTK_FIXED(add_subgrp_fixed),add_subgrp_button,50,30);

	opcoes_grp_box = gtk_box_new(0,0);
	opcoes_grp_frame = gtk_frame_new("Opções");
	opcoes_grp_fixed = gtk_fixed_new();

	confirma_grp_img = gtk_image_new_from_file(IMG_OK);
	confirma_grp_button = gtk_button_new_with_label("Confirmar");
	gtk_button_set_image(GTK_BUTTON(confirma_grp_button),confirma_grp_img);

	altera_grp_img = gtk_image_new_from_file(IMG_ALTER);
	altera_grp_button = gtk_button_new_with_label("Alterar");
	gtk_button_set_image(GTK_BUTTON(altera_grp_button),altera_grp_img);

	cancela_grp_img = gtk_image_new_from_file(IMG_CANCEL);
	cancela_grp_button = gtk_button_new_with_label("Cancelar");
	gtk_button_set_image(GTK_BUTTON(cancela_grp_button),cancela_grp_img);

	exclui_grp_img = gtk_image_new_from_file(IMG_EXCLUI);
	exclui_grp_button = gtk_button_new_with_label("Excluir");
	gtk_button_set_image(GTK_BUTTON(exclui_grp_button),exclui_grp_img);

	gtk_box_pack_start(GTK_BOX(opcoes_grp_box),confirma_grp_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_grp_box),altera_grp_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_grp_box),cancela_grp_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_grp_box),exclui_grp_button,0,0,5);
	gtk_container_add(GTK_CONTAINER(opcoes_grp_frame),opcoes_grp_box);
	gtk_fixed_put(GTK_FIXED(opcoes_grp_fixed),opcoes_grp_frame,100,330);

	layout_janela_grupo = gtk_layout_new(NULL,NULL);
	caixa_grande = gtk_box_new(1,0);

	gtk_box_pack_start(GTK_BOX(caixa_grande),cod_grupo_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),nome_grupo_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),add_subgrp_fixed,0,0,0);

	gtk_layout_put(GTK_LAYOUT(layout_janela_grupo),caixa_grande,0,0);
	gtk_layout_put(GTK_LAYOUT(layout_janela_grupo),visao_geral_grp_fixed,0,0);
	gtk_layout_put(GTK_LAYOUT(layout_janela_grupo),opcoes_grp_fixed,0,0);

	gtk_container_add(GTK_CONTAINER(janela_grupo),layout_janela_grupo);

	sprintf(code,"%i",tasker("grupos"));

	gtk_entry_set_text(GTK_ENTRY(cod_grp_entry),code);

	g_signal_connect(add_subgrp_button,"clicked",G_CALLBACK(cad_subgrupo),NULL);
	g_signal_connect(psq_grp_button,"clicked",G_CALLBACK(pesquisa_grp),cod_grp_entry);

	g_signal_connect(cod_grp_entry,"activate",G_CALLBACK(cod_grp),NULL);
	g_signal_connect(confirma_grp_button,"clicked",G_CALLBACK(conclui_grupo),NULL);
	g_signal_connect(altera_grp_button,"clicked",G_CALLBACK(altera_grupo),NULL);
	g_signal_connect(cancela_grp_button,"clicked",G_CALLBACK(cancela_grupo),NULL);
	g_signal_connect(exclui_grp_button,"clicked",G_CALLBACK(exclui_grupo),NULL);
	g_signal_connect(janela_grupo,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_CAD_GRP]);

	g_signal_connect(cad_grp_treeview,"row-activated",G_CALLBACK(enter_code_from_treeview),cod_grp_entry);

	gtk_widget_show_all(janela_grupo);
	return 0;
}
