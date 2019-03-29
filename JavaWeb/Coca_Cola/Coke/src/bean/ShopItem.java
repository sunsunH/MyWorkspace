package bean;

public class ShopItem{
	      private Integer id;//'主键编号',
	      private Integer shopid ;//'外键引用购物车ID',
	      private Integer productid;// '外键引用商品ID',
	      private Integer quantity;//'每个商品所购买数量',
	      public ShopItem(){
		    }
	      public ShopItem(Integer id,Integer shopid,Integer productid,Integer quantity){
		        super();
		        this.id=id;
		        this.shopid=shopid;
		        this.productid=productid;
		        this.quantity=quantity;
		   }
		public Integer getId() {
			return id;
		}
		public void setId(Integer id) {
			this.id = id;
		}
		public Integer getShopid() {
			return shopid;
		}
		public void setShopid(Integer shopid) {
			this.shopid = shopid;
		}
		public Integer getProductid() {
			return productid;
		}
		public void setProductid(Integer productid) {
			this.productid = productid;
		}
		public Integer getQuantity() {
			return quantity;
		}
		public void setQuantity(Integer quantity) {
			this.quantity = quantity;
		}


}
