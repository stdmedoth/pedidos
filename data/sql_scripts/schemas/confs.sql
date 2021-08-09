create table if not exists confs(  code int primary key auto_increment,
  navegador_path1 varchar(1000) default '' not null,
  navegador_path2 varchar(1000) default '' not null,
  navegador_pdr int default 1 not null,
  imp_path1 varchar(1000) default '' not null,
  imp_path2 varchar(1000) default '' not null,
  imp_path3 varchar(1000) default '' not null,
  print_logs int not null default 0,
  bd_logs int not null default 0);
