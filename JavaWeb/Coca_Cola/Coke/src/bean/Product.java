package bean;

public class Product{
	    private Integer id ;  // '商品ID',
	    private String productnumber;//'商品编号',
	    private String kind;//'商品口味种类', 
	    private String category;//'商品分类名称',
	    private String cas;//'商品摘要信息',
	    private String productname;//'商品名称',
	    private String imagepath;//'商品图片名称',
	    private String isnewproduct;//'是否新商品1-true,0-false',
	    private Float price;//'价格',
	    private Integer stock;//'剩余量',
	    private String delsoft;         //软删除标志 1软删除，0正常
	    //Constructors
	    /**default constructor*/
	    public Product(){
	    }

	    /**full constructor*/
	    public Product(Integer id,String productnumber,String kind,String category,String cas,
	    		       String productname,String imagepath,String isnewproduct,
	    		       Float price,Integer stock,String delsoft){
	        super();
	        this.id=id;
	        this.productnumber=productnumber;
	        this.kind=kind;
	        this.category=category;
	        this.cas=cas;
	        this.productname=productname;
	        this.imagepath=imagepath;
	        this.isnewproduct=isnewproduct;
	        this.price=price;
	        this.stock=stock;
	        this.delsoft=delsoft;
	    }
	  //Property accessors
		public Integer getId() {
			return id;
		}

		public void setId(Integer id) {
			this.id = id;
		}

		public String getProductnumber() {
			return productnumber;
		}

		public void setProductnumber(String productnumber) {
			this.productnumber = productnumber;
		}

		public String getKind() {
			return kind;
		}

		public void setKind(String kind) {
			this.kind = kind;
		}

		public String getCategory() {
			return category;
		}

		public void setCategory(String category) {
			this.category = category;
		}

		public String getCas() {
			return cas;
		}

		public void setCas(String cas) {
			this.cas = cas;
		}

		public String getProductname() {
			return productname;
		}

		public void setProductname(String productname) {
			this.productname = productname;
		}

		public String getImagepath() {
			return imagepath;
		}

		public void setImagepath(String imagepath) {
			this.imagepath = imagepath;
		}

		public String getIsnewproduct() {
			return isnewproduct;
		}

		public void setIsnewproduct(String isnewproduct) {
			this.isnewproduct = isnewproduct;
		}

		public Float getPrice() {
			return price;
		}

		public void setPrice(Float price) {
			this.price = price;
		}

		public Integer getStock() {
			return stock;
		}

		public void setStock(Integer stock) {
			this.stock = stock;
		}

		public String getDelsoft() {
			return delsoft;
		}

		public void setDelsoft(String delsoft) {
			this.delsoft = delsoft;
		}
}
