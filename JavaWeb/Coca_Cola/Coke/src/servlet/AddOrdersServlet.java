package servlet;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import bean.Product_ShopItem;
import bean.Usr;
import dao.OrdersDAO;
import dao.OrdersItemDAO;
import dao.ProductDAO;
import dao.ShopDAO;
import dao.ShopItemDAO;

/**
 * Servlet implementation class AddOrdersServlet
 */
@WebServlet("/AddOrdersServlet")
public class AddOrdersServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public AddOrdersServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		String submit=request.getParameter("submit");
		String productid=request.getParameter("productid");
		String quantity=request.getParameter("quantity");
		String stock=request.getParameter("stock");
		String shopid=request.getParameter("shopid");
		String price=request.getParameter("price");
		submit = new String(submit.getBytes("iso-8859-1"),"UTF-8");
		HttpSession session = request.getSession();
		Usr user = (Usr) session.getAttribute("users");
		String forward="Afail.jsp";
		if(user==null){
			forward="Afail.jsp";
		}else{
			if(submit.equalsIgnoreCase("Á¢¼´¹ºÂò")){
				if(Integer.valueOf(quantity)<=Integer.valueOf(stock)){
				OrdersDAO dao1=new OrdersDAO();
				dao1.insert(user);
				Integer ordersid=dao1.select();
				ProductDAO dao2=new ProductDAO();
				dao2.Update(Integer.valueOf(quantity), productid);
				ShopItemDAO dao3=new ShopItemDAO();
				dao3.Delete(shopid, productid);
				OrdersItemDAO dao4=new OrdersItemDAO();
				dao4.insert(ordersid,productid,Integer.valueOf(quantity),Float.valueOf(price));
				forward="Bsuccess.jsp";
			}	
		}else{
			ShopItemDAO dao3=new ShopItemDAO();
			dao3.Delete(shopid, productid);
			forward="Dsuccess.jsp";
		}
					
		}		
		RequestDispatcher rd=request.getRequestDispatcher(forward);
		rd.forward(request, response);
	}

}
