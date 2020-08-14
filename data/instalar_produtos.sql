-- MySQL dump 10.13  Distrib 5.6.6-m9, for Win32 (x86)
--
-- Host: localhost    Database: erp
-- ------------------------------------------------------
-- Server version	5.6.6-m9-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `produtos`
--

DROP TABLE IF EXISTS `produtos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `produtos` (
  `code` int(11) NOT NULL AUTO_INCREMENT,
  `nome` varchar(150) DEFAULT 'Produto Sem Nome',
  `peso` float DEFAULT '0',
  `unidades` int(11) DEFAULT '1',
  `unidades_atacado` int(11) DEFAULT '1',
  `fornecedor` int(11) DEFAULT '1',
  `grupo` int(11) DEFAULT '1',
  `grupo_nivel` int(11) DEFAULT '2',
  `observacoes` varchar(500) DEFAULT '',
  PRIMARY KEY (`code`),
  KEY `unidades` (`unidades`),
  KEY `fornecedor` (`fornecedor`),
  KEY `grupo` (`grupo`),
  CONSTRAINT `produtos_ibfk_1` FOREIGN KEY (`unidades`) REFERENCES `unidades` (`code`),
  CONSTRAINT `produtos_ibfk_2` FOREIGN KEY (`fornecedor`) REFERENCES `terceiros` (`code`),
  CONSTRAINT `produtos_ibfk_3` FOREIGN KEY (`grupo`) REFERENCES `grupos` (`code`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `produtos`
--

LOCK TABLES `produtos` WRITE;
/*!40000 ALTER TABLE `produtos` DISABLE KEYS */;
INSERT INTO `produtos` VALUES (1,'Papelão',0,4,2,1,2,2,''),(2,'Percalux',0,3,3,1,7,2,''),(3,'Cabeceado',0,3,7,1,24,2,''),(4,'Cola',0,9,9,1,30,2,''),(5,'Linha',0,6,6,1,35,2,''),(6,'Papel Offset',0,7,7,1,46,2,'\n\n'),(7,'Película',0,6,6,1,52,3,'	'),(8,'Resistência',0,4,4,1,61,2,''),(9,'Espiral',0,7,7,1,64,2,'');
/*!40000 ALTER TABLE `produtos` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-07-19 17:51:46
