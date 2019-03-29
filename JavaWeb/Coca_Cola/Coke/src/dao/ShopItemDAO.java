package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import bean.ShopItem;
import util.DataAccess;

public class ShopItemDAO {
	public boolean add(Integer shopid,String productid){
		Connection con2=DataAccess.getConnection();
		boolean flag=false;
		String sq = "insert into shopitem(shopid,productid,quantity) values(?,?,?)";
		try{
			PreparedStatement ps=con2.prepareStatement(sq);
			ps.setInt(1,shopid);
			ps.setString(2,productid);
			ps.setInt(3,1);
			ps.executeUpdate();
			flag=true;
	        ps.close();// 关闭命令对象连接		 
	        con2.close();// 关闭数据库连接
		}catch(SQLException e){
			e.printStackTrace();
		}		
		return flag;
	}
	public Integer check(Integer shopid,String productid){
		Connection con3=DataAccess.getConnection();
		String sq = "select id from shopitem where shopid=? and productid=?";
		ResultSet rs=null;
		Integer pu=null;
		try{
			PreparedStatement ps=con3.prepareStatement(sq);
			ps.setInt(1,shopid);
			ps.setString(2,productid);
			rs=ps.executeQuery();
			if(rs.next()){
				pu=rs.getInt("id");			
			}
	        ps.close();// 关闭命令对象连接		 
	        con3.close();// 关闭数据库连接
		}catch(SQLException e){
			e.printStackTrace();
		}		
		return pu;
	}
	public boolean Update(Integer shopid,String productid){
		Connection con4=DataAccess.getConnection();
		boolean flag=false;
		String sql="update shopitem set quantity=quantity+1 where shopid=? and productid=?;";	
		try{
			PreparedStatement ps=con4.prepareStatement(sql);
			ps.setInt(1,shopid);
			ps.setString(2,productid);
			ps.executeUpdate();
			flag=true;
	        ps.close();// 关闭命令对象连接		 
	        con4.close();// 关闭数据库连接
		}catch(SQLException e){
			e.printStackTrace();
		}		
		return flag;
	}
	public boolean Delete(String shopid,String productid){
		Connection con=DataAccess.getConnection();
		boolean flag=false;
		String sql="DELETE  from shopitem where shopid=? and productid=?;";	
		try{
			PreparedStatement ps=con.prepareStatement(sql);
			ps.setString(1,shopid);
			ps.setString(2,productid);
			ps.executeUpdate();
			flag=true;
	        ps.close();// 关闭命令对象连接		 
	        con.close();// 关闭数据库连接
		}catch(SQLException e){
			e.printStackTrace();
		}		
		return flag;
	}


}
