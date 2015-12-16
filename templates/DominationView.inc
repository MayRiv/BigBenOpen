<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<h1>Доминация</h1>

	<p>Чтобы получить статистику общих игр двух игроков введите их ники и нажмите "Сравнить"</p> 
	<p><input id='ComparePlayer1' name="Player1" type="text"/><input id='ComparePlayer2' name="Player2" type="text"/></p> 
	<p><input type="button" value="Сравнить" onclick="bbr.tryGetDomination()"/></p>

<?php
	//var_dump($obj['domination']);
	if (isset($obj['domination']) && $obj['domination']->status)
	{
		echo '<body><table class="table_dark"><caption>Статистика совместных игр</caption>';
		echo "	<tr><th>Роли</th><th>Всего игр</th><th>Побед у ".$obj['domination']->comparePlayer1."</th><th>Побед у ".$obj['domination']->comparePlayer2."</th></tr>";
		
		echo "<tr><td>Оба красных</td><td>".$obj['domination']->BRed['total']."</td><td>".$obj['domination']->BRed['v1']."</td><td>".$obj['domination']->BRed['v2']."</td></tr>";
		echo "<tr><td>Оба черных</td><td>".$obj['domination']->BBlack['total']."</td><td>".$obj['domination']->BBlack['v1']."</td><td>".$obj['domination']->BBlack['v2']."</td></tr>";
		echo "<tr><td>".$obj['domination']->comparePlayer1." красный, ".$obj['domination']->comparePlayer2." черный</td><td>".$obj['domination']->RB['total']."</td><td>".$obj['domination']->RB['v1']."</td><td>".$obj['domination']->RB['v2']."</td></tr>";
		echo "<tr><td>".$obj['domination']->comparePlayer1." черный, ".$obj['domination']->comparePlayer2." красный</td><td>".$obj['domination']->BR['total']."</td><td>".$obj['domination']->BR['v1']."</td><td>".$obj['domination']->BR['v2']."</td></tr>";
		echo '</table>';
		if (isset($obj['domination']->BR['s']))
			echo "<p>".$obj['domination']->comparePlayer1." застрелил ".$obj['domination']->comparePlayer2." ". $obj['domination']->BR['s']." раз</p>";
		if (isset($obj['domination']->RB['s']))
			echo "<p>".$obj['domination']->comparePlayer2 ." застрелил ".$obj['domination']->comparePlayer1 ." ". $obj['domination']->RB['s']." раз</p>";
		echo "<div><p>Сыграли в играх: ";
		foreach ($obj['domination']->games as $game) {
			echo "<a href='?action=showGame&GameId=".$game['id']."'>".$game['id']."</a> ";
		}
		echo "</p></div>";
	}
?>
</div>
<datalist id="players_list">
<?php	foreach ($obj['players'] as $player)
			if (!($player['Status'] === "Master" || $player['Status'] === "Admin"))
    			echo "<option>".$player['Name']."</option>";?>
</datalist>

<script type="text/javascript">
<?php
	$names = "var availableTags = [";
	foreach ($obj['players'] as $player)
    	$names .= '"'.$player["Name"].'",';
    $names[strlen($names) - 1] = ']';
    echo $names.";";

	echo "$( \"#ComparePlayer1\" ).autocomplete({source: availableTags});";

	echo "$( \"#ComparePlayer2\" ).autocomplete({source: availableTags});";
?>
</script>

<?php getView("Footer.inc", null); ?>
</body>
