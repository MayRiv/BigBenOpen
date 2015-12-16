<?php getView("HeaderView.inc", $obj);?>
<body>
	<table class="table_dark">
		<tr><th>Игрок</th><th>Баллы за роль</th><th>Лучшие</th><th>Сюрприз</th><th>Штрафы</th></tr>
<?php 
	//echo "<tr><td>".$obj['game']['."</td><td></td><td></td><td></td>|
	$i = 1;
	foreach ($obj['players'] as $player) {
	echo "<tr><td>".$i++."</td><td>".$player['player']."</td><td>".$player['Role']."</td><td>".$player['BestVotes']."</td><td>".$player['Surprise']."</td><td>".$player['Penalty']."</td></tr>";
	if ($player['WasShotFirst'])
		$firstBlood = $player;
}

	echo "</table><div id='feed>'"

	echo "<p>Первоубиенный ".$firstBlood['Name']."Попал в ".$firstBlood['BestMove']." черных игроков</p>"
	echo "<p>Победила команда: ".$obj['game']["Status"]."</p>";
	echo "<p>Ведущий: ".$obj['game']["MasterName"]."</p>";
?>
	</div>
<?php getView("Footer.inc", $obj);?>

</body>