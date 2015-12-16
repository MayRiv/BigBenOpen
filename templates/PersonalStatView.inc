<?php $params = array('jQuerySwitchOff'=>true);
getView("HeaderView.inc", $params ); ?>
<div id="feed">
	<h1>Личный кабинет</h1>
	<?php
		//$obj->show();
		echo "<div><h2>Статистика игрока $obj->player</h2>";
		echo "<p>Получил $obj->bestVotes лучших</p>";
		echo "<p>Убит в первую ночь $obj->firstBloodCount раз</p>";
		foreach ($obj->roomGameCount as $roomId => $gameCount) {
			echo "<p>Сыграл $gameCount игр в $roomId зале</p>";
		}
			
		if($obj->firstBloodCount)
			echo "<p>В среднем $obj->averageBestMove черных в лучшем ходе</p></div>";
		

		echo '<body><table class="table_dark">';
		echo "<tr><th>Роль</th><th>Всего сыграно</th><th>Побед</th>";
		echo	"<tr><td>Всего</td><td>$obj->totalGamesCount</td><td>$obj->totalVictoryCount</th></td>";
		echo	"<tr><td>Красный</td><td>$obj->totalRedCountGames</td><td>$obj->totalRedVictoryGames</th></td>";
		echo	"<tr><td>Черный</td><td>$obj->totalBlackCountGames</td><td>$obj->totalBlackVictoryGames</th></td>";
		
		echo "<tr><th colspan='3'>Подробно</th></tr>";
		echo	"<tr><td>Мирный житель</td><td>$obj->citizensGameCount</td><td>$obj->citizensVictoryCount</td></tr>";
		echo	"<tr><td>Шериф</td><td>$obj->sherifGameCount</td><td>$obj->sherifVictoryCount</td></tr>";
		echo	"<tr><td>Мафия</td><td>$obj->mafiaGameCount</td><td>$obj->mafiaVictoryCount</td></tr>";
		echo	"<tr><td>Дон</td><td>$obj->donGameCount</td><td>$obj->donVictoryCount</th></td>";
		
		echo '</table>';

		echo "<div><p>Сыграл в играх: ";
		foreach ($obj->games as $game) {
			echo "<a href='?action=showGame&GameId=".$game."'>".$game."</a> ";
		}
		echo "</p></div>";
		/*echo "<p>График побед игровыми ролям по неделям.</p>";
		echo '<div  style="margin:auto;"><p><noscript><strong style="color: red;">Для отображения данных необходимо включить JavaScript!</strong></noscript></p>
    <div id="placeholder" style="height:300px;"></div>
    <div>
      <div id="legend"></div>
      <p style="text-align: center;"><a href="#" onclick="switch_show(); return false;">Сменить вид</a></p>
    </div>
    <div style="clear: both;"></div>
    <div id="overview" style="margin-top:20px;width:600px;height:50px;display: inline-block;"></div></div>';
		$games= '<script language="javascript" type="text/javascript">var all_data = [{ label: "Все роли сыграно", color: 0, data: [';
		$start = null;
		foreach ($obj->stat as $date => $stat) {
			if (!isset($start))
				$start = $date;
			$end = $date;
			$games .= "[\"$date\",".(isset($stat['general']['total'])?$stat['general']['total']:0) ."],";
		}
		$games[strlen($games) - 1] = ']';
		$games .= "},";

		$games .= '{ label: "Все роли победы", color: 1, data: [';
		foreach ($obj->stat as $date => $stat) {
			$games .= "[\"$date\",".(isset($stat['general']['victories'])?$stat['general']['victories']:0) ."],";
		}
		$games[strlen($games) - 1] = ']';

		$games .= "}];";

		echo $games;
		echo "var selection = [\"$start\", \"$end\"];";
		getView("DrawScriptRawPart.inc", null);*/
	?>

<p><a href="?action=changePassword">Сменить пароль</a></p>
</div>

<?php getView("Footer.inc", null); ?>
</body>