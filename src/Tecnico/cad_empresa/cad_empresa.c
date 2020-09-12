#include "consultar.c"
#include "atualiza.c"

int cadastro_empresa(){
  GtkWidget *janela;
  GtkWidget *infos_colunas,
  *infos_linha1,*infos_linha2,
  *infos_linha3,*infos_linha4;
  GtkWidget *person_colunas,
  *person_linha1,*person_linha2,
  *person_linha3,*person_linha4;


  GtkWidget *cad_emp_nome_frame,
  *cad_emp_cpnj_frame,
  *cad_emp_logr_frame,
  *cad_emp_cep_frame,
  *cad_emp_bairro_frame,
  *cad_emp_cidade_frame,
  *cad_emp_uf_frame,
  *cad_emp_numrua_frame,
  *cad_emp_tiporua_frame,
  *cad_emp_telefone_frame,
  *cad_emp_celular_frame,
  *cad_emp_email_frame,
  *cad_emp_emailsenha_frame,
  *cad_emp_img_init_frame,
  *cad_emp_img_init_box,
  *cad_emp_script_path_frame,
  *cad_emp_script_path_box,
  *cad_emp_box;

  GtkWidget *cad_emp_nome_fixed,
  *cad_emp_cpnj_fixed,
  *cad_emp_logr_fixed,
  *cad_emp_cep_fixed,
  *cad_emp_bairro_fixed,
  *cad_emp_cidade_fixed,
  *cad_emp_uf_fixed,
  *cad_emp_numrua_fixed,
  *cad_emp_tiporua_fixed,
  *cad_emp_telefone_fixed,
  *cad_emp_celular_fixed,
  *cad_emp_email_fixed,
  *cad_emp_emailsenha_fixed,
  *cad_emp_img_init_fixed,
  *cad_emp_script_path_fixed;

  GtkWidget *cad_emp_frame;

  GtkWidget *opcoes_box,*opcoes_fixed,*atualizar_button;

  GtkWidget *box, *fixed;
  janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_title(GTK_WINDOW(janela),"Empresa");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"system-software-install");
  if(personalizacao.janela_keep_above==1)
    gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
  gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

  opcoes_box = gtk_box_new(0,0);
  opcoes_fixed = gtk_fixed_new();
  atualizar_button = gtk_button_new_with_label("Atualizar");
  gtk_box_pack_start(GTK_BOX(opcoes_box),atualizar_button,0,0,0);
  gtk_fixed_put(GTK_FIXED(opcoes_fixed),opcoes_box,20,20);

  cad_emp_notebook = gtk_notebook_new();
  infos_colunas = gtk_box_new(1,0);
  infos_linha1 = gtk_box_new(0,0);
  infos_linha2  = gtk_box_new(0,0);
  infos_linha3 = gtk_box_new(0,0);
  infos_linha4 = gtk_box_new(0,0);

  person_colunas = gtk_box_new(1,0);
  person_linha1 = gtk_box_new(0,0);
  person_linha2  = gtk_box_new(0,0);
  person_linha3 = gtk_box_new(0,0);
  person_linha4 = gtk_box_new(0,0);

  cad_emp_nome_fixed = gtk_fixed_new();
  cad_emp_cpnj_fixed = gtk_fixed_new();
  cad_emp_logr_fixed = gtk_fixed_new();
  cad_emp_cep_fixed = gtk_fixed_new();
  cad_emp_bairro_fixed = gtk_fixed_new();
  cad_emp_cidade_fixed = gtk_fixed_new();
  cad_emp_uf_fixed = gtk_fixed_new();
  cad_emp_numrua_fixed = gtk_fixed_new();
  cad_emp_tiporua_fixed = gtk_fixed_new();
  cad_emp_telefone_fixed = gtk_fixed_new();
  cad_emp_celular_fixed = gtk_fixed_new();
  cad_emp_email_fixed = gtk_fixed_new();
  cad_emp_emailsenha_fixed = gtk_fixed_new();

  cad_emp_script_path_box = gtk_box_new(0,0);
  cad_emp_script_path_fixed = gtk_fixed_new();

  cad_emp_nome_frame = gtk_frame_new("Nome:");
  cad_emp_cpnj_frame = gtk_frame_new("CNPJ:");
  cad_emp_logr_frame = gtk_frame_new("Logradouro:");
  cad_emp_frame = gtk_frame_new("Dados da Empresa:");
  cad_emp_cep_frame = gtk_frame_new("CEP:");
  cad_emp_bairro_frame = gtk_frame_new("Bairro");
  cad_emp_cidade_frame = gtk_frame_new("Cidade");
  cad_emp_uf_frame = gtk_frame_new("UF:");
  cad_emp_numrua_frame = gtk_frame_new("Número");
  cad_emp_tiporua_frame = gtk_frame_new("Tipo:");
  cad_emp_telefone_frame = gtk_frame_new("Telefone:");
  cad_emp_celular_frame = gtk_frame_new("Celular:");
  cad_emp_email_frame = gtk_frame_new("Email:");
  cad_emp_emailsenha_frame = gtk_frame_new("Senha:");
  cad_emp_script_path_frame = gtk_frame_new("Interpretador Scripts");
  cad_emp_box = gtk_box_new(1,0);

  cad_emp_nome_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_emp_nome_entry),25);
  cad_emp_cpnj_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_emp_cpnj_entry),30);
  cad_emp_logr_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_emp_logr_entry),40);
  cad_emp_cep_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_emp_cep_entry),20);
  cad_emp_bairro_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_emp_bairro_entry),25);
  cad_emp_cidade_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_emp_cidade_entry),20);
  cad_emp_uf_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_emp_uf_entry),5);
  cad_emp_numrua_spin = gtk_spin_button_new_with_range(1,10000,1);
  cad_emp_tiporua_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(cad_emp_tiporua_combo),0,("Tipo:"));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_emp_tiporua_combo),"1",(tip_logds[0]));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_emp_tiporua_combo),"2",(tip_logds[1]));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_emp_tiporua_combo),"3",(tip_logds[2]));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_emp_tiporua_combo),"4",(tip_logds[3]));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_emp_tiporua_combo),"5",(tip_logds[4]));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_emp_tiporua_combo),"6",(tip_logds[5]));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_emp_tiporua_combo),"7",(tip_logds[6]));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cad_emp_tiporua_combo),"8",("Outros"));
  gtk_combo_box_set_active(GTK_COMBO_BOX(cad_emp_tiporua_combo),1);
  cad_emp_telefone_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_emp_telefone_entry),10);
  cad_emp_celular_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_emp_celular_entry),10);
  cad_emp_email_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_emp_email_entry),20);
  cad_emp_emailsenha_entry = gtk_entry_new();
  gtk_entry_set_visibility(GTK_ENTRY(cad_emp_emailsenha_entry),FALSE);
  gtk_entry_set_width_chars(GTK_ENTRY(cad_emp_emailsenha_entry),10);

  cad_emp_script_path_entry = gtk_entry_new();
  cad_emp_script_path_chooser = gtk_file_chooser_button_new("Abrir",GTK_FILE_CHOOSER_ACTION_OPEN);
  gtk_entry_set_width_chars(GTK_ENTRY(cad_emp_script_path_entry),30);
  gtk_box_pack_start(GTK_BOX(cad_emp_script_path_box),cad_emp_script_path_entry,0,0,20);
  gtk_box_pack_start(GTK_BOX(cad_emp_script_path_box),cad_emp_script_path_chooser,0,0,20);
  gtk_container_add(GTK_CONTAINER(cad_emp_script_path_frame),cad_emp_script_path_box);
  gtk_fixed_put(GTK_FIXED(cad_emp_script_path_fixed),cad_emp_script_path_frame,20,20);

  gtk_container_add(GTK_CONTAINER(cad_emp_nome_frame),cad_emp_nome_entry);
  gtk_container_add(GTK_CONTAINER(cad_emp_cpnj_frame),cad_emp_cpnj_entry);
  gtk_container_add(GTK_CONTAINER(cad_emp_logr_frame),cad_emp_logr_entry);
  gtk_container_add(GTK_CONTAINER(cad_emp_cep_frame),cad_emp_cep_entry);
  gtk_container_add(GTK_CONTAINER(cad_emp_bairro_frame),cad_emp_bairro_entry);
  gtk_container_add(GTK_CONTAINER(cad_emp_cidade_frame),cad_emp_cidade_entry);
  gtk_container_add(GTK_CONTAINER(cad_emp_uf_frame),cad_emp_uf_entry);
  gtk_container_add(GTK_CONTAINER(cad_emp_numrua_frame),cad_emp_numrua_spin);
  gtk_container_add(GTK_CONTAINER(cad_emp_tiporua_frame),cad_emp_tiporua_combo);
  gtk_container_add(GTK_CONTAINER(cad_emp_telefone_frame),cad_emp_telefone_entry);
  gtk_container_add(GTK_CONTAINER(cad_emp_celular_frame),cad_emp_celular_entry);
  gtk_container_add(GTK_CONTAINER(cad_emp_email_frame),cad_emp_email_entry);
  gtk_container_add(GTK_CONTAINER(cad_emp_emailsenha_frame),cad_emp_emailsenha_entry);

  gtk_fixed_put(GTK_FIXED(cad_emp_nome_fixed),cad_emp_nome_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_emp_cpnj_fixed),cad_emp_cpnj_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_emp_logr_fixed),cad_emp_logr_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_emp_cep_fixed),cad_emp_cep_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_emp_bairro_fixed),cad_emp_bairro_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_emp_cidade_fixed),cad_emp_cidade_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_emp_uf_fixed),cad_emp_uf_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_emp_numrua_fixed),cad_emp_numrua_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_emp_tiporua_fixed),cad_emp_tiporua_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_emp_telefone_fixed),cad_emp_telefone_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_emp_celular_fixed),cad_emp_celular_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_emp_email_fixed),cad_emp_email_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_emp_emailsenha_fixed),cad_emp_emailsenha_frame,20,20);

  gtk_box_pack_start(GTK_BOX(infos_linha1),cad_emp_nome_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(infos_linha1),cad_emp_cpnj_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(infos_linha2),cad_emp_cep_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(infos_linha2),cad_emp_logr_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(infos_linha2),cad_emp_tiporua_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(infos_linha2),cad_emp_numrua_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(infos_linha3),cad_emp_cidade_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(infos_linha3),cad_emp_bairro_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(infos_linha3),cad_emp_uf_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(infos_linha4),cad_emp_telefone_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(infos_linha4),cad_emp_celular_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(infos_linha4),cad_emp_email_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(infos_linha4),cad_emp_emailsenha_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(infos_colunas),infos_linha1,0,0,0);
  gtk_box_pack_start(GTK_BOX(infos_colunas),infos_linha2,0,0,0);
  gtk_box_pack_start(GTK_BOX(infos_colunas),infos_linha3,0,0,0);
  gtk_box_pack_start(GTK_BOX(infos_colunas),infos_linha4,0,0,0);

  cad_emp_img_init_chooser = gtk_file_chooser_button_new("Abrir",GTK_FILE_CHOOSER_ACTION_OPEN);
  cad_emp_img_init_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_emp_img_init_entry),50);
  cad_emp_img_init_frame = gtk_frame_new("Caminho Imagem Inicial");
  cad_emp_img_init_fixed = gtk_fixed_new();
  cad_emp_img_init_box = gtk_box_new(0,0);

  gtk_box_pack_start(GTK_BOX(cad_emp_img_init_box),cad_emp_img_init_entry,0,0,5);
  gtk_box_pack_start(GTK_BOX(cad_emp_img_init_box),cad_emp_img_init_chooser,0,0,5);
  gtk_container_add(GTK_CONTAINER(cad_emp_img_init_frame),cad_emp_img_init_box);
  gtk_fixed_put(GTK_FIXED(cad_emp_img_init_fixed),cad_emp_img_init_frame,20,20);

  gtk_box_pack_start(GTK_BOX(person_linha1),cad_emp_img_init_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(person_linha2),cad_emp_script_path_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(person_colunas),person_linha1,0,0,0);
  gtk_box_pack_start(GTK_BOX(person_colunas),person_linha2,0,0,0);

  gtk_notebook_append_page(GTK_NOTEBOOK(cad_emp_notebook),infos_colunas,gtk_label_new("informações"));
  gtk_notebook_append_page(GTK_NOTEBOOK(cad_emp_notebook),person_colunas,gtk_label_new("Personalização"));

  gtk_box_pack_start(GTK_BOX(cad_emp_box),cad_emp_notebook,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_emp_box),opcoes_fixed,0,0,0);

  cad_emp_consulta();

  g_signal_connect(cad_emp_img_init_chooser,"file-set",G_CALLBACK(get_filename_to_entry),cad_emp_img_init_entry);
  g_signal_connect(cad_emp_script_path_chooser,"file-set",G_CALLBACK(get_filename_to_entry),cad_emp_script_path_entry);

  g_signal_connect(atualizar_button,"clicked",G_CALLBACK(cad_emp_atualiza),NULL);
  gtk_container_add(GTK_CONTAINER(janela),cad_emp_box);
  gtk_widget_show_all(janela);
  return 0;
}