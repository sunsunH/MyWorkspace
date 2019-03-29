<%@ page contentType="text/html; charset=UTF-8" language="java" import="java.sql.*" errorPage="" %>
<%@ page import="javax.servlet.http.HttpSession"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>Coca-Cola首页</title>
<link href="css/bootstrap.css" rel="stylesheet" type="text/css" media="all" />
<!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
<script src="js/jquery.min.js"></script>
<!-- Custom Theme files -->
<!--theme-style-->
<link href="css/style.css" rel="stylesheet" type="text/css" media="all" />	
<!--//theme-style-->
<script> 
function check(){
	   if(form.username.value==""){
	      alert("用户名不能为空！");
	      form.username.focus();
	      return false;
	   }else if(form.password1.value==""){
	      alert("密码不能为空！");
	      form.password1.focus();
	      return false;
	   }
}
</script>
</head>

<body>
<jsp:useBean id="user" class="bean.Usr" scope="session"></jsp:useBean>
<jsp:setProperty property="*" name="user"/>
<!--header-->
	<div class="line">	
	</div>
	<div class="header">
		<div class="logo">
			<a href="index.jsp"><img src="images/logo1.png" alt="" width="100" height="100"></a>
		</div>
		<div  class="header-top">
			<div class="header-grid">
				<ul class="header-in">			
					</ul>
					<div class="search-box">
					    <div id="sb-search" class="sb-search">
							<form name="form1" action="FindProductServlet" method="get">
								<input class="sb-search-input" placeholder="输入你要搜索的物品..." type="search" name="search" id="search">
								<input class="sb-search-submit" type="submit" value="">
								<span class="sb-icon-search"> </span>
							</form>
						</div>
				    </div>
					<!-- search-scripts -->
					<script src="js/classie.js"></script>
					<script src="js/uisearch.js"></script>
						<script>
							new UISearch( document.getElementById( 'sb-search' ) );
						</script>
					<div class="clearfix"> </div>
			</div>
			<div class="header-bottom">
				<div class="h_menu4"><!-- start h_menu4 -->
				<a class="toggleMenu" href="#">菜单</a>
				<ul class="nav">
					<li class="active"><a href="index.jsp">首页</a></li>				
					<li><a href="FindProductServlet?search=碳酸饮料">碳酸饮料</a></li>					
					<li><a href="FindProductServlet?search=果汁">果汁</a></li>
					<li><a href="FindProductServlet?search=咖啡">咖啡</a></li>
					<li><a href="FindProductServlet?search=水">饮用水</a></li>
					<li><a href="">更多 <i> </i></a>
						<ul>
							<li><a href="FindOrdersServlet">订单</a></li>
							<li><a href="FindShopItemServlet">购物车</a></li>
                            <li><a href="register.jsp">注册</a></li>						
                       </ul>
				   </li>
				   <li><a href="">用户名:<%= user.getUsername()%><i> </i></a>
						<ul>
							 <li><a href='LogoutServlet'>注销</a></li>					
                       </ul>
				   </li>
				</ul>
				<script type="text/javascript" src="js/nav.js"></script>
			</div><!-- end h_menu4 -->
			<div class="clearfix"> </div>
		</div>
		</div>
		<div class="clearfix"> </div>
	</div>
	<!---->	
	<div class="banner">
	<div class="container">
		<div class="banner-matter">
			<h1>一路有你 可口可乐<span>Coca-Cola</h1>
			<div class="out">
				<a href="FindDiscussServlet" class="find">发现更多 </a>
				<a href="FindProductServlet?search=味" class="shop">购物</a>
				<div class="clearfix"> </div>
			</div>
		</div>	
		</div>
	</div>
<!---->
<div class="content">
	<div class="sport-your">
<!-- requried-jsfiles-for owl -->
							<link href="css/owl.carousel.css" rel="stylesheet">
							    <script src="js/owl.carousel.js"></script>
							        <script>
									    $(document).ready(function() {
									      $("#owl-demo").owlCarousel({
									        items : 5,
									        lazyLoad : true,
									        autoPlay : true,
									        navigation : true,
									        navigationText :  true,
									        pagination : false
									      });
									    });
									  </script>
							 <!-- //requried-jsfiles-for owl -->

		<!-- start content_slider -->
		<div class="line1">	
		</div>
		<div class="line2">
		</div>
	</div>
		<!--//sreen-gallery-cursual---->
	<div class="content-bottom">
		<div class="col-md-8 bottom-content">
			<script src="js/responsiveslides.min.js"></script>
					<script>
						$(function () {
						  $("#slider").responsiveSlides({
							auto: true,
							speed: 500,
							namespace: "callbacks",
							pager: false,
							 nav:true
						  });
						});
					</script>
					<div class="slider">
						<div class="callbacks_container">
						  <ul class="rslides" id="slider">
							<li>
							  <img src="images/GD1.jpg" alt="">
							  
							</li>
							<li>
							  <img src="images/GD2.jpg" alt="">
								
							</li>
							<li>
							  <img src="images/GD3.jpg" alt="">
							  
							</li>
						  </ul>
					  </div>
					</div>

		</div>
		<div class="col-md-4 bottom-grid">
				<div class="container">
		<div class="account">
		<div class="account-pass">
		<div class="col-md-7 account-top">
		<%
		  if(user.getUsername()==null){%>
			<form name="form" action="accountServlet" method="get">	
			<div> 	
					<span><h3><font size="10"></>账户</font></h3></span></br>
				<span>用户名</span>
				<input type="text" name="username"/> 
			</div>
			<div> 
				<span >密码</span>
				<input type="password" name="password"/>
			</div>				
				<input type="submit" value="登录" id="Login" onclick="return check()"/> 
			</form>
		  <%}else{%>
			            <font size="10" color="red">您已登录<br/></>用户名:<%= user.getUsername()%></font>
		   <%}%>
		</div>
		<div class="col-md-5 left-account ">
			<!--  <a href="register.jsp" class="create">注册新账户</a>-->
<div class="clearfix"> </div>
		</div>
	<div class="clearfix"> </div>
	</div>
	</div>
</div>
		</div>
	<div class="clearfix"> </div>
	</div>
</div>	
<!--footer-->
		<div id="example1">
		<div id="owl-demo" class="owl-carousel text-center">
			<div class="item">
				<a href="single.jsp" title="image" rel="title1">
					<img class="img-responsive " src="images/TS1.jpg" alt="" width="371" height="296">
				<div class="run">
					<!--<i> </i>-->
					<p>可乐</p>
				</div>
				</a>
			</div>
			<div class="item">
				<a href="single.jsp" title="image" rel="title1">
					<img class="img-responsive " src="images/TS2.jpg" alt="" width="371" height="296">
				<div class="run">
					<!--  <i class="foot-in"> </i>-->
					<p>雪碧</p>
				</div>
				</a>
			</div>
			<div class="item">
				<a href="single.jsp" title="image" rel="title1">
					<img class="img-responsive " src="images/GZ1.jpg" alt="" width="371" height="296">
				<div class="run">
				<!--<i class="cycling"> </i>-->
				<p>果汁</p>
				</div>
				</a>
			</div>
			<div class="item">
				<a href="single.jsp" title="image" rel="title1">
					<img class="img-responsive " src="images/KF1.jpg" alt="" width="371" height="296">
				<div class="run">
				<!--<i class="fitness"> </i>-->
				<p>咖啡</p>
				</div>
				</a>
			</div>
			<div class="item">
				<a href="single.jsp" title="image" rel="title1">
					<img class="img-responsive " src="images/TS1.jpg" alt="" width="371" height="296">
				<div class="run">
				<!--<i class="tennis"> </i>-->
				<p>可乐</p>
				</div>
				</a>
			</div>
			<div class="item">
				<a href="single.jsp" title="image" rel="title1">
					<img class="img-responsive " src="images/TS2.jpg" alt="" width="371" height="296">
				<div class="run">
				<!--<i> </i>-->
				<p>雪碧</p>
				</div>
				</a>
			</div>
			<div class="item">
				<a href="single.jsp" title="image" rel="title1">
					<img class="img-responsive " src="images/GZ1.jpg" alt="" width="371" height="296">
				<div class="run">
					<!--<i class="foot-in"> </i>-->
					<p>果汁</p>
				</div>
				</a>
			</div>
			<div class="item">
				<a href="single.jsp" title="image" rel="title1">
					<img class="img-responsive " src="images/KF1.jpg" alt="" width="371" height="296">
				<div class="run">
				<!--<i class="cycling"> </i>-->
				<p>咖啡</p>
				</div>
				</a>
			</div>
			<div class="item">
				<a href="single.jsp" title="image" rel="title1">
					<img class="img-responsive " src="images/TS1.jpg" alt="" width="371" height="296">
				<div class="run">
				<!--<i class="fitness"> </i>-->
				<p>可乐</p>
				</div>
				</a>
			</div>
			<div class="item">
				<a href="single.jsp" title="image" rel="title1">
					<img class="img-responsive " src="images/TS2.jpg" alt="" width="371" height="296">
				<div class="run">
				<!--  <i class="tennis"> </i>-->
				<p>雪碧</p>
				</div>
				</a>
			</div>
			<div class="item">
				<a href="single.jsp" title="image" rel="title1">
					<img class="img-responsive " src="images/GZ1.jpg" alt="" width="371" height="296">
				  <div class="run">
				<!--<i> </i>-->
				<p>果汁</p>
				</div>
				</a>
			</div>
		</div>
		</div>
		<!--  <h6 class="your-in">你的可口可乐</h6>-->
		<div class="line2">
		</div>
</body>
</html>
