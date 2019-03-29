 <%@ page contentType="text/html; charset=UTF-8" language="java" import="java.sql.*,bean.Usr" errorPage="" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>购物车</title>
<link href="css/bootstrap.css" rel="stylesheet" type="text/css" media="all" />
<!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
<script src="js/jquery.min.js"></script>
<!-- Custom Theme files -->
<!--theme-style-->
<link href="css/style.css" rel="stylesheet" type="text/css" media="all" />	
<link href="css/test3.css" rel="stylesheet" type="text/css" media="all" />	
<!--//theme-style-->
<script>
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
			<div class="ckeck-top heading">
			</div>
			<div class="ckeckout-top">
			<div class="cart-items">
			 <h2>我的购物车</h2><br/>
			<div class="in-check" >
				<ul class="unit">
					<li><span><font color="#fff">商品图片</font-color></span></li>
					<li><span><font color="#fff">商品名称</font-color></span></li>		
					<li><span><font color="#fff">商品价格</font-color></span></li>
					<li><span><font color="#fff">购买数量</font-color></span></li>
					<li> </li>
					<div class="clearfix"> </div>
				</ul>
				<c:forEach var="product" items="${requestScope.product_shopitems}">
				<form name="form1" action="AddOrdersServlet" method="get">
				<ul class="cart-header">
						<li class="ring-in"><ul class="slides">
			<div class="thumb-image">
			<img src="images/${product.imagepath}" data-imagezoom="true" class="img-responsive "  alt="" width="100px"height="100px"></div>	
			</ul>	
						</li>
						<li><span class="name">${product.productname}<input readonly type="hidden" value="${product.id}" name="productid"/></span></li>
						<li><span class="cost">¥$<input readonly  value="${product.price}" name="price"/><br/>购买数量不多于:<input readonly  value="${product.stock}" name="stock"/>
						                                       <input readonly type="hidden" value="${product.shopid}" name="shopid"/></li>
						<li><span>
						<ul class="btn-numbox">							
				            <ul class="count">				     
					            <li><input type="text" class="input-num" id="input-num" value="${product.quantity}" name="quantity"/></li>
					            <input type="submit" value="删除" name="submit"  onclick="return check()"/>
					           <input type="submit" value="立即购买" name="submit"  onclick="return check()"/>
					        
				            </ul>					           
				            </ul>	                   
						</span></li>
					<div class="clearfix"> </div>
				</ul>
				</form>
				</c:forEach>
				
			</div>
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

