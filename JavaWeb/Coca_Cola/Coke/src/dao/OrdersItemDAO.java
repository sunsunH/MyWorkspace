package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import bean.OrdersItem;
import bean.Product_ShopItem;
import util.DataAccess;

public class OrdersItemDAO {
	public boolean insert(Integer ordersid,String productid,Integer quantity,Float price){
		Connection con1=DataAccess.getConnection();
		boolean flag=false;
		String sq = "insert into ordersitem(ordersid,productid,quantity,price) values(?,?,?,?)";
		try{
			PreparedStatement ps=con1.prepareStatement(sq);
			ps.setInt(1,ordersid);
			ps.setString(2,productid);
			ps.setInt(3,quantity);
			ps.setFloat(4,Float.valueOf(quantity)*price);
			ps.executeUpdate();
			flag=true;
	        ps.close();// 关闭命令对象连接		 
	        con1.close();// 关闭数据库连接
		}catch(SQLException e){
			e.printStackTrace();
		}		
		return flag;
	}
	public List<OrdersItem>getOrdersItem(Integer ordersid){
		Connection con=DataAccess.getConnection();
		String sql="select * from ordersitem where ordersid=?;";
		List<OrdersItem>list=new ArrayList<OrdersItem>();
		PreparedStatement pst=null;
		ResultSet rs=null;
		try{
			pst=con.prepareStatement(sql);
			pst.setInt(1,ordersid);
			rs=pst.executeQuery();
			while(rs.next()){
				OrdersItem pu=new OrdersItem();
				pu.setId(rs.getInt("id"));		
				pu.setProductid(rs.getInt("productid"));
				pu.setOrdersid(rs.getInt("ordersid"));
				pu.setQuantity(rs.getString("quantity"));
				pu.setPrice(rs.getFloat("price"));
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
