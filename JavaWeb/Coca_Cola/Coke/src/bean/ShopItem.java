package bean;

public class ShopItem{
	      private Integer id;//'�������',
	      private Integer shopid ;//'������ù��ﳵID',
	      private Integer productid;// '���������ƷID',
	      private Integer quantity;//'ÿ����Ʒ����������',
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
