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

import bean.Orders_Item;
import bean.Usr;
import dao.OrdersDAO;
import dao.Orders_ItemDAO;

/**
 * Servlet implementation class FindOrdersServlet
 */
@WebServlet("/FindOrdersServlet")
public class FindOrdersServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public FindOrdersServlet() {
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
			Orders_ItemDAO dao=new Orders_ItemDAO();
	    	List<Orders_Item>orders_items=dao.getOrders_Item(user);  
	    	request.setAttribute("orders_items",orders_items);
			forward="showOrders.jsp";
		}		
		RequestDispatcher rd=request.getRequestDispatcher(forward);
		rd.forward(request, response);

	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
