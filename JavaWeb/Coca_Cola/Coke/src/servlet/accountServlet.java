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
import dao.UsrDAO;

/**
 * Servlet implementation class accountServlet
 */
@WebServlet("/accountServlet")
public class accountServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public accountServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		String username =request.getParameter("username");
	    String password =request.getParameter("password");
	    username = new String(username.getBytes("iso-8859-1"),"UTF-8");
	    password = new String(password.getBytes("iso-8859-1"),"UTF-8");
		UsrDAO dao=new UsrDAO();
	    Usr user=dao.logIn(username, password);
	    if(user!=null){
			HttpSession session= request.getSession();
			session.setAttribute("users", user);			
			RequestDispatcher rd=request.getRequestDispatcher("Asuccess.jsp");
			rd.forward(request, response);	
		} else{
			RequestDispatcher rd=request.getRequestDispatcher("Afail.jsp");
			rd.forward(request, response);
		}	
	}
}
