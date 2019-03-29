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
import dao.UsrDAO;

/**
 * Servlet implementation class registerHandleServlet
 */
@WebServlet("/registerServlet")
public class registerServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public registerServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		HttpSession session=request.getSession();
		session.invalidate();
		String username=request.getParameter("username");
		String password=request.getParameter("password1");
		username = new String(username.getBytes("iso-8859-1"),"UTF-8");
		password = new String(password.getBytes("iso-8859-1"),"UTF-8");
		Usr user=new Usr();
		user.setUsername(username);
		user.setPassword(password);
		UsrDAO dao1=new UsrDAO();
		boolean flag1=dao1.Register(user);
		user=dao1.logIn(username, password);
		ShopDAO dao2=new ShopDAO();	
		String forward="Rfail.jsp";
		if(flag1){
			boolean flag2=dao2.Register(user);
			if(flag2){
				forward="Rsuccess.jsp";
		
			}else{			
				forward="Rfail.jsp";			
		    }			
		}else{			
			forward="Rfail.jsp";	

		}
		RequestDispatcher rd=request.getRequestDispatcher(forward);
		rd.forward(request, response);
	}

}
