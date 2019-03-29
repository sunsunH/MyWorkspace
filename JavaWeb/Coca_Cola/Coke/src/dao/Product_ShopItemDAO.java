package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import bean.Product_ShopItem;
import util.DataAccess;

public class Product_ShopItemDAO {
	public List<Product_ShopItem>getProduct_ShopItem(Integer shopid){
		Connection con=DataAccess.getConnection();
		String sql="select product.*,shopitem.quantity,shopitem.shopid from product,shopitem where product.id=shopitem.productid and shopid=?;";
		List<Product_ShopItem>list=new ArrayList<Product_ShopItem>();
		PreparedStatement pst=null;
		ResultSet rs=null;
		try{
			pst=con.prepareStatement(sql);
			pst.setInt(1,shopid);
			rs=pst.executeQuery();
			while(rs.next()){
				Product_ShopItem pu=new Product_ShopItem();
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
				pu.setShopid(rs.getInt("shopid"));
				pu.setQuantity(rs.getInt("quantity"));
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
