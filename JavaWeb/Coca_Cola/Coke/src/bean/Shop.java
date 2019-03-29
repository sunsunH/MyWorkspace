package bean;

public class Shop{
	    private Integer id;      //'购物车物品ID',
	    private Integer usrid;//'用户ID',
	    private String delsoft ;//'软删除标志',
	    public Shop(){
	    }

	    /**full constructor*/
	    public Shop(Integer id,Integer usrid,String delsoft){
	        super();
	        this.id=id;
	        this.usrid=usrid;
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
}
