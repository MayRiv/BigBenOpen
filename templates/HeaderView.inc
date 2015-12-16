<html>
<head>
	<link rel="stylesheet" type="text/css" href="templates/bigbenrating.css"/>
	<link rel="stylesheet" type="text/css" href="templates/auto-complete.css">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<script type="text/javascript" src="js/bigbenrating.js"></script>
	<script language="javascript" type="text/javascript" src="js/flot/jquery.js"></script>
    <script language="javascript" type="text/javascript" src="js/flot/jquery.flot.js"></script>
    <script language="javascript" type="text/javascript" src="js/flot/jquery.flot.stack.js"></script>
    <script language="javascript" type="text/javascript" src="js/flot/jquery.flot.selection.js"></script>
	<script src="http://code.jquery.com/jquery-1.8.3.js"></script>
  	<script src="js/jquery-ui-1.11.4/jquery-ui.js"></script>
  	<link type="text/css" href="js/jquery-ui-1.11.4/jquery-ui.css" rel="stylesheet" />
    <script type="text/javascript" src="js/auto-complete.min.js"></script>
</head>
<body>
	<div id="auth-div" style="float:right">
		<?php
		if (isset($_SESSION['isAuth']) && $_SESSION['isAuth'] == 1)
		{
			echo "<p>Привет, ".$_SESSION['player']."</p>";
			echo "<a href='?action=logout'>Выйти</a>";
		}
		else
		{
			echo "<a href='?action=login'>Авторизироваться</a>";
		}
		?>
	</div>
	<div style="text-align: center"><h1>Рейтинг клуба BigBen</h1></div>
	<div id="css-menu-wrapper">
		<div id="css-menu">
			<ul>
				<li><a href="/?action=getRating">
					<span class="text-top">Общий рейтинг</span>
					<span class="text-bottom">Рейтинг игроков</span>
				</a></li>
				<li><a href="/?action=getPersonalStat">
					<span class="text-top">Личный кабинет</span>
					<span class="text-bottom">Статистика игрока</span>
				</a></li>
				<li><a href="/?action=getGlobalStat">
					<span class="text-top">Глобальная статистика</span>
					<span class="text-bottom">Топы игроков</span>
				</a></li>
				<li><a href="/?action=getDomination">
					<span class="text-top">Парная статистика</span>
					<span class="text-bottom">Доминация</span>
				</a></li>
				<li><a href="/?action=getPowerMap">
					<span class="text-top">Групповая статистика</span>
					<span class="text-bottom">Карта силы</span>
				</a></li>
				<li><a href="/?action=showGames">
					<span class="text-top">Подробно про игры</span>
					<span class="text-bottom">История игр</span>
				</a></li>
				<?php
				if ($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin"))
				echo '<li><a href="/?action=showAdminPanel">
					<span class="text-top">Административная панель</span>
					<span class="text-bottom">Для ведущих</span>
				</a></li>';
				?>
			</ul>
		</div>
	</div>
