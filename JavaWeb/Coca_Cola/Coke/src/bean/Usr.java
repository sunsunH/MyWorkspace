package bean;

public class Usr{
	    private Integer id;             //�û�id
	    private String username;        //�û���
	    private String password;        //����
	    private String superuser;    //�û���ɫȨ�� 2����Ա��1��ͨ�û�
	    private String delsoft;         //��ɾ����־ 1��ɾ����0����
	    //Constructors
	    /**default constructor*/
	    public Usr(){
	    }

	    /**full constructor
	     * @param id */
	    public Usr(String username,String password,String superuser,String delsoft, Integer id){
	        super();
	        this.id=id;
	        this.username=username;
	        this.password=password;
	        this.superuser=superuser;
	        this.delsoft=delsoft;
	    }
	    
	    //Property accessors
	    public Integer getId(){
	    	
	    	return id;
		}
		
		public void setId(Integer id){
			this.id=id;
		}
		public String getUsername(){
			return username;
		}
		public void setUsername(String username){
			this.username=username;
		}
		public String getPassword(){
			return password;
		}
		public void setPassword(String password){
			this.password=password;
		}
		public String getSuperuser(){
			return superuser;
		}
		public void setSuperuser(String superuser){
			this.superuser=superuser;
		}
		public String getDelsoft(){
			return delsoft;
		}
		public void setDelsoft(String delsoft){
			this.delsoft=delsoft;
		}
}
