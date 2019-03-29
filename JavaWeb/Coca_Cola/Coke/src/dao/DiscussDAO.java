package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;

import bean.Discuss;
import bean.Usr;
import util.DataAccess;

public class DiscussDAO {
	public boolean insert(Usr u,Integer productid,String cas){
		Connection con1=DataAccess.getConnection();
		boolean flag=false;
		String sq = "insert into discuss(usrid,productid,cas,createtime,delsoft) values(?,?,?,?,?)";
		try{
			PreparedStatement ps=con1.prepareStatement(sq);
			ps.setInt(1,u.getId());
			ps.setInt(2,productid);
			ps.setString(3,cas);
			ps.setTimestamp(4,new Timestamp(System.currentTimeMillis()));
			ps.setString(5,"0");
			ps.executeUpdate();
			flag=true;
	        ps.close();// 关闭命令对象连接		 
	        con1.close();// 关闭数据库连接
		}catch(SQLException e){
			e.printStackTrace();
		}		
		return flag;
	}
	public List<Discuss>getAllDiscuss(){
		Connection con=DataAccess.getConnection();
		String sql="select discuss.*,product.productname from discuss,product where discuss.productid=product.id;";
		List<Discuss>list=new ArrayList<Discuss>();
		PreparedStatement pst=null;
		ResultSet rs=null;
		try{
			pst=con.prepareStatement(sql);
			rs=pst.executeQuery();
			while(rs.next()){
				Discuss pu=new Discuss();
				pu.setId(rs.getInt("id"));		
				pu.setCas(rs.getString("cas"));
				pu.setUsrid(rs.getInt("usrid"));
				pu.setProductid(rs.getInt("productid"));
				pu.setCreatetime(rs.getDate("createtime"));
				pu.setDelsoft(rs.getString("delsoft"));
				pu.setProductname(rs.getString("productname"));
				list.add(pu);
			}
			
		}catch(SQLException e){
			e.printStackTrace();
		}finally{
			try{
				if(rs!=null){
					rs.close();
				}
				if(pst!=null){
					pst.close();
				}
				if(con!=null){
					con.close();
				}
			}catch(Exception e2){
				e2.printStackTrace();
			}
		}		
		return list;
		
	}

}
