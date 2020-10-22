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
-- Table structure for table `preco_grupo`
--

DROP TABLE IF EXISTS `preco_grupo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `preco_grupo` (
  `code` int(11) NOT NULL AUTO_INCREMENT,
  `produto` int(11) DEFAULT '1',
  `grupo` int(11) DEFAULT '1',
  `valor_fat` float DEFAULT '0',
  `valor_vist` float DEFAULT '0',
  PRIMARY KEY (`code`),
  KEY `grupo` (`grupo`),
  CONSTRAINT `preco_grupo_ibfk_1` FOREIGN KEY (`grupo`) REFERENCES `grupos` (`code`)
) ENGINE=InnoDB AUTO_INCREMENT=44 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `preco_grupo`
--

LOCK TABLES `preco_grupo` WRITE;
/*!40000 ALTER TABLE `preco_grupo` DISABLE KEYS */;
INSERT INTO `preco_grupo` VALUES (1,10,3,138.5,0),(2,10,4,151.5,141.5),(3,10,5,86.5,81),(4,10,6,0,0),(5,1,3,131.5,131.5),(6,1,4,151.5,141.5),(7,1,5,86.5,81),(8,1,6,0,0),(9,2,9,9.14,8.7),(10,2,10,7.53,7.13),(11,2,11,9.14,8.7),(12,2,13,7.53,7.13),(13,2,14,9.14,8.7),(14,2,18,10.76,10.22),(15,2,21,10.76,10.22),(16,2,19,10.76,10.22),(17,2,22,10.76,10.22),(18,2,20,10.76,10.22),(19,2,23,10.76,10.22),(20,3,27,59,59),(21,3,28,81.5,81.5),(22,3,29,1.18,1.18),(23,3,25,59,59),(24,3,26,1.18,1.18),(25,4,32,22.5,22.5),(26,4,33,88.5,83),(27,4,34,157,149),(28,4,31,22.5,22.5),(29,5,38,39.5,39.5),(30,5,41,28.5,28.5),(31,5,44,15,15),(32,6,51,168.5,168.5),(33,7,54,69,69),(34,7,56,89.5,89.5),(35,7,59,119.5,119.5),(36,7,55,69,69),(37,7,57,89.5,89.5),(38,7,60,119,119),(39,7,62,62.5,62.5),(40,7,63,62.5,62.5),(41,9,65,12.5,12.5),(42,9,66,14,14),(43,9,67,16,16);
/*!40000 ALTER TABLE `preco_grupo` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-07-19 17:48:03
