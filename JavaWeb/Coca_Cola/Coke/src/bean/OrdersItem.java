package bean;

public class OrdersItem{
	      private Integer id;//'�������',
	      private Integer ordersid ;//'������ù��ﳵID',
	      private Integer productid;// '���������ƷID',
	      private String quantity;//'ÿ����Ʒ����������',
	      private Float price;//'�۸�',
	      public OrdersItem(){}
	      public OrdersItem(Integer id,Integer ordersid,Integer productid,String quantity,Float price){
		        super();
		        this.id=id;
		        this.ordersid=ordersid;
		        this.productid=productid;
		        this.quantity=quantity;
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
		public Float getPrice() {
			return price;
		}

		public void setPrice(Float price) {
			this.price = price;
		}

}
