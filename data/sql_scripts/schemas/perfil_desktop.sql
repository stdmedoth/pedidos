create table if not exists perfil_desktop(
  code int primary key auto_increment,
  desktop_img int default 0,
  tema int default 0,
  janela_init bool default 0,
  janelas_keep_above bool default 0);
