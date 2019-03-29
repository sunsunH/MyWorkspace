package dao;

import java.sql.Connection;


import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import bean.Usr;
import util.DataAccess;

public class ShopDAO {
	public Integer select(Usr u){
		Connection con1=DataAccess.getConnection();
		String sql="select id from shop where usrid=?;";
		PreparedStatement pst=null;
		ResultSet rs=null;
		Integer pu=null;
		try{
			pst=con1.prepareStatement(sql);
			pst.setInt(1,u.getId());
			rs=pst.executeQuery();
			if(rs.next()){
				pu=rs.getInt("id");			
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
				if(con1!=null){
					con1.close();
				}
			}catch(Exception e2){
				e2.printStackTrace();
			}
		}
		return pu;
	}

	public boolean Register(Usr u){
		Connection con2=DataAccess.getConnection();
		boolean flag=false;
		String sq = "insert into shop(usrid,delsoft) values(?,?)";
		try{
			PreparedStatement ps=con2.prepareStatement(sq);
			ps.setInt(1,u.getId());
			ps.setString(2,"0");
			ps.executeUpdate();
			flag=true;
	        ps.close();// 关闭命令对象连接		 
	        con2.close();// 关闭数据库连接
		}catch(SQLException e){
			e.printStackTrace();
		}		
		return flag;
	}
    
}
