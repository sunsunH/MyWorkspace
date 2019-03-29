package servlet;

import java.io.IOException;


import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;


import bean.Product_ShopItem;
import bean.Usr;

import dao.Product_ShopItemDAO;
import dao.ShopDAO;

/**
 * Servlet implementation class FindShopItemServlet
 */
@WebServlet("/FindShopItemServlet")
public class FindShopItemServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public FindShopItemServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		HttpSession session = request.getSession();
		Usr user = (Usr) session.getAttribute("users");
		String forward;
		if(user==null){
			forward="Afail.jsp";
		}else{
			ShopDAO dao1=new ShopDAO();
			Integer shopid=dao1.select(user);
	    	Product_ShopItemDAO dao2=new Product_ShopItemDAO();
	    	List<Product_ShopItem>product_shopitems=dao2.getProduct_ShopItem(shopid);  
	    	request.setAttribute("product_shopitems",product_shopitems);
			forward="showShop.jsp";
		}		
		RequestDispatcher rd=request.getRequestDispatcher(forward);
		rd.forward(request, response);
		
	}
}
