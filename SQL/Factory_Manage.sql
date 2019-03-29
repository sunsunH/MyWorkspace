--建表
USE 销售管理
GO
CREATE TABLE 供应商
(供应商编号 INT PRIMARY KEY,
供应商名称 VARCHAR(20) NOT NULL,
联系电话 VARCHAR(13) NOT NULL,
地址 VARCHAR(20))

CREATE TABLE 产品
(产品编号 INT PRIMARY KEY,
产品名称 VARCHAR(20) NOT NULL,
单价 DECIMAL(8,2) CHECK(单价>0),
库存量 INT CHECK(库存量>=0))

CREATE TABLE 客户
(客户编号 INT PRIMARY KEY,
客户名称 VARCHAR(20) NOT NULL,
联系电话 VARCHAR(13) NOT NULL,
地址 VARCHAR(20))

CREATE TABLE 员工
(员工编号 INT PRIMARY KEY,
姓名 VARCHAR(10) NOT NULL,
工资 DECIMAL(8,2) CHECK(工资 BETWEEN 1800 AND 100000),
联系电话 VARCHAR(13) NOT NULL,
地址 VARCHAR(20))

CREATE TABLE 订单
(订单编号 INT PRIMARY KEY,
客户编号 INT NOT NULL,
员工编号 INT NOT NULL,
日期 DATE,
FOREIGN KEY (客户编号) REFERENCES 客户 (客户编号),
FOREIGN KEY (员工编号) REFERENCES 员工 (员工编号))

CREATE TABLE 供应
(供应编号 INT PRIMARY KEY,
供应商编号 INT,
产品编号 INT,
供应数量 INT NOT NULL,
FOREIGN KEY (供应商编号) REFERENCES 供应商 (供应商编号),
FOREIGN KEY (产品编号) REFERENCES 产品 (产品编号))

CREATE TABLE 订购
(订单编号 INT,
产品编号 INT,
订购数量 INT NOT NULL,
PRIMARY KEY(订单编号,产品编号),
FOREIGN KEY (订单编号) REFERENCES 订单 (订单编号),
FOREIGN KEY (产品编号) REFERENCES 产品 (产品编号))

--插入数据
INSERT INTO 供应商 VALUES(1,'上海卷笔刀有限公司','0577-88335572','上海')
INSERT INTO 供应商 VALUES(2,'深圳科技有限公司','0577-89574833','深圳')
INSERT INTO 供应商 VALUES(3,'温州软件有限公司','0589-54815618','温州')
INSERT INTO 供应商 VALUES(4,'南京材料有限公司','0895-45621205','南京')
INSERT INTO 供应商 VALUES(5,'佛山装饰有限公司','0456-77895630','佛山')
INSERT INTO 供应商 VALUES(6,'宁波服饰有限公司','0158-56893256','宁波')
SELECT *FROM 供应商

INSERT INTO 产品 VALUES(1,'路由器',120.00,100)
INSERT INTO 产品 VALUES(2,'打印纸',10.00,200)
INSERT INTO 产品 VALUES(3,'卷笔刀',3.00,300)
INSERT INTO 产品 VALUES(4,'爆米花',5.00,600)
INSERT INTO 产品 VALUES(5,'菜刀',30.00,300)
INSERT INTO 产品 VALUES(6,'牛仔裤',130.00,100)
INSERT INTO 产品 VALUES(7,'薯脆',3.00,1000)
SELECT *FROM 产品

INSERT INTO 客户 VALUES(1,'湖南实业有限公司','0868-85463951','湖南')
INSERT INTO 客户 VALUES(2,'中国移动有限公司','0896-84569853','北京')
INSERT INTO 客户 VALUES(3,'中国电信有限公司','0456-78952649','河北')
INSERT INTO 客户 VALUES(4,'中国联通有限公司','0589-78953295','河南')
INSERT INTO 客户 VALUES(5,'天津文化有限公司','0458-78563459','天津')
INSERT INTO 客户 VALUES(6,'青岛智能有限公司','0589-45896321','青岛')
SELECT *FROM 客户

INSERT INTO 员工 VALUES(1,'张三',3000.50,'16945895639','湖南')
INSERT INTO 员工 VALUES(2,'王五',3500.50,'15989453695','湖北')
INSERT INTO 员工 VALUES(3,'李四',3900.00,'17658963245','江西')
INSERT INTO 员工 VALUES(4,'小明',3100.00,'18952479853','北京')
INSERT INTO 员工 VALUES(5,'小红',3200.50,'17789632456','广州')
INSERT INTO 员工 VALUES(6,'小智',3900.00,'15745862159','沈阳')
INSERT INTO 员工 VALUES(7,'韩梅梅',2200.00,'12345678985','美国')
SELECT *FROM 员工

INSERT INTO 订单 VALUES(1,2,1,'2016-03-08')
INSERT INTO 订单 VALUES(2,3,4,'2017-06-06')
SELECT *FROM 订单

INSERT INTO 供应 VALUES(1,1,2,300)
INSERT INTO 供应 VALUES(2,2,1,600)
INSERT INTO 供应 VALUES(3,3,3,700)
INSERT INTO 供应 VALUES(4,1,1,700)
SELECT *FROM 供应

INSERT INTO 订购 VALUES(1,1,20)
INSERT INTO 订购 VALUES(1,2,10)
INSERT INTO 订购 VALUES(1,3,30)
INSERT INTO 订购 VALUES(2,1,30)
INSERT INTO 订购 VALUES(2,3,60)
INSERT INTO 订购 VALUES(2,6,90)
SELECT *FROM 订购
	

--订单数视图
CREATE VIEW VIEW_订单(客户编号,订单总数)
AS
SELECT 客户编号,COUNT(订单编号)
FROM 订单
GROUP BY 客户编号;
SELECT *FROM VIEW_订单

--产品数视图
CREATE VIEW VIEW_产品(产品编号,产品总数)
AS
SELECT 产品编号,SUM(订购数量)
FROM 订购
GROUP BY 产品编号;
SELECT *FROM VIEW_产品

--订单明细视图
CREATE VIEW VIEW_订单明细(订单编号,客户编号,员工编号,产品编号,订购数量,日期,总额)  
AS
SELECT 
订单.订单编号,客户.客户编号,员工.员工编号,产品.产品编号,订购.订购数量,订单.日期,单价*订购数量 AS 总额 
FROM 订单,订购,产品,客户,员工
WHERE 
订单.订单编号=订购.订单编号 AND 客户.客户编号=订单.客户编号 AND 员工.员工编号=订单.员工编号 AND 产品.产品编号=订购.产品编号 
SELECT *FROM VIEW_订单明细

--查询订单明细视图
CREATE PROCEDURE PRO_VIEW_订单明细
--@订单编号 INT
AS
SELECT *
FROM VIEW_订单明细
--WHERE 订单编号=@订单编号
EXEC PRO_VIEW_订单明细

--查询订单量最多的客户或者产品
CREATE PROCEDURE PRO_SELECT_MAX_订单
AS
SELECT *
FROM 客户
WHERE 客户编号 IN
(SELECT 客户编号 FROM VIEW_订单
WHERE 订单总数 IN
(SELECT MAX(订单总数)FROM VIEW_订单))
CREATE PROCEDURE PRO_SELECT_MAX_订单
AS
SELECT 客户编号,订单总数 
FROM  VIEW_订单  
where 订单总数>=ALL(SELECT 订单总数 FROM VIEW_订单)

CREATE PROCEDURE PRO_SELECT_MAX_产品
AS
SELECT 产品编号,产品总数 
FROM VIEW_产品
WHERE 产品总数>=ALL(SELECT 产品总数 FROM VIEW_产品)
EXEC PRO_SELECT_MAX_产品

--存储过程

--存储查询插入供应商信息
CREATE PROCEDURE PRO_INSERT_供应商
@供应商编号 INT,
@供应商名称 VARCHAR(20),
@联系电话 CHAR(13),
@地址 VARCHAR(20)
AS
IF EXISTS
(SELECT *
FROM 供应商
WHERE 供应商编号=@供应商编号)
PRINT '该供应商记录已经存在'
ELSE
INSERT INTO 供应商(供应商编号,供应商名称,联系电话,地址)
VALUES(@供应商编号,@供应商名称,@联系电话,@地址)
EXEC PRO_INSERT_供应商 9,'沃尔玛','18774871311','美国';

--插入产品信息
CREATE PROCEDURE PRO_INSERT_产品
@产品编号 INT,
@产品名称 VARCHAR(20),
@单价 DECIMAL(8,2),
@库存量 INT
AS
IF EXISTS
(SELECT *
FROM 产品
WHERE 产品编号=@产品编号)
PRINT '该产品记录已经存在'
ELSE
INSERT INTO 产品(产品编号,产品名称,单价,库存量)
VALUES(@产品编号,@产品名称,@单价,@库存量)

--客户信息
CREATE PROCEDURE PRO_INSERT_客户
@客户编号 INT,
@客户名称 VARCHAR(20),
@联系电话 CHAR(13),
@地址 VARCHAR(20)
AS
IF EXISTS
(SELECT *
FROM 客户
WHERE 客户编号=@客户编号)
PRINT '该客户记录已经存在'
ELSE
INSERT INTO 客户(客户编号,客户名称,联系电话,地址)
VALUES(@客户编号,@客户名称,@联系电话,@地址)

--插入员工信息
CREATE PROCEDURE PRO_INSERT_员工
@员工编号 INT,
@姓名 VARCHAR(20),
@工资 DECIMAL(9,2),
@联系电话 CHAR(13),
@地址 VARCHAR(20)
AS
IF EXISTS
(SELECT *
FROM 员工
WHERE 员工编号=@员工编号)
PRINT '该员工记录已经存在'
ELSE
INSERT INTO 员工(员工编号,姓名,工资,联系电话,地址)
VALUES(@员工编号,@姓名,@工资,@联系电话,@地址)

--插入订单信息
CREATE PROCEDURE PRO_INSERT_订单
@订单编号 INT,
@客户编号 INT,
@员工编号 INT,
@日期 DATE
AS
IF EXISTS
(SELECT *
FROM 订单
WHERE 订单编号=@订单编号)
PRINT '该订单信息已存在'
ELSE
INSERT INTO 订单(订单编号,客户编号,员工编号,日期)
VALUES(@订单编号,@客户编号,@员工编号,@日期)


--插入供应信息
CREATE PROCEDURE PRO_INSERT_供应
@供应编号 INT,
@供应商编号 INT,
@产品编号 INT,
@供应数量 INT
AS
SELECT *
FROM 供应
WHERE 供应编号=@供应编号
INSERT INTO 供应(供应编号,供应商编号,产品编号,供应数量)
VALUES(@供应编号,@供应商编号,@产品编号,@供应数量)

--插入订购信息
CREATE PROCEDURE PRO_INSERT_订购
@订单编号 INT,
@产品编号 INT,
@订购数量 INT
AS
SELECT *
FROM 订购
WHERE 订单编号=@订单编号 AND 产品编号=@产品编号
INSERT INTO 订购(订单编号,产品编号,订购数量)
VALUES(@订单编号,@产品编号,@订购数量)


--存储删除插入供应商信息的操作
CREATE PROCEDURE PRO_DELETE_供应商
@供应商编号 INT
AS
if EXISTS
(SELECT * 
FROM 供应商 
WHERE 供应商编号=@供应商编号)
DELETE FROM 供应商
WHERE 供应商编号=@供应商编号 
ELSE
PRINT '该供应商不存在'

--删除产品信息
CREATE PROCEDURE PRO_DELETE_产品
@产品编号 INT
AS
if EXISTS
(SELECT * 
FROM 产品 
WHERE 产品编号=@产品编号)
DELETE FROM 产品
WHERE 产品编号=@产品编号 
ELSE
PRINT '该产品不存在'

--删除客户信息
CREATE PROCEDURE PRO_DELETE_客户
@客户编号 INT
AS
if EXISTS
(SELECT * 
FROM 客户 
WHERE 客户编号=@客户编号)
DELETE FROM 供应商
WHERE 客户编号=@客户编号 
ELSE
PRINT '该客户不存在'

--删除员工信息
CREATE PROCEDURE PRO_DELETE_员工
@员工编号 INT
AS
if EXISTS
(SELECT * 
FROM 员工 
WHERE 员工编号=@员工编号)
DELETE FROM 员工
WHERE 员工编号=@员工编号 
ELSE
PRINT '该员工不存在'

--删除订单信息
CREATE PROCEDURE PRO_DELETE_订单
@订单编号 INT
AS
if EXISTS
(SELECT * 
FROM 订单 
WHERE 订单编号=@订单编号)
DELETE FROM 订单
WHERE 订单编号=@订单编号 
ELSE
PRINT '该订单不存在'

--删除供应信息
CREATE PROCEDURE PRO_DELETE_供应
@供应编号 INT
AS
if EXISTS
(SELECT * 
FROM 供应 
WHERE 供应编号=@供应编号)
DELETE FROM 供应
WHERE 供应编号=@供应编号 
ELSE
PRINT '此次供应不存在'

--删除订购信息
CREATE PROCEDURE PRO_DELETE_订购
@订单编号 INT,
@产品编号 INT
AS
if EXISTS
(SELECT * 
FROM 订购 
WHERE 订单编号=@订单编号 AND 产品编号=@产品编号)
DELETE FROM 订购
WHERE 订单编号=@订单编号 AND 产品编号=@产品编号 
ELSE
PRINT '此次订购不存在'


--存储更新供应商信息的操作
CREATE PROCEDURE PRO_UPDATE_供应商 
@供应商编号 INT, 
@供应商名称 VARCHAR(20), 
@联系电话 CHAR(13),
@地址 VARCHAR(20) 
AS
IF EXISTS
(SELECT * 
FROM 供应商 
WHERE 供应商编号=@供应商编号)
UPDATE 供应商 
SET 供应商名称=@供应商名称,  
联系电话=@联系电话, 
地址=@地址 
WHERE 供应商编号=@供应商编号 
ELSE
PRINT '无此供应商信息!'

--更新产品信息
CREATE PROCEDURE PRO_UPDATE_产品 
@产品编号 INT, 
@产品名称 VARCHAR(20), 
@单价 DECIMAL(8,2),
@库存量 INT 
AS
IF EXISTS
(SELECT * 
FROM 产品 
WHERE 产品编号=@产品编号)
UPDATE 产品 
SET 产品名称=@产品名称,  
单价=@单价, 
库存量=@库存量 
WHERE 产品编号=@产品编号 
ELSE
PRINT '无此产品信息!'

--更新客户信息
CREATE PROCEDURE PRO_UPDATE_客户 
@客户编号 INT, 
@客户名称 VARCHAR(20), 
@联系电话 CHAR(13),
@地址 VARCHAR(20) 
AS
IF EXISTS
(SELECT * 
FROM 客户 
WHERE 客户编号=@客户编号)
UPDATE 客户 
SET 客户名称=@客户名称,  
联系电话=@联系电话, 
地址=@地址 
WHERE 客户编号=@客户编号 
ELSE
PRINT '无此客户信息!'

--更新员工信息
CREATE PROCEDURE PRO_UPDATE_员工 
@员工编号 INT, 
@姓名 CHAR(10), 
@工资 DECIMAL(9,2), 
@联系电话 CHAR(13),
@地址 VARCHAR(20) 
AS
IF EXISTS
(SELECT * 
FROM 员工 
WHERE 员工编号=@员工编号)
UPDATE 员工 
SET 姓名=@姓名, 
工资=@工资, 
联系电话=@联系电话, 
地址=@地址 
WHERE 员工编号=@员工编号 
ELSE
PRINT '无此员工信息!'
EXEC PRO_UPDATE_员工 1,'小明',6000,'10023564789','北极';

--更新订单信息
/*CREATE PROCEDURE PRO_UPDATE_订单
@订单编号INT,
@客户编号INT, 
@员工编号INT,
@日期DATE
AS
IF EXISTS
(SELECT * 
FROM 订单
WHERE 订单编号=@订单编号)
UPDATE 订单
SET 客户编号=@客户编号,
员工编号=@员工编号,
日期=@日期
WHERE 订单编号=@订单编号
ELSE
PRINT '无此订单信息!'

--更新供应信息
CREATE PROCEDURE PRO_UPDATE_供应
@供应编号INT,
@供应商编号INT, 
@产品编号INT, 
@供应数量INT
AS
IF EXISTS
(SELECT * 
FROM 供应
WHERE 供应编号=@供应编号)
UPDATE 供应
SET 供应商编号=@供应商编号,
产品编号=@产品编号,
供应数量=@供应数量
WHERE 供应编号=@供应编号
ELSE
PRINT '无此供应信息!'

--更新订购信息
CREATE PROCEDURE PRO_UPDATE_订购
@订单编号INT, 
@产品编号INT, 
@订购数量INT
AS
IF EXISTS
(SELECT * 
FROM 订购
WHERE 订单编号=@订单编号AND 产品编号=@产品编号)
UPDATE 订购
SET 订购数量=@订购数量
WHERE 订单编号=@订单编号 AND 产品编号=@产品编号
ELSE
PRINT '无此订购信息!'*/ 


--存储查询供应商信息的操作
CREATE PROCEDURE PRO_SELECT_供应商
@供应商编号 INT
AS
SELECT *
FROM 供应商
WHERE 供应商编号=@供应商编号
EXEC PRO_SELECT_供应商 3;

--查询产品信息
CREATE PROCEDURE PRO_SELECT_产品
@产品编号 INT
AS
SELECT *
FROM 产品
WHERE 产品编号=@产品编号

--查询客户信息
CREATE PROCEDURE PRO_SELECT_客户
@客户编号 INT
AS
SELECT *
FROM 客户
WHERE 客户编号=@客户编号

--查询员工信息
CREATE PROCEDURE PRO_SELECT_员工
@员工编号 INT
AS
SELECT *
FROM 员工
WHERE 员工编号=@员工编号

--查询订单信息
CREATE PROCEDURE PRO_SELECT_订单
@订单编号 INT
AS
SELECT *
FROM 订单
WHERE 订单编号=@订单编号

--查询供应信息
CREATE PROCEDURE PRO_SELECT_供应
@供应编号 INT
AS
SELECT *
FROM 供应
WHERE 供应编号=@供应编号

--查询订购信息
CREATE PROCEDURE PRO_SELECT_订购
@订单编号 INT,@产品编号 INT
AS
SELECT *
FROM 订购
WHERE 订单编号=@订单编号 AND 产品编号=@产品编号


--完整的订单销售流程
CREATE PROCEDURE PRO_订单流程
@订单编号 INT,   
@客户编号 INT, 
@员工编号 INT,
@产品编号 INT,
@订购数量 INT, 
@日期 DATE
AS
IF EXISTS
(SELECT * 
FROM 订单
WHERE 订单编号=@订单编号)
PRINT'该订单已经存在，不需重复下订单' 
ELSE IF NOT EXISTS 
(SELECT * 
FROM 产品
WHERE 产品编号=@产品编号)
print'仓库里没有该产品，不予订购' 
ELSE IF NOT EXISTS 
(SELECT * 
FROM 客户
WHERE 客户编号=@客户编号)
PRINT'你输入的客户不存在' 
ELSE IF NOT EXISTS 
(SELECT * 
FROM 员工
WHERE 员工编号=@员工编号)
PRINT'你输入的员工不存在' 
ELSE IF EXISTS 
(SELECT * 
FROM 产品
WHERE 库存量<@订购数量 AND 产品编号=@产品编号)
PRINT '该产品库存不足不予以订购' 
ELSE 
BEGIN 
EXEC PRO_INSERT_订单 @订单编号 ,@客户编号,@员工编号 ,@日期 
EXEC  PRO_INSERT_订购 @订单编号,@产品编号,@订购数量
PRINT '订单下发成功'
END;
EXEC PRO_订单流程 2,1,1,1,33,'2017-07-07'
EXEC PRO_订单流程 2,1,1,2,66,'2017-07-07'
EXEC PRO_订单流程 2,1,1,3,99,'2017-07-07'

--订单的退订
CREATE PROCEDURE PRO_DELETE_订单流程
@订单编号 INT,
@产品编号 INT
AS
BEGIN
EXEC PRO_DELETE_订单 @订单编号
EXEC PRO_DELETE_订购 @订单编号,@产品编号
PRINT '订单退订成功'
END;
EXEC PRO_DELETE_订单流程 2,1
EXEC PRO_DELETE_订单流程 2,3
EXEC PRO_DELETE_订单流程 2,6

--供应触发器
CREATE TRIGGER 供应_TRIGGER
ON 供应
FOR INSERT,DELETE
AS
UPDATE 产品
SET 库存量=库存量+(SELECT 供应数量
FROM INSERTED
WHERE 产品.产品编号=INSERTED.产品编号)
FROM 供应,产品,INSERTED
WHERE 产品.产品编号=INSERTED.产品编号
UPDATE 产品
SET 库存量=库存量-(SELECT 供应数量
FROM DELETED
WHERE 产品.产品编号=DELETED.产品编号)
FROM 供应,产品,DELETED
WHERE 产品.产品编号=DELETED.产品编号


--订购触发器
CREATE TRIGGER 订购_TRIGGER
ON 订购
FOR INSERT,DELETE
AS
UPDATE 产品
SET 库存量=库存量-(SELECT 订购数量
FROM INSERTED
WHERE 产品.产品编号=INSERTED.产品编号)
FROM 订购,产品,INSERTED
WHERE 产品.产品编号=INSERTED.产品编号
UPDATE 产品
SET 库存量=库存量+(SELECT 订购数量
FROM DELETED
WHERE 产品.产品编号=DELETED.产品编号)
FROM 订购,产品,DELETED
WHERE 产品.产品编号=DELETED.产品编号
