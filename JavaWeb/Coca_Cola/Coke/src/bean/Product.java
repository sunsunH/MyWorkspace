package bean;

public class Product{
	    private Integer id ;  // '��ƷID',
	    private String productnumber;//'��Ʒ���',
	    private String kind;//'��Ʒ��ζ����', 
	    private String category;//'��Ʒ��������',
	    private String cas;//'��ƷժҪ��Ϣ',
	    private String productname;//'��Ʒ����',
	    private String imagepath;//'��ƷͼƬ����',
	    private String isnewproduct;//'�Ƿ�����Ʒ1-true,0-false',
	    private Float price;//'�۸�',
	    private Integer stock;//'ʣ����',
	    private String delsoft;         //��ɾ����־ 1��ɾ����0����
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
