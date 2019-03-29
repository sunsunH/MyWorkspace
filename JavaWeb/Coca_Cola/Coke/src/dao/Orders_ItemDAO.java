package dao;

import java.sql.Connection;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import bean.Orders_Item;
import bean.Usr;
import util.DataAccess;

public class Orders_ItemDAO {
	public List<Orders_Item>getOrders_Item(Usr u){
		Connection con=DataAccess.getConnection();
		String sql="select orders.*,ordersitem.productid,ordersitem.quantity,ordersitem.price from orders,ordersitem where orders.id=ordersitem.ordersid and orders.usrid=?;";
		List<Orders_Item>list=new ArrayList<Orders_Item>();
		PreparedStatement pst=null;
		ResultSet rs=null;
		try{
			pst=con.prepareStatement(sql);
			pst.setInt(1,u.getId());
			rs=pst.executeQuery();
			while(rs.next()){
				Orders_Item pu=new Orders_Item();
				pu.setId(rs.getInt("id"));
				pu.setCreatetime(rs.getDate("createtime"));
				pu.setProductid(rs.getInt("productid"));
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
