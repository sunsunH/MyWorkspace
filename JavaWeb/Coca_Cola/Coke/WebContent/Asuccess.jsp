<%@ page contentType="text/html; charset=UTF-8" language="java" import="java.sql.*" errorPage="" %>
<%@page import="bean.Usr"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>登录成功</title>
<link href="css/bootstrap.css" rel="stylesheet" type="text/css" media="all" />
<!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
<script src="js/jquery.min.js"></script>
<!-- Custom Theme files -->
<!--theme-style-->
<link href="css/style.css" rel="stylesheet" type="text/css" media="all" />	
<!--//theme-style-->
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="keywords" content="Sport Responsive web template, Bootstrap Web Templates, Flat Web Templates, Andriod Compatible web template, 
Smartphone Compatible web template, free webdesigns for Nokia, Samsung, LG, SonyErricsson, Motorola web design" />
<script type="application/x-javascript"> 
addEventListener("load", function() { setTimeout(hideURLbar, 0); }, false); 
function hideURLbar(){ window.scrollTo(0,1); } </script>
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
							<form name="form" action="FindProductServlet" method="get">
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
					<!-- //search-scripts -->
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
		<div class="col-md-4 bottom-grid2">
				<div class="container">
		<div class="register">	
		<div class=" register-top">
			<center>
                <form name="form" action="index.jsp" method="get">
               <p style='color:red;font-size:50px;'>登录成功!</p>
                                                   用户名:<%= user.getUsername()%>
              <a href="#" onClick="history.back();return false;"><input type="submit" value="返回" name="返回"/> </a>
                </form>
                   </center>

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