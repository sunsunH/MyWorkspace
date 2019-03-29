package util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DataAccess {
	final static String url="jdbc:mysql://localhost:3306/coke?useUnicode=true&characterEncoding=utf8&useSSL=false";
    final static String username = "root";
    final static String password = "123456";
    public static Connection getConnection(){
        Connection conn=null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn=DriverManager.getConnection(url,username,password);
        } catch (ClassNotFoundException e) {
              e.printStackTrace();
        } catch (SQLException e) {
              e.printStackTrace();
        }
    return conn;
    }

}
