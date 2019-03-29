DROP DATABASE IF EXISTS coke;
CREATE DATABASE coke DEFAULT CHARSET=utf8;

use coke ;

set names utf8 ;

DROP TABLE IF EXISTS shop;
CREATE TABLE orders(
  id int NOT NULL auto_increment COMMENT '订单ID',
  usrid int default NULL COMMENT '用户ID',
	createtime datetime default NULL COMMENT '订单创建时间',
  delsoft varchar(2) default NULL COMMENT '软删除标志',
  PRIMARY KEY(id)
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='订单表';

CREATE TABLE ordersitem (
  id int NOT NULL auto_increment COMMENT '主键编号',
  ordersid int default NULL COMMENT '外键引用订单ID',
  productid int default NULL COMMENT '外键引用商品ID',
  quantity varchar(50) default NULL COMMENT '每个商品所购买数量',
  PRIMARY KEY(id)
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='订单与商品中间表';

DROP TABLE IF EXISTS product;
CREATE TABLE product (
  id int NOT NULL auto_increment COMMENT '商品ID',
  productnumber varchar(50) default NULL COMMENT '商品编号',
  kind varchar(50) default NULL COMMENT '商品口味种类', 
	category varchar(32) default NULL COMMENT '商品分类名称',
	cas varchar(32) default NULL COMMENT '商品摘要信息',
	productname varchar(32) default NULL COMMENT '商品名称',
  imagepath varchar(100) default NULL COMMENT '商品图片名称',
  isnewproduct varchar(2) default NULL COMMENT '是否新商品1-true,0-false',
  price float default NULL COMMENT '价格',
  stock int default NULL COMMENT '剩余量',
  delsoft varchar(2) default NULL COMMENT '软删除标志',
  PRIMARY KEY(id)
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='商品表';

DROP TABLE IF EXISTS shopitem;
CREATE TABLE shopitem (
  id int NOT NULL auto_increment COMMENT '主键编号',
  shopid int default NULL COMMENT '外键引用购物车ID',
  productid int default NULL COMMENT '外键引用商品ID',
  quantity int default NULL COMMENT '每个商品所购买数量',
  PRIMARY KEY(id)
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='购物车与商品中间表';
DROP TABLE IF EXISTS shop;
CREATE TABLE shop (
  id int NOT NULL auto_increment COMMENT '购物车ID',
  usrid int default NULL COMMENT '用户ID',
  delsoft varchar(2) default NULL COMMENT '软删除标志',
  PRIMARY KEY(id)
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='购物车表';

DROP TABLE IF EXISTS usr;
CREATE TABLE usr (
  id int NOT NULL auto_increment COMMENT '用户ID',
  username varchar(32) default NULL COMMENT '用户名',
  password varchar(32) default NULL COMMENT '密码',
  superuser varchar(2) default NULL COMMENT '用户角色权限2管理员,1普通用户',
  delsoft varchar(2) default NULL COMMENT '软删除标志1软删除,0正常',
  PRIMARY KEY(id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='用户表';


alter table shopitem add constraint shopitem_shop__shopid_fk foreign key(shopid) references shop(id);
alter table shopitem add constraint shopitem_product_productid_fk foreign key(productid) references product(id);

alter table ordersitem add constraint ordersitem_shop__shopid_fk foreign key(ordersid) references orders(id);
alter table ordersitem add constraint ordersitem_product_productid_fk foreign key(productid) references product(id);

alter table shop add constraint shop_usr_id_fk foreign key(usrid) references usr(id);

alter table orders add constraint oeders_usr_id_fk foreign key(usrid) references usr(id);

insert into usr values(1,"admin","123456","2","0");
insert into product values(1,"111","樱桃味","碳酸饮料","碳酸饮料可乐樱桃味","可乐","TS1.jpg","1","3.0",10,"0");
insert into product values(2,"112","经典味","碳酸饮料","碳酸饮料可乐经典味","可乐","TS1.jpg","0","2.5",10,"0");
insert into product values(3,"121","苹果味","碳酸饮料","碳酸饮料芬达苹果味","芬达","TS3.jpg","1","2.5",10,"0");
insert into product values(4,"122","橙汁味","碳酸饮料","碳酸饮料芬达橙汁味","芬达","TS3.jpg","1","2.5",10,"0");
insert into product values(5,"131","薄荷味","碳酸饮料","碳酸饮料雪碧樱桃味","雪碧","TS2.jpg","1","2.5",10,"0");
insert into product values(6,"132","经典味","碳酸饮料","碳酸饮料雪碧樱桃味","雪碧","TS2.jpg","0","2.5",10,"0");
insert into product values(7,"141","柠檬味","碳酸饮料","碳酸饮料怡泉柠檬味","怡泉","TS4.jpg","0","2.5",10,"0");
insert into product values(8,"211","果粒橙味","果汁","果汁美汁源果粒橙味","美汁源","GZ1.jpg","0","3.0",10,"0");
insert into product values(9,"212","果粒奶优味","果汁","果汁美汁源果粒奶优味","美汁源","GZ2.jpg","0","3.0",10,"0");
insert into product values(10,"213","椰子汁味","果汁","果汁美汁源果粒奶优味","美汁源","GZ3.jpg","1","3.0",10,"0");
insert into product values(11,"214","淳萃柠味","果汁","果汁美汁源淳萃柠味","美汁源","GZ4.jpg","1","3.0",10,"0");
insert into product values(12,"311","醇香拿铁味","咖啡","咖啡乔雅醇香拿铁味","乔雅","KF1.jpg","0","3.0",10,"0");
insert into product values(13,"312","浓香经典味","咖啡","咖啡乔雅浓香经典味","乔雅","KF2.jpg","0","3.0",10,"0");
insert into product values(14,"411","无味","水","水冰露无味","冰露","YS1.jpg","0","2.0",10,"0");
insert into product values(15,"421","无味","水","水水动乐无味","水动乐","YS2.jpg","0","2.0",10,"0");


select count(*) from product;
select username from usr;



select product.* from product,shopitem where product.id=shopitem.productid and shopid="1";


select * from shopitem where shopid=1;



insert into orders values(1,1,now(),0);


select * from product where cas  like '%碳酸%' order by null;



select max(id) from orders;

DELETE  from shopitem where shopid=1 and productid=1;

