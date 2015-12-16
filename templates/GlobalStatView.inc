<?php getView("HeaderView.inc", null); ?>
<div id="feed"><h2>Глобальная статистика</h2>
<?php
foreach ($obj->top as $role=>$stat) {

	 echo "<table class='table_dark'>
	 <caption>Top-3 $role</caption>
	 <th>Игрок</th><th>Сыграно игр</th><th>Винрейт</th><th>Количество лучших</th>";

	 foreach ($stat as $player) {
	 	echo "<tr><td>".$player['player']."</td><td>".$player['t']."</td><td>".round($player['r'], 2)."</td><td>".$player['b']."</td></tr>";
	 }
	 echo "</table>";

}
?>
</div>
<?php getView("Footer.inc", null); ?>
</body>
