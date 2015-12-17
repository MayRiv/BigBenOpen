<?php getView("HeaderView.inc", null); ?>
<div id="feed"><h2>BigBen Rating</h2>
<?php
	echo "<p>Рейтинг игроков за период от $obj->date1 до $obj->date2.</p></div>";
?>
<table class="table_dark">
		<tr><th>#</th><th>Игрок</th><th>Сыграно игр</th><th>Победы</th><th>Количество лучших</th><th>Рейтинг</th></tr>
<?php
	{
		$i = 1;
		$others = array();
		foreach ($obj->rating as $player=>$stat) 
			{
			
				//echo "<tr><td>$i</th><td>".$stat['stat']."</td><td>".(int)(1000 * $stat['r'])."</td><td>".$stat['t']."</td><td>";
				echo "<tr><td>$i</th><td>$player</td><td>0</td><td>";
				$percent = round($stat['v'] / 7* 100, 2);
				echo $stat['v']." ($percent%)";
				echo"</td><td>".$stat['p']."</td>";
				echo "</tr>";
			}
	}
?>
</table>
<?php getView("Footer.inc", null); ?>
</body>
