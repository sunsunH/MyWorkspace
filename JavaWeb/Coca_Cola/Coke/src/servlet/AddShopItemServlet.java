package servlet;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import bean.Usr;
import dao.ShopDAO;
import dao.ShopItemDAO;

/**
 * Servlet implementation class AddShopItem
 */
@WebServlet("/AddShopItemServlet")
public class AddShopItemServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public AddShopItemServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		String productid=request.getParameter("productid");
		HttpSession session = request.getSession();
		Usr user = (Usr) session.getAttribute("users");
		String forward="Afail.jsp";
		if(user==null){
			forward="Afail.jsp";
		}else{
			//user.getId();
			ShopDAO dao2=new ShopDAO();
			Integer shopid=dao2.select(user);
			ShopItemDAO dao3=new ShopItemDAO();
			Integer shop=dao3.check(shopid, productid);
			if(shop!=null){
				dao3.Update(shopid, productid);
			}else{
				dao3.add(shopid, productid);
			}		
			forward="Addsuccess.jsp";
		}		
		RequestDispatcher rd=request.getRequestDispatcher(forward);
		rd.forward(request, response);
	}

}
