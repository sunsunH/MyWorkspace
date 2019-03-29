package bean;

import java.sql.Date;

public class Discuss{
	    private Integer id;      //'ID',
	    private Integer usrid;//'用户ID',
	    private Integer productid ;//'外键引用产品ID',
	    private Date createtime;//'创建时间',
	    private String cas ;
	    private String delsoft ;//'软删除标志',
	    private String productname ;//'外键引用产品ID',
	    public Discuss(){
	    }

	    /**full constructor*/
	    public Discuss(Integer id,Integer usrid,Date createtime,Integer productid,String delsoft,String cas,String productname){
	        super();
	        this.id=id;
	        this.usrid=usrid;
	        this.productid=productid;
	        this.createtime=createtime;
	        this.cas=cas;
	        this.delsoft=delsoft;
	        this.productname=productname;

	    }

		public Integer getId() {
			return id;
		}

		public void setId(Integer id) {
			this.id = id;
		}

		public Integer getUsrid() {
			return usrid;
		}

		public void setUsrid(Integer usrid) {
			this.usrid = usrid;
		}
		

		public String getDelsoft() {
			return delsoft;
		}

		public void setDelsoft(String delsoft) {
			this.delsoft = delsoft;
		}

		public Date getCreatetime() {
			return createtime;
		}

		public void setCreatetime(Date createtime) {
			this.createtime = createtime;
		}
		public Integer getProductid() {
			return productid;
		}

		public void setProductid(Integer productid) {
			this.productid = productid;
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
}
