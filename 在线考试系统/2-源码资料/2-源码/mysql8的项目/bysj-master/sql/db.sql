/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 80027
Source Host           : localhost:3306
Source Database       : db

Target Server Type    : MYSQL
Target Server Version : 80027
File Encoding         : 65001

Date: 2022-01-20 16:00:28
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `course`
-- ----------------------------
DROP TABLE IF EXISTS `course`;
CREATE TABLE `course` (
  `cno` int NOT NULL AUTO_INCREMENT,
  `cname` varchar(20) COLLATE utf8_danish_ci NOT NULL,
  PRIMARY KEY (`cno`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb3 COLLATE=utf8_danish_ci;

-- ----------------------------
-- Records of course
-- ----------------------------
INSERT INTO `course` VALUES ('1', '软件工程');
INSERT INTO `course` VALUES ('2', '软件测试');

-- ----------------------------
-- Table structure for `exam`
-- ----------------------------
DROP TABLE IF EXISTS `exam`;
CREATE TABLE `exam` (
  `eid` int NOT NULL AUTO_INCREMENT,
  `pname` varchar(20) COLLATE utf8_danish_ci NOT NULL,
  `cno` int NOT NULL,
  `userid` int NOT NULL,
  `classid` int NOT NULL,
  `singlenumber` int NOT NULL,
  `singlecore` int NOT NULL,
  `multiplenumber` int NOT NULL,
  `multiplecore` int NOT NULL,
  `examdate` date NOT NULL,
  `examtime` date NOT NULL,
  `testtime` int NOT NULL,
  PRIMARY KEY (`eid`),
  KEY `fk_relationship_2` (`userid`),
  KEY `fk_relationship_3` (`classid`),
  KEY `fk_relationship_4` (`cno`),
  CONSTRAINT `fk_relationship_2` FOREIGN KEY (`userid`) REFERENCES `users` (`userid`),
  CONSTRAINT `fk_relationship_3` FOREIGN KEY (`classid`) REFERENCES `pjclass` (`classid`),
  CONSTRAINT `fk_relationship_4` FOREIGN KEY (`cno`) REFERENCES `course` (`cno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8_danish_ci;

-- ----------------------------
-- Records of exam
-- ----------------------------

-- ----------------------------
-- Table structure for `paper`
-- ----------------------------
DROP TABLE IF EXISTS `paper`;
CREATE TABLE `paper` (
  `pid` int NOT NULL AUTO_INCREMENT,
  `eid` int NOT NULL,
  `sid` int NOT NULL,
  `cno` int NOT NULL,
  `stype` int NOT NULL,
  `scontent` varchar(255) COLLATE utf8_danish_ci NOT NULL,
  `sa` varchar(255) COLLATE utf8_danish_ci NOT NULL,
  `sb` varchar(255) COLLATE utf8_danish_ci NOT NULL,
  `sc` varchar(255) COLLATE utf8_danish_ci NOT NULL,
  `sd` varchar(255) COLLATE utf8_danish_ci NOT NULL,
  `skey` varchar(255) COLLATE utf8_danish_ci NOT NULL,
  PRIMARY KEY (`pid`),
  KEY `fk_relationship_13` (`eid`),
  KEY `fk_relationship_14` (`sid`),
  CONSTRAINT `fk_relationship_13` FOREIGN KEY (`eid`) REFERENCES `exam` (`eid`),
  CONSTRAINT `fk_relationship_14` FOREIGN KEY (`sid`) REFERENCES `subject` (`sid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8_danish_ci;

-- ----------------------------
-- Records of paper
-- ----------------------------

-- ----------------------------
-- Table structure for `pjclass`
-- ----------------------------
DROP TABLE IF EXISTS `pjclass`;
CREATE TABLE `pjclass` (
  `classid` int NOT NULL AUTO_INCREMENT,
  `classname` varchar(20) COLLATE utf8_danish_ci DEFAULT NULL,
  PRIMARY KEY (`classid`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb3 COLLATE=utf8_danish_ci;

-- ----------------------------
-- Records of pjclass
-- ----------------------------
INSERT INTO `pjclass` VALUES ('1', '软件17-1');
INSERT INTO `pjclass` VALUES ('2', '软件17-2');
INSERT INTO `pjclass` VALUES ('3', '计网17-1');
INSERT INTO `pjclass` VALUES ('4', '无');

-- ----------------------------
-- Table structure for `role`
-- ----------------------------
DROP TABLE IF EXISTS `role`;
CREATE TABLE `role` (
  `roleid` int NOT NULL AUTO_INCREMENT,
  `rolename` varchar(20) COLLATE utf8_danish_ci DEFAULT NULL,
  PRIMARY KEY (`roleid`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb3 COLLATE=utf8_danish_ci;

-- ----------------------------
-- Records of role
-- ----------------------------
INSERT INTO `role` VALUES ('1', '老师');
INSERT INTO `role` VALUES ('2', '学生');
INSERT INTO `role` VALUES ('3', '管理员');

-- ----------------------------
-- Table structure for `studentexam`
-- ----------------------------
DROP TABLE IF EXISTS `studentexam`;
CREATE TABLE `studentexam` (
  `seid` int NOT NULL AUTO_INCREMENT,
  `userid` int NOT NULL,
  `classid` int NOT NULL,
  `eid` int NOT NULL,
  `pname` varchar(20) COLLATE utf8_danish_ci NOT NULL,
  `zscore` int NOT NULL,
  `score` int NOT NULL,
  `tjtime` datetime NOT NULL,
  PRIMARY KEY (`seid`),
  KEY `fk_relationship_6` (`userid`),
  KEY `fk_relationship_7` (`classid`),
  KEY `fk_relationship_8` (`eid`),
  CONSTRAINT `fk_relationship_6` FOREIGN KEY (`userid`) REFERENCES `users` (`userid`),
  CONSTRAINT `fk_relationship_7` FOREIGN KEY (`classid`) REFERENCES `pjclass` (`classid`),
  CONSTRAINT `fk_relationship_8` FOREIGN KEY (`eid`) REFERENCES `exam` (`eid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8_danish_ci;

-- ----------------------------
-- Records of studentexam
-- ----------------------------

-- ----------------------------
-- Table structure for `studentsubject`
-- ----------------------------
DROP TABLE IF EXISTS `studentsubject`;
CREATE TABLE `studentsubject` (
  `ssid` int NOT NULL AUTO_INCREMENT,
  `seid` int NOT NULL,
  `userid` int NOT NULL,
  `eid` int NOT NULL,
  `sid` int NOT NULL,
  `studentkey` varchar(10) COLLATE utf8_danish_ci NOT NULL,
  PRIMARY KEY (`ssid`),
  KEY `fk_relationship_9` (`seid`),
  KEY `fk_relationship_10` (`userid`),
  KEY `fk_relationship_11` (`eid`),
  KEY `fk_relationship_12` (`sid`),
  CONSTRAINT `fk_relationship_10` FOREIGN KEY (`userid`) REFERENCES `users` (`userid`),
  CONSTRAINT `fk_relationship_11` FOREIGN KEY (`eid`) REFERENCES `exam` (`eid`),
  CONSTRAINT `fk_relationship_12` FOREIGN KEY (`sid`) REFERENCES `subject` (`sid`),
  CONSTRAINT `fk_relationship_9` FOREIGN KEY (`seid`) REFERENCES `studentexam` (`seid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8_danish_ci;

-- ----------------------------
-- Records of studentsubject
-- ----------------------------

-- ----------------------------
-- Table structure for `subject`
-- ----------------------------
DROP TABLE IF EXISTS `subject`;
CREATE TABLE `subject` (
  `sid` int NOT NULL AUTO_INCREMENT,
  `cno` int NOT NULL,
  `stype` int NOT NULL,
  `scontent` varchar(255) COLLATE utf8_danish_ci NOT NULL,
  `sa` varchar(255) COLLATE utf8_danish_ci NOT NULL,
  `sb` varchar(255) COLLATE utf8_danish_ci NOT NULL,
  `sc` varchar(255) COLLATE utf8_danish_ci NOT NULL,
  `sd` varchar(255) COLLATE utf8_danish_ci NOT NULL,
  `skey` varchar(255) COLLATE utf8_danish_ci NOT NULL,
  PRIMARY KEY (`sid`),
  UNIQUE KEY `scontent` (`scontent`),
  KEY `fk_relationship_5` (`cno`),
  CONSTRAINT `fk_relationship_5` FOREIGN KEY (`cno`) REFERENCES `course` (`cno`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb3 COLLATE=utf8_danish_ci;

-- ----------------------------
-- Records of subject
-- ----------------------------
INSERT INTO `subject` VALUES ('1', '2', '1', '软件测试的目的是(___)', '试验性运行软件', '发现软件错误', '证明软件正确', '找出软件中全部错误', 'B');
INSERT INTO `subject` VALUES ('2', '2', '1', '在一个长度为n的顺序表的表尾插入一个新元素的渐进时间复杂度为', 'O (n)', 'O (1)', 'O (n2 )', 'O (log2 n)', 'A');
INSERT INTO `subject` VALUES ('3', '1', '1', '计算机系统中的存贮器系统是指', 'RAM存贮器', 'ROM存贮器', '主存贮器', 'cache、主存贮器和外存贮器', 'D');
INSERT INTO `subject` VALUES ('4', '1', '1', '某机字长32位，其中1位符号位，31位表示尾数。若用定点小数表示，则最大正小数为', '+（1 – 2-32）', '+（1 – 2-31）', '2-32', '2-31', 'B');
INSERT INTO `subject` VALUES ('5', '1', '1', '算术 / 逻辑运算单元74181ALU可完成', '16种算术运算功能', '16种逻辑运算功能', '16种算术运算功能和16种逻辑运算功能', '4位乘法运算和除法运算功能', 'C');
INSERT INTO `subject` VALUES ('6', '1', '1', '存储单元是指', '存放一个二进制信息位的存贮元', '存放一个机器字的所有存贮元集合', '存放一个字节的所有存贮元集合', '存放两个字节的所有存贮元集合；', 'B');

-- ----------------------------
-- Table structure for `type`
-- ----------------------------
DROP TABLE IF EXISTS `type`;
CREATE TABLE `type` (
  `stype` int NOT NULL AUTO_INCREMENT,
  `name` varchar(30) COLLATE utf8_danish_ci NOT NULL,
  PRIMARY KEY (`stype`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb3 COLLATE=utf8_danish_ci;

-- ----------------------------
-- Records of type
-- ----------------------------
INSERT INTO `type` VALUES ('1', '一，单选题');
INSERT INTO `type` VALUES ('2', '二，多选题');

-- ----------------------------
-- Table structure for `users`
-- ----------------------------
DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `userid` int NOT NULL AUTO_INCREMENT,
  `roleid` int DEFAULT NULL,
  `username` varchar(20) COLLATE utf8_danish_ci DEFAULT NULL,
  `userpwd` varchar(20) COLLATE utf8_danish_ci DEFAULT NULL,
  `truename` varchar(30) COLLATE utf8_danish_ci DEFAULT NULL,
  `classid` int DEFAULT NULL,
  PRIMARY KEY (`userid`),
  UNIQUE KEY `username` (`username`),
  KEY `fk_relationship_1` (`roleid`),
  CONSTRAINT `fk_relationship_1` FOREIGN KEY (`roleid`) REFERENCES `role` (`roleid`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb3 COLLATE=utf8_danish_ci;

-- ----------------------------
-- Records of users
-- ----------------------------
INSERT INTO `users` VALUES ('1', '3', 'admin', '12345', '管理员', '1');
INSERT INTO `users` VALUES ('2', '1', 'rj0001', '12345', '王林', '1');
INSERT INTO `users` VALUES ('3', '2', '17510001', '11111', '张三丰', '1');
INSERT INTO `users` VALUES ('4', '2', '17510002', '12345', '李四', '2');
INSERT INTO `users` VALUES ('5', '2', '17510003', '12345', '王五', '1');
