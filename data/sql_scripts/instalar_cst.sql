create table prod_origem(
  code int not null primary key,
  idOrigem int not null,
  nome varchar(200),
  aliquota float
);

create table cst_cson(
  code int not null primary key,
  charIdTrib varchar(3) not null,
  nome varchar(200),
  regime int not null
);

insert into prod_origem values(1,0,"Nacional, exceto as indicadas nos códigos 3, 4, 5 e 8	", 7);
insert into prod_origem values(2,1,"Estrangeira – Importação direta, exceto a indicada no código 6	", 4);
insert into prod_origem values(3,2,"Estrangeira – Adquirida no mercado interno, exceto a indicada no código 7	", 4);
insert into prod_origem values(4,3,"Nacional, Conteúdo de Import. superio a 40%, inferior ou igual a 70%", 4);
insert into prod_origem values(5,4,"Nacional, cuja prod. tenha sido feita em conformidade com os processos prod. básicos", 7);
insert into prod_origem values(6,5,"Nacional, Conteúdo de Import. inferior ou igual a 40% (quarenta por cento)", 7);
insert into prod_origem values(7,6,"Estrangeira – Importação direta, (Ver lista de Bens Sem Similar Nacional – LESSIN)", 7);
insert into prod_origem values(8,7,"Estrangeira – Adquirida no mercado interno(Ver lista de Bens Sem Similar Nac. – LESSIN)", 7);
insert into prod_origem values(9,8,"Nacional, Conteúdo de Importação superior a 70%", 4);


insert into cst_cson values(1,"00", "Tributada integralmente", 1);
insert into cst_cson values(2,"10", "Tributada e com cobrança do ICMS por substituição tributária", 1);
insert into cst_cson values(3,"20",  "Com redução de base de cálculo", 1);
insert into cst_cson values(4,"30", "Isenta ou não tributada e com cobrança do ICMS por substituição tributária", 1);
insert into cst_cson values(5,"40", "Isenta", 1);
insert into cst_cson values(6,"41", "Não tributada", 1);
insert into cst_cson values(7,"50", "Suspensão", 1);
insert into cst_cson values(8,"51", "Diferimento", 1);
insert into cst_cson values(9,"60", "ICMS cobrado anteriormente por substituição tributária", 1);
insert into cst_cson values(10,"70", "Com redução de base de cálculo e cobrança do ICMS por substituição tributária", 1);
insert into cst_cson values(11,"90", "Outras", 1);
