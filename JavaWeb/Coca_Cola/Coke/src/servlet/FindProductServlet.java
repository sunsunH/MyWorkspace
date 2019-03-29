package servlet;

import java.io.IOException;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import bean.Product;
import dao.ProductDAO;

/**
 * Servlet implementation class selectShopServlet
 */
@WebServlet("/FindProductServlet")
public class FindProductServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public FindProductServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		String key=request.getParameter("search");
		key = new String(key.getBytes("iso-8859-1"),"UTF-8");
		ProductDAO dao=new ProductDAO();
    	List<Product>products=dao.getAllProduct(key);  
    	request.setAttribute("products", products);
		RequestDispatcher rd = request.getRequestDispatcher("showProduct.jsp");
		rd.forward(request, response);
	}
}
