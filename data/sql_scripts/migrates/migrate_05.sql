-- migrate criado com script migrate pedidos



ALTER TABLE cheque_finan DROP CONSTRAINT cheque_finan_ibfk_2;
ALTER TABLE parcelas_tab DROP CONSTRAINT parcelas_tab_ibfk_1;
ALTER TABLE titulos MODIFY code INT AUTO_INCREMENT;
ALTER TABLE parcelas_tab ADD CONSTRAINT parcelas_tab_ibfk_1 FOREIGN KEY (parcelas_id) REFERENCES titulos(code);
ALTER TABLE cheque_finan  ADD CONSTRAINT cheque_finan_ibfk_2 FOREIGN KEY (titulo) REFERENCES titulos(code);
ALTER TABLE titulos ADD CONSTRAINT titulos_ibfk_2 FOREIGN KEY (pedido) REFERENCES pedidos(code);
UPDATE terceiros t SET t.doc = CAST(t.doc AS UNSIGNED) where LENGTH(doc) > 0;

ALTER TABLE titulos MODIFY pedido INT NULL;

update versao set versao = '1.1.1.5', lancamento = '2021-07-09';
insert into migrate values(5, 'Versao 1.1.1.5', 'migrate_05.sql', '1.1.1.5', '2021-07-09');
