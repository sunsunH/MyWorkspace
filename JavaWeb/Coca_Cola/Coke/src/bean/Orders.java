package bean;

import java.sql.Date;

public class Orders{
	    private Integer id;      //'����ID',
	    private Integer usrid;//'�û�ID',
	    private Date createtime;//'��������ʱ��',
	    private String delsoft ;//'��ɾ����־',
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
