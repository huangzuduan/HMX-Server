-- --------------------------------------------------------
-- 主机:                           127.0.0.1
-- 服务器版本:                        10.0.20-MariaDB - mariadb.org binary distribution
-- 服务器操作系统:                      Win64
-- HeidiSQL 版本:                  9.1.0.4867
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- 导出 stock_data 的数据库结构
CREATE DATABASE IF NOT EXISTS `stock_data` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `stock_data`;


-- 导出  表 stock_data.stock_info 结构
DROP TABLE IF EXISTS `stock_info`;
CREATE TABLE IF NOT EXISTS `stock_info` (
  `stockid` char(50) NOT NULL,
  `name` char(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='股票的基本信息';

-- 正在导出表  stock_data.stock_info 的数据：~0 rows (大约)
DELETE FROM `stock_info`;
/*!40000 ALTER TABLE `stock_info` DISABLE KEYS */;
/*!40000 ALTER TABLE `stock_info` ENABLE KEYS */;


-- 导出  表 stock_data.stock_minute 结构
DROP TABLE IF EXISTS `stock_minute`;
CREATE TABLE IF NOT EXISTS `stock_minute` (
  `idx` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `stockid` char(50) NOT NULL,
  `onprice` float NOT NULL,
  `offprice` float NOT NULL,
  `curprice` float NOT NULL,
  `topprice` float NOT NULL,
  `lowprice` float NOT NULL,
  `buyprice` float NOT NULL,
  `sellprice` float NOT NULL,
  `dealnum` int(11) NOT NULL,
  `dealmoney` int(11) NOT NULL,
  `buy1num` int(11) NOT NULL,
  `buy1price` float NOT NULL,
  `buy2num` int(11) NOT NULL,
  `buy2price` float NOT NULL,
  `buy3num` int(11) NOT NULL,
  `buy3price` float NOT NULL,
  `buy4num` int(11) NOT NULL,
  `buy4price` float NOT NULL,
  `buy5num` int(11) NOT NULL,
  `buy5price` float NOT NULL,
  `sell1num` int(11) NOT NULL,
  `sell1price` float NOT NULL,
  `sell2num` int(11) NOT NULL,
  `sell2price` float NOT NULL,
  `sell3num` int(11) NOT NULL,
  `sell3price` float NOT NULL,
  `sell4num` int(11) NOT NULL,
  `sell4price` float NOT NULL,
  `sell5num` int(11) NOT NULL,
  `sell5price` float NOT NULL,
  `date` char(50) NOT NULL,
  `time` char(50) NOT NULL,
  PRIMARY KEY (`idx`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COMMENT='每天时刻信息记录\r\n';

-- 正在导出表  stock_data.stock_minute 的数据：~1 rows (大约)
DELETE FROM `stock_minute`;
/*!40000 ALTER TABLE `stock_minute` DISABLE KEYS */;
INSERT INTO `stock_minute` (`idx`, `stockid`, `onprice`, `offprice`, `curprice`, `topprice`, `lowprice`, `buyprice`, `sellprice`, `dealnum`, `dealmoney`, `buy1num`, `buy1price`, `buy2num`, `buy2price`, `buy3num`, `buy3price`, `buy4num`, `buy4price`, `buy5num`, `buy5price`, `sell1num`, `sell1price`, `sell2num`, `sell2price`, `sell3num`, `sell3price`, `sell4num`, `sell4price`, `sell5num`, `sell5price`, `date`, `time`) VALUES
	(1, '601006', 8.71, 8.74, 8.62, 8.74, 8.61, 8.64, 8.65, 0, 0, 0, 8.64, 0, 8.63, 0, 8.62, 0, 8.61, 0, 8.6, 0, 8.65, 0, 8.66, 0, 8.67, 0, 8.68, 0, 8.69, '2015-12-31', '15:00:00');
/*!40000 ALTER TABLE `stock_minute` ENABLE KEYS */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
