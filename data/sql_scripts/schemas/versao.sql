CREATE TABLE IF NOT EXISTS versao( code INT PRIMARY KEY AUTO_INCREMENT, versao VARCHAR(30) NOT NULL, lancamento DATETIME NOT NULL);

INSERT IGNORE INTO versao VALUES(1, '1.0', '2021-05-28');
