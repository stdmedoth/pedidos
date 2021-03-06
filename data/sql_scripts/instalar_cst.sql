insert into prod_origem values(1,0,"Nacional, exceto as indicadas nos códigos 3, 4, 5 e 8	", 7);
insert into prod_origem values(2,1,"Estrangeira – Importação direta, exceto a indicada no código 6	", 4);
insert into prod_origem values(3,2,"Estrangeira – Adquirida no mercado interno, exceto a indicada no código 7	", 4);
insert into prod_origem values(4,3,"Nacional, Conteúdo de Import. superio a 40%, inferior ou igual a 70%", 4);
insert into prod_origem values(5,4,"Nacional, cuja prod. tenha sido feita em conformidade com os processos prod. básicos", 7);
insert into prod_origem values(6,5,"Nacional, Conteúdo de Import. inferior ou igual a 40% (quarenta por cento)", 7);
insert into prod_origem values(7,6,"Estrangeira – Importação direta, (Ver lista de Bens Sem Similar Nacional – LESSIN)", 7);
insert into prod_origem values(8,7,"Estrangeira – Adquirida no mercado interno(Ver lista de Bens Sem Similar Nac. – LESSIN)", 7);
insert into prod_origem values(9,8,"Nacional, Conteúdo de Importação superior a 70%", 4);

insert into cst_cson values(1,"101", "Tributada pelo S.N. com perm. de créd.", 1);
insert into cst_cson values(2,"102", "Tributada pelo S.N. sem perm. de créd.", 1);
insert into cst_cson values(3,"103", "Isenção do ICMS no S.N. para faixa de receita bruta", 1);
insert into cst_cson values(4,"201", "Tributada pelo S.N. com perm. de créd. e com cobrança do ICMS por ST", 1);
insert into cst_cson values(5,"202", "Tributada pelo S.N. sem permissão de crédito e com cobrança do ICMS por ST", 1);
insert into cst_cson values(6,"203", "Isenção do ICMS no S.N. para faixa de receita bruta e com cobrança do ICMS por ST", 1);
insert into cst_cson values(7,"300", "Imune", 1);
insert into cst_cson values(8,"400", "Não tributada pelo S.N.", 1);
insert into cst_cson values(9,"500", "ICMS cobrado anteriormente por ST (substituído) ou por antecipação", 1);
insert into cst_cson values(10,"900", "Outros", 1);

insert into cst_cson values(11,"00", "Tributada integralmente", 3);
insert into cst_cson values(12,"10", "Tributada e com cobrança do ICMS por substituição tributária", 3);
insert into cst_cson values(13,"20",  "Com redução de base de cálculo", 3);
insert into cst_cson values(14,"30", "Isenta ou não tributada e com cobrança do ICMS por substituição tributária", 3);
insert into cst_cson values(15,"40", "Isenta", 3);
insert into cst_cson values(16,"41", "Não tributada", 3);
insert into cst_cson values(17,"50", "Suspensão", 3);
insert into cst_cson values(18,"51", "Diferimento", 3);
insert into cst_cson values(19,"60", "ICMS cobrado anteriormente por substituição tributária", 3);
insert into cst_cson values(20,"70", "Com redução de base de cálculo e cobrança do ICMS por substituição tributária", 3);
insert into cst_cson values(21,"90", "Outras", 3);
