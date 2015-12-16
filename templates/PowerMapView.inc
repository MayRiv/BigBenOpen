<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<h1>Карта силы</h1>
	<body><table class="table_dark"><caption>Статистика совместных игр</caption>
		<tr><th>Ник игрока</th><th>Баланс побед</th><th>Количество игр</th></tr>
<?php
{
function cmpDom($a, $b) {
   	if ($a[0] == $b[0]) {
        return 0;
    }
    return ($a[0] > $b[0]) ? -1 : 1;
}
		$players = uasort($obj->map, 'cmpDom');
		$zeroPlayerInserted = false;
		foreach ($obj->map as $player => $domination) {
			if ($domination[0]==0 && !$zeroPlayerInserted)
			{
				echo "<tr style='color:#00FF00'><td colspan=3>".$_SESSION['player']."</td></tr>";
				$zeroPlayerInserted = true;
			}
			if ($domination[1])
				echo "<tr><td><a href='?action=getDomination&ComparePlayer1=".urlencode($_SESSION['player'])."&ComparePlayer2=".urlencode($player)."'>$player</a></td><td>$domination[0]</td><td>$domination[1]</td></tr>";
		}
		echo '</table>';
}
?>
</div>
<?php getView("Footer.inc", null); ?>
</body>
