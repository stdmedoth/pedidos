CREATE TABLE IF NOT EXISTS `IcmsInterestadual` (
  `code` int(11) NOT NULL AUTO_INCREMENT,
  `origem` varchar(2) NOT NULL,
  `destino` varchar(2) NOT NULL,
  `icms` decimal(10,2) NOT NULL,
  PRIMARY KEY (`code`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=730 ;
