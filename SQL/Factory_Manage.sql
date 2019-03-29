--����
USE ���۹���
GO
CREATE TABLE ��Ӧ��
(��Ӧ�̱�� INT PRIMARY KEY,
��Ӧ������ VARCHAR(20) NOT NULL,
��ϵ�绰 VARCHAR(13) NOT NULL,
��ַ VARCHAR(20))

CREATE TABLE ��Ʒ
(��Ʒ��� INT PRIMARY KEY,
��Ʒ���� VARCHAR(20) NOT NULL,
���� DECIMAL(8,2) CHECK(����>0),
����� INT CHECK(�����>=0))

CREATE TABLE �ͻ�
(�ͻ���� INT PRIMARY KEY,
�ͻ����� VARCHAR(20) NOT NULL,
��ϵ�绰 VARCHAR(13) NOT NULL,
��ַ VARCHAR(20))

CREATE TABLE Ա��
(Ա����� INT PRIMARY KEY,
���� VARCHAR(10) NOT NULL,
���� DECIMAL(8,2) CHECK(���� BETWEEN 1800 AND 100000),
��ϵ�绰 VARCHAR(13) NOT NULL,
��ַ VARCHAR(20))

CREATE TABLE ����
(������� INT PRIMARY KEY,
�ͻ���� INT NOT NULL,
Ա����� INT NOT NULL,
���� DATE,
FOREIGN KEY (�ͻ����) REFERENCES �ͻ� (�ͻ����),
FOREIGN KEY (Ա�����) REFERENCES Ա�� (Ա�����))

CREATE TABLE ��Ӧ
(��Ӧ��� INT PRIMARY KEY,
��Ӧ�̱�� INT,
��Ʒ��� INT,
��Ӧ���� INT NOT NULL,
FOREIGN KEY (��Ӧ�̱��) REFERENCES ��Ӧ�� (��Ӧ�̱��),
FOREIGN KEY (��Ʒ���) REFERENCES ��Ʒ (��Ʒ���))

CREATE TABLE ����
(������� INT,
��Ʒ��� INT,
�������� INT NOT NULL,
PRIMARY KEY(�������,��Ʒ���),
FOREIGN KEY (�������) REFERENCES ���� (�������),
FOREIGN KEY (��Ʒ���) REFERENCES ��Ʒ (��Ʒ���))

--��������
INSERT INTO ��Ӧ�� VALUES(1,'�Ϻ���ʵ����޹�˾','0577-88335572','�Ϻ�')
INSERT INTO ��Ӧ�� VALUES(2,'���ڿƼ����޹�˾','0577-89574833','����')
INSERT INTO ��Ӧ�� VALUES(3,'����������޹�˾','0589-54815618','����')
INSERT INTO ��Ӧ�� VALUES(4,'�Ͼ��������޹�˾','0895-45621205','�Ͼ�')
INSERT INTO ��Ӧ�� VALUES(5,'��ɽװ�����޹�˾','0456-77895630','��ɽ')
INSERT INTO ��Ӧ�� VALUES(6,'�����������޹�˾','0158-56893256','����')
SELECT *FROM ��Ӧ��

INSERT INTO ��Ʒ VALUES(1,'·����',120.00,100)
INSERT INTO ��Ʒ VALUES(2,'��ӡֽ',10.00,200)
INSERT INTO ��Ʒ VALUES(3,'��ʵ�',3.00,300)
INSERT INTO ��Ʒ VALUES(4,'���׻�',5.00,600)
INSERT INTO ��Ʒ VALUES(5,'�˵�',30.00,300)
INSERT INTO ��Ʒ VALUES(6,'ţ�п�',130.00,100)
INSERT INTO ��Ʒ VALUES(7,'���',3.00,1000)
SELECT *FROM ��Ʒ

INSERT INTO �ͻ� VALUES(1,'����ʵҵ���޹�˾','0868-85463951','����')
INSERT INTO �ͻ� VALUES(2,'�й��ƶ����޹�˾','0896-84569853','����')
INSERT INTO �ͻ� VALUES(3,'�й��������޹�˾','0456-78952649','�ӱ�')
INSERT INTO �ͻ� VALUES(4,'�й���ͨ���޹�˾','0589-78953295','����')
INSERT INTO �ͻ� VALUES(5,'����Ļ����޹�˾','0458-78563459','���')
INSERT INTO �ͻ� VALUES(6,'�ൺ�������޹�˾','0589-45896321','�ൺ')
SELECT *FROM �ͻ�

INSERT INTO Ա�� VALUES(1,'����',3000.50,'16945895639','����')
INSERT INTO Ա�� VALUES(2,'����',3500.50,'15989453695','����')
INSERT INTO Ա�� VALUES(3,'����',3900.00,'17658963245','����')
INSERT INTO Ա�� VALUES(4,'С��',3100.00,'18952479853','����')
INSERT INTO Ա�� VALUES(5,'С��',3200.50,'17789632456','����')
INSERT INTO Ա�� VALUES(6,'С��',3900.00,'15745862159','����')
INSERT INTO Ա�� VALUES(7,'��÷÷',2200.00,'12345678985','����')
SELECT *FROM Ա��

INSERT INTO ���� VALUES(1,2,1,'2016-03-08')
INSERT INTO ���� VALUES(2,3,4,'2017-06-06')
SELECT *FROM ����

INSERT INTO ��Ӧ VALUES(1,1,2,300)
INSERT INTO ��Ӧ VALUES(2,2,1,600)
INSERT INTO ��Ӧ VALUES(3,3,3,700)
INSERT INTO ��Ӧ VALUES(4,1,1,700)
SELECT *FROM ��Ӧ

INSERT INTO ���� VALUES(1,1,20)
INSERT INTO ���� VALUES(1,2,10)
INSERT INTO ���� VALUES(1,3,30)
INSERT INTO ���� VALUES(2,1,30)
INSERT INTO ���� VALUES(2,3,60)
INSERT INTO ���� VALUES(2,6,90)
SELECT *FROM ����
	

--��������ͼ
CREATE VIEW VIEW_����(�ͻ����,��������)
AS
SELECT �ͻ����,COUNT(�������)
FROM ����
GROUP BY �ͻ����;
SELECT *FROM VIEW_����

--��Ʒ����ͼ
CREATE VIEW VIEW_��Ʒ(��Ʒ���,��Ʒ����)
AS
SELECT ��Ʒ���,SUM(��������)
FROM ����
GROUP BY ��Ʒ���;
SELECT *FROM VIEW_��Ʒ

--������ϸ��ͼ
CREATE VIEW VIEW_������ϸ(�������,�ͻ����,Ա�����,��Ʒ���,��������,����,�ܶ�)  
AS
SELECT 
����.�������,�ͻ�.�ͻ����,Ա��.Ա�����,��Ʒ.��Ʒ���,����.��������,����.����,����*�������� AS �ܶ� 
FROM ����,����,��Ʒ,�ͻ�,Ա��
WHERE 
����.�������=����.������� AND �ͻ�.�ͻ����=����.�ͻ���� AND Ա��.Ա�����=����.Ա����� AND ��Ʒ.��Ʒ���=����.��Ʒ��� 
SELECT *FROM VIEW_������ϸ

--��ѯ������ϸ��ͼ
CREATE PROCEDURE PRO_VIEW_������ϸ
--@������� INT
AS
SELECT *
FROM VIEW_������ϸ
--WHERE �������=@�������
EXEC PRO_VIEW_������ϸ

--��ѯ���������Ŀͻ����߲�Ʒ
CREATE PROCEDURE PRO_SELECT_MAX_����
AS
SELECT *
FROM �ͻ�
WHERE �ͻ���� IN
(SELECT �ͻ���� FROM VIEW_����
WHERE �������� IN
(SELECT MAX(��������)FROM VIEW_����))
CREATE PROCEDURE PRO_SELECT_MAX_����
AS
SELECT �ͻ����,�������� 
FROM  VIEW_����  
where ��������>=ALL(SELECT �������� FROM VIEW_����)

CREATE PROCEDURE PRO_SELECT_MAX_��Ʒ
AS
SELECT ��Ʒ���,��Ʒ���� 
FROM VIEW_��Ʒ
WHERE ��Ʒ����>=ALL(SELECT ��Ʒ���� FROM VIEW_��Ʒ)
EXEC PRO_SELECT_MAX_��Ʒ

--�洢����

--�洢��ѯ���빩Ӧ����Ϣ
CREATE PROCEDURE PRO_INSERT_��Ӧ��
@��Ӧ�̱�� INT,
@��Ӧ������ VARCHAR(20),
@��ϵ�绰 CHAR(13),
@��ַ VARCHAR(20)
AS
IF EXISTS
(SELECT *
FROM ��Ӧ��
WHERE ��Ӧ�̱��=@��Ӧ�̱��)
PRINT '�ù�Ӧ�̼�¼�Ѿ�����'
ELSE
INSERT INTO ��Ӧ��(��Ӧ�̱��,��Ӧ������,��ϵ�绰,��ַ)
VALUES(@��Ӧ�̱��,@��Ӧ������,@��ϵ�绰,@��ַ)
EXEC PRO_INSERT_��Ӧ�� 9,'�ֶ���','18774871311','����';

--�����Ʒ��Ϣ
CREATE PROCEDURE PRO_INSERT_��Ʒ
@��Ʒ��� INT,
@��Ʒ���� VARCHAR(20),
@���� DECIMAL(8,2),
@����� INT
AS
IF EXISTS
(SELECT *
FROM ��Ʒ
WHERE ��Ʒ���=@��Ʒ���)
PRINT '�ò�Ʒ��¼�Ѿ�����'
ELSE
INSERT INTO ��Ʒ(��Ʒ���,��Ʒ����,����,�����)
VALUES(@��Ʒ���,@��Ʒ����,@����,@�����)

--�ͻ���Ϣ
CREATE PROCEDURE PRO_INSERT_�ͻ�
@�ͻ���� INT,
@�ͻ����� VARCHAR(20),
@��ϵ�绰 CHAR(13),
@��ַ VARCHAR(20)
AS
IF EXISTS
(SELECT *
FROM �ͻ�
WHERE �ͻ����=@�ͻ����)
PRINT '�ÿͻ���¼�Ѿ�����'
ELSE
INSERT INTO �ͻ�(�ͻ����,�ͻ�����,��ϵ�绰,��ַ)
VALUES(@�ͻ����,@�ͻ�����,@��ϵ�绰,@��ַ)

--����Ա����Ϣ
CREATE PROCEDURE PRO_INSERT_Ա��
@Ա����� INT,
@���� VARCHAR(20),
@���� DECIMAL(9,2),
@��ϵ�绰 CHAR(13),
@��ַ VARCHAR(20)
AS
IF EXISTS
(SELECT *
FROM Ա��
WHERE Ա�����=@Ա�����)
PRINT '��Ա����¼�Ѿ�����'
ELSE
INSERT INTO Ա��(Ա�����,����,����,��ϵ�绰,��ַ)
VALUES(@Ա�����,@����,@����,@��ϵ�绰,@��ַ)

--���붩����Ϣ
CREATE PROCEDURE PRO_INSERT_����
@������� INT,
@�ͻ���� INT,
@Ա����� INT,
@���� DATE
AS
IF EXISTS
(SELECT *
FROM ����
WHERE �������=@�������)
PRINT '�ö�����Ϣ�Ѵ���'
ELSE
INSERT INTO ����(�������,�ͻ����,Ա�����,����)
VALUES(@�������,@�ͻ����,@Ա�����,@����)


--���빩Ӧ��Ϣ
CREATE PROCEDURE PRO_INSERT_��Ӧ
@��Ӧ��� INT,
@��Ӧ�̱�� INT,
@��Ʒ��� INT,
@��Ӧ���� INT
AS
SELECT *
FROM ��Ӧ
WHERE ��Ӧ���=@��Ӧ���
INSERT INTO ��Ӧ(��Ӧ���,��Ӧ�̱��,��Ʒ���,��Ӧ����)
VALUES(@��Ӧ���,@��Ӧ�̱��,@��Ʒ���,@��Ӧ����)

--���붩����Ϣ
CREATE PROCEDURE PRO_INSERT_����
@������� INT,
@��Ʒ��� INT,
@�������� INT
AS
SELECT *
FROM ����
WHERE �������=@������� AND ��Ʒ���=@��Ʒ���
INSERT INTO ����(�������,��Ʒ���,��������)
VALUES(@�������,@��Ʒ���,@��������)


--�洢ɾ�����빩Ӧ����Ϣ�Ĳ���
CREATE PROCEDURE PRO_DELETE_��Ӧ��
@��Ӧ�̱�� INT
AS
if EXISTS
(SELECT * 
FROM ��Ӧ�� 
WHERE ��Ӧ�̱��=@��Ӧ�̱��)
DELETE FROM ��Ӧ��
WHERE ��Ӧ�̱��=@��Ӧ�̱�� 
ELSE
PRINT '�ù�Ӧ�̲�����'

--ɾ����Ʒ��Ϣ
CREATE PROCEDURE PRO_DELETE_��Ʒ
@��Ʒ��� INT
AS
if EXISTS
(SELECT * 
FROM ��Ʒ 
WHERE ��Ʒ���=@��Ʒ���)
DELETE FROM ��Ʒ
WHERE ��Ʒ���=@��Ʒ��� 
ELSE
PRINT '�ò�Ʒ������'

--ɾ���ͻ���Ϣ
CREATE PROCEDURE PRO_DELETE_�ͻ�
@�ͻ���� INT
AS
if EXISTS
(SELECT * 
FROM �ͻ� 
WHERE �ͻ����=@�ͻ����)
DELETE FROM ��Ӧ��
WHERE �ͻ����=@�ͻ���� 
ELSE
PRINT '�ÿͻ�������'

--ɾ��Ա����Ϣ
CREATE PROCEDURE PRO_DELETE_Ա��
@Ա����� INT
AS
if EXISTS
(SELECT * 
FROM Ա�� 
WHERE Ա�����=@Ա�����)
DELETE FROM Ա��
WHERE Ա�����=@Ա����� 
ELSE
PRINT '��Ա��������'

--ɾ��������Ϣ
CREATE PROCEDURE PRO_DELETE_����
@������� INT
AS
if EXISTS
(SELECT * 
FROM ���� 
WHERE �������=@�������)
DELETE FROM ����
WHERE �������=@������� 
ELSE
PRINT '�ö���������'

--ɾ����Ӧ��Ϣ
CREATE PROCEDURE PRO_DELETE_��Ӧ
@��Ӧ��� INT
AS
if EXISTS
(SELECT * 
FROM ��Ӧ 
WHERE ��Ӧ���=@��Ӧ���)
DELETE FROM ��Ӧ
WHERE ��Ӧ���=@��Ӧ��� 
ELSE
PRINT '�˴ι�Ӧ������'

--ɾ��������Ϣ
CREATE PROCEDURE PRO_DELETE_����
@������� INT,
@��Ʒ��� INT
AS
if EXISTS
(SELECT * 
FROM ���� 
WHERE �������=@������� AND ��Ʒ���=@��Ʒ���)
DELETE FROM ����
WHERE �������=@������� AND ��Ʒ���=@��Ʒ��� 
ELSE
PRINT '�˴ζ���������'


--�洢���¹�Ӧ����Ϣ�Ĳ���
CREATE PROCEDURE PRO_UPDATE_��Ӧ�� 
@��Ӧ�̱�� INT, 
@��Ӧ������ VARCHAR(20), 
@��ϵ�绰 CHAR(13),
@��ַ VARCHAR(20) 
AS
IF EXISTS
(SELECT * 
FROM ��Ӧ�� 
WHERE ��Ӧ�̱��=@��Ӧ�̱��)
UPDATE ��Ӧ�� 
SET ��Ӧ������=@��Ӧ������,  
��ϵ�绰=@��ϵ�绰, 
��ַ=@��ַ 
WHERE ��Ӧ�̱��=@��Ӧ�̱�� 
ELSE
PRINT '�޴˹�Ӧ����Ϣ!'

--���²�Ʒ��Ϣ
CREATE PROCEDURE PRO_UPDATE_��Ʒ 
@��Ʒ��� INT, 
@��Ʒ���� VARCHAR(20), 
@���� DECIMAL(8,2),
@����� INT 
AS
IF EXISTS
(SELECT * 
FROM ��Ʒ 
WHERE ��Ʒ���=@��Ʒ���)
UPDATE ��Ʒ 
SET ��Ʒ����=@��Ʒ����,  
����=@����, 
�����=@����� 
WHERE ��Ʒ���=@��Ʒ��� 
ELSE
PRINT '�޴˲�Ʒ��Ϣ!'

--���¿ͻ���Ϣ
CREATE PROCEDURE PRO_UPDATE_�ͻ� 
@�ͻ���� INT, 
@�ͻ����� VARCHAR(20), 
@��ϵ�绰 CHAR(13),
@��ַ VARCHAR(20) 
AS
IF EXISTS
(SELECT * 
FROM �ͻ� 
WHERE �ͻ����=@�ͻ����)
UPDATE �ͻ� 
SET �ͻ�����=@�ͻ�����,  
��ϵ�绰=@��ϵ�绰, 
��ַ=@��ַ 
WHERE �ͻ����=@�ͻ���� 
ELSE
PRINT '�޴˿ͻ���Ϣ!'

--����Ա����Ϣ
CREATE PROCEDURE PRO_UPDATE_Ա�� 
@Ա����� INT, 
@���� CHAR(10), 
@���� DECIMAL(9,2), 
@��ϵ�绰 CHAR(13),
@��ַ VARCHAR(20) 
AS
IF EXISTS
(SELECT * 
FROM Ա�� 
WHERE Ա�����=@Ա�����)
UPDATE Ա�� 
SET ����=@����, 
����=@����, 
��ϵ�绰=@��ϵ�绰, 
��ַ=@��ַ 
WHERE Ա�����=@Ա����� 
ELSE
PRINT '�޴�Ա����Ϣ!'
EXEC PRO_UPDATE_Ա�� 1,'С��',6000,'10023564789','����';

--���¶�����Ϣ
/*CREATE PROCEDURE PRO_UPDATE_����
@�������INT,
@�ͻ����INT, 
@Ա�����INT,
@����DATE
AS
IF EXISTS
(SELECT * 
FROM ����
WHERE �������=@�������)
UPDATE ����
SET �ͻ����=@�ͻ����,
Ա�����=@Ա�����,
����=@����
WHERE �������=@�������
ELSE
PRINT '�޴˶�����Ϣ!'

--���¹�Ӧ��Ϣ
CREATE PROCEDURE PRO_UPDATE_��Ӧ
@��Ӧ���INT,
@��Ӧ�̱��INT, 
@��Ʒ���INT, 
@��Ӧ����INT
AS
IF EXISTS
(SELECT * 
FROM ��Ӧ
WHERE ��Ӧ���=@��Ӧ���)
UPDATE ��Ӧ
SET ��Ӧ�̱��=@��Ӧ�̱��,
��Ʒ���=@��Ʒ���,
��Ӧ����=@��Ӧ����
WHERE ��Ӧ���=@��Ӧ���
ELSE
PRINT '�޴˹�Ӧ��Ϣ!'

--���¶�����Ϣ
CREATE PROCEDURE PRO_UPDATE_����
@�������INT, 
@��Ʒ���INT, 
@��������INT
AS
IF EXISTS
(SELECT * 
FROM ����
WHERE �������=@�������AND ��Ʒ���=@��Ʒ���)
UPDATE ����
SET ��������=@��������
WHERE �������=@������� AND ��Ʒ���=@��Ʒ���
ELSE
PRINT '�޴˶�����Ϣ!'*/ 


--�洢��ѯ��Ӧ����Ϣ�Ĳ���
CREATE PROCEDURE PRO_SELECT_��Ӧ��
@��Ӧ�̱�� INT
AS
SELECT *
FROM ��Ӧ��
WHERE ��Ӧ�̱��=@��Ӧ�̱��
EXEC PRO_SELECT_��Ӧ�� 3;

--��ѯ��Ʒ��Ϣ
CREATE PROCEDURE PRO_SELECT_��Ʒ
@��Ʒ��� INT
AS
SELECT *
FROM ��Ʒ
WHERE ��Ʒ���=@��Ʒ���

--��ѯ�ͻ���Ϣ
CREATE PROCEDURE PRO_SELECT_�ͻ�
@�ͻ���� INT
AS
SELECT *
FROM �ͻ�
WHERE �ͻ����=@�ͻ����

--��ѯԱ����Ϣ
CREATE PROCEDURE PRO_SELECT_Ա��
@Ա����� INT
AS
SELECT *
FROM Ա��
WHERE Ա�����=@Ա�����

--��ѯ������Ϣ
CREATE PROCEDURE PRO_SELECT_����
@������� INT
AS
SELECT *
FROM ����
WHERE �������=@�������

--��ѯ��Ӧ��Ϣ
CREATE PROCEDURE PRO_SELECT_��Ӧ
@��Ӧ��� INT
AS
SELECT *
FROM ��Ӧ
WHERE ��Ӧ���=@��Ӧ���

--��ѯ������Ϣ
CREATE PROCEDURE PRO_SELECT_����
@������� INT,@��Ʒ��� INT
AS
SELECT *
FROM ����
WHERE �������=@������� AND ��Ʒ���=@��Ʒ���


--�����Ķ�����������
CREATE PROCEDURE PRO_��������
@������� INT,   
@�ͻ���� INT, 
@Ա����� INT,
@��Ʒ��� INT,
@�������� INT, 
@���� DATE
AS
IF EXISTS
(SELECT * 
FROM ����
WHERE �������=@�������)
PRINT'�ö����Ѿ����ڣ������ظ��¶���' 
ELSE IF NOT EXISTS 
(SELECT * 
FROM ��Ʒ
WHERE ��Ʒ���=@��Ʒ���)
print'�ֿ���û�иò�Ʒ�����趩��' 
ELSE IF NOT EXISTS 
(SELECT * 
FROM �ͻ�
WHERE �ͻ����=@�ͻ����)
PRINT'������Ŀͻ�������' 
ELSE IF NOT EXISTS 
(SELECT * 
FROM Ա��
WHERE Ա�����=@Ա�����)
PRINT'�������Ա��������' 
ELSE IF EXISTS 
(SELECT * 
FROM ��Ʒ
WHERE �����<@�������� AND ��Ʒ���=@��Ʒ���)
PRINT '�ò�Ʒ��治�㲻���Զ���' 
ELSE 
BEGIN 
EXEC PRO_INSERT_���� @������� ,@�ͻ����,@Ա����� ,@���� 
EXEC  PRO_INSERT_���� @�������,@��Ʒ���,@��������
PRINT '�����·��ɹ�'
END;
EXEC PRO_�������� 2,1,1,1,33,'2017-07-07'
EXEC PRO_�������� 2,1,1,2,66,'2017-07-07'
EXEC PRO_�������� 2,1,1,3,99,'2017-07-07'

--�������˶�
CREATE PROCEDURE PRO_DELETE_��������
@������� INT,
@��Ʒ��� INT
AS
BEGIN
EXEC PRO_DELETE_���� @�������
EXEC PRO_DELETE_���� @�������,@��Ʒ���
PRINT '�����˶��ɹ�'
END;
EXEC PRO_DELETE_�������� 2,1
EXEC PRO_DELETE_�������� 2,3
EXEC PRO_DELETE_�������� 2,6

--��Ӧ������
CREATE TRIGGER ��Ӧ_TRIGGER
ON ��Ӧ
FOR INSERT,DELETE
AS
UPDATE ��Ʒ
SET �����=�����+(SELECT ��Ӧ����
FROM INSERTED
WHERE ��Ʒ.��Ʒ���=INSERTED.��Ʒ���)
FROM ��Ӧ,��Ʒ,INSERTED
WHERE ��Ʒ.��Ʒ���=INSERTED.��Ʒ���
UPDATE ��Ʒ
SET �����=�����-(SELECT ��Ӧ����
FROM DELETED
WHERE ��Ʒ.��Ʒ���=DELETED.��Ʒ���)
FROM ��Ӧ,��Ʒ,DELETED
WHERE ��Ʒ.��Ʒ���=DELETED.��Ʒ���


--����������
CREATE TRIGGER ����_TRIGGER
ON ����
FOR INSERT,DELETE
AS
UPDATE ��Ʒ
SET �����=�����-(SELECT ��������
FROM INSERTED
WHERE ��Ʒ.��Ʒ���=INSERTED.��Ʒ���)
FROM ����,��Ʒ,INSERTED
WHERE ��Ʒ.��Ʒ���=INSERTED.��Ʒ���
UPDATE ��Ʒ
SET �����=�����+(SELECT ��������
FROM DELETED
WHERE ��Ʒ.��Ʒ���=DELETED.��Ʒ���)
FROM ����,��Ʒ,DELETED
WHERE ��Ʒ.��Ʒ���=DELETED.��Ʒ���
