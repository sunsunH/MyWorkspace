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

import bean.Discuss;
import bean.Product_ShopItem;
import bean.Usr;
import dao.DiscussDAO;
import dao.Product_ShopItemDAO;
import dao.ShopDAO;

/**
 * Servlet implementation class AddDiscussServlet
 */
@WebServlet("/AddDiscussServlet")
public class AddDiscussServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public AddDiscussServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		String productid=request.getParameter("productid");	
		System.out.print(productid);
		String cas=request.getParameter("cas");
		cas = new String(cas.getBytes("iso-8859-1"),"UTF-8");
		HttpSession session = request.getSession();
		Usr user = (Usr) session.getAttribute("users");
		String forward;
		if(user==null){
			forward="Afail.jsp";
		}else{
			DiscussDAO dao=new DiscussDAO();
			List<Discuss> discuss=dao.getAllDiscuss();
			request.setAttribute("discusss",discuss);
			if(cas!=null){  
				dao.insert(user,Integer.valueOf(productid),cas);			
			}	
			forward="Dissuccess.jsp";
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
