package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import bean.Usr;
import util.DataAccess;


public class UsrDAO {
	public Usr logIn(String username,String password){
		Connection con1=DataAccess.getConnection();
		String sql="select * from usr where username=? and password=?;";
		PreparedStatement pst=null;
		ResultSet rs=null;
		Usr pu=null;
		try{
			pst=con1.prepareStatement(sql);
			pst.setString(1,username);
			pst.setString(2,password);
			rs=pst.executeQuery();
			if(rs.next()){
				pu=new Usr();
				pu.setId(rs.getInt("id"));				
				pu.setUsername(rs.getString("username"));
				pu.setPassword(rs.getString("password"));
				pu.setSuperuser(rs.getString("superuser"));
				pu.setDelsoft(rs.getString("delsoft"));
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
		Connection con=DataAccess.getConnection();
		String sq = "select id from usr where username=?";
		ResultSet rs=null;
		Integer pu=null;
		boolean flag=false;
		try{
			PreparedStatement ps=con.prepareStatement(sq);
			ps.setString(1,u.getUsername());
			rs=ps.executeQuery();
			if(rs.next()){
				pu=rs.getInt("id");	
			}
			ps.close();// 关闭命令对象连接
			if(pu==null){
				String sql= "insert into usr(username,password,superuser,delsoft) values(?,?,?,?)";				
				PreparedStatement pst=con.prepareStatement(sql);
				pst.setString(1,u.getUsername());
				pst.setString(2,u.getPassword());
				pst.setString(3,"1");
				pst.setString(4,"0");
				pst.executeUpdate();
				flag=true;
			    pst.close();// 关闭命令对象连接		 
			}else{
				flag=false;	
			}
			con.close();// 关闭数据库连接		 
		}catch(SQLException e){
			e.printStackTrace();
		}		
		return flag;
	}
}
