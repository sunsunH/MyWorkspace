package bean;

import java.sql.Date;

public class Orders_Item{
	      private Integer id;//'主键编号',
	      private Integer ordersid ;//'外键引用购物车ID',
	      private Integer productid;// '外键引用商品ID',
	      private String quantity;//'每个商品所购买数量',
	      private Float price;//'总价',
	      private Integer usrid;//'用户ID',
		  private Date createtime;//'订单创建时间',
	      public Orders_Item(){}
	      public Orders_Item(Integer id,Integer ordersid,Integer productid,String quantity,Integer usrid,Date createtime,Float price){
		        super();
		        this.id=id;
		        this.ordersid=ordersid;
		        this.productid=productid;
		        this.quantity=quantity;
		        this.usrid=usrid;
		        this.createtime=createtime;
		        this.price=price;
		   }
		public Integer getId() {
			return id;
		}
		public void setId(Integer id) {
			this.id = id;
		}
		public Integer getOrdersid() {
			return ordersid;
		}
		public void setOrdersid(Integer ordersid) {
			this.ordersid = ordersid;
		}
		public Integer getProductid() {
			return productid;
		}
		public void setProductid(Integer productid) {
			this.productid = productid;
		}
		public String getQuantity() {
			return quantity;
		}
		public void setQuantity(String quantity) {
			this.quantity = quantity;
		}
		public Integer getUsrid() {
			return usrid;
		}

		public void setUsrid(Integer usrid) {
			this.usrid = usrid;
		}
		public Date getCreatetime() {
			return createtime;
		}

		public void setCreatetime(Date createtime) {
			this.createtime = createtime;
		}
		public Float getPrice() {
			return price;
		}

		public void setPrice(Float price) {
			this.price = price;
		}

}
