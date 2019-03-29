package dao;

import java.sql.Connection;


import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;


import bean.Product;
import util.DataAccess;

public class ProductDAO {
	public List<Product>getAllProduct(String key){
		Connection con=DataAccess.getConnection();
		String sql="select * from product  where cas  like ?;";
		List<Product>list=new ArrayList<Product>();
		PreparedStatement pst=null;
		ResultSet rs=null;
		try{
			pst=con.prepareStatement(sql);
			pst.setString(1,"%"+key+"%");
			rs=pst.executeQuery();
			while(rs.next()){
				Product pu=new Product();
				pu.setId(rs.getInt("id"));		
				pu.setProductnumber(rs.getString("productnumber"));
				pu.setKind(rs.getString("kind"));
				pu.setCategory(rs.getString("category"));
				pu.setCas(rs.getString("cas"));
				pu.setProductname(rs.getString("productname"));
				pu.setImagepath(rs.getString("imagepath"));
				pu.setIsnewproduct(rs.getString("isnewproduct"));
				pu.setPrice(rs.getFloat("price"));
				pu.setStock(rs.getInt("stock"));
				pu.setDelsoft(rs.getString("delsoft"));
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
	public boolean Update(Integer quantity,String productid){
		Connection con4=DataAccess.getConnection();
		boolean flag=false;
		String sql="update product set stock=stock-? where id=?;";	
		try{
			PreparedStatement ps=con4.prepareStatement(sql);
			ps.setInt(1,quantity);
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
}
