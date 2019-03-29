package bean;

import java.sql.Date;

public class Orders{
	    private Integer id;      //'订单ID',
	    private Integer usrid;//'用户ID',
	    private Date createtime;//'订单创建时间',
	    private String delsoft ;//'软删除标志',
	    public Orders(){
	    }

	    /**full constructor*/
	    public Orders(Integer id,Integer usrid,Date createtime,String delsoft){
	        super();
	        this.id=id;
	        this.usrid=usrid;
	        this.createtime=createtime;
	        this.delsoft=delsoft;
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
}
