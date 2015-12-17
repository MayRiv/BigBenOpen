<?php getView("HeaderView.inc", null); ?>
<div id="feed"><h2>BigBen Rating</h2>
<?php
	echo "<p>Рейтинг игроков.</p></div>";
?>
<table class="table_dark">
		<tr><th>#</th><th>Игрок</th><th>Победы</th><th>Рейтинг</th></tr>
<?php
	{
		$i = 1;
		$others = array();
		foreach ($obj->rating as $player=>$stat) 
			{
			
				echo "<tr><td>$i</th><td>".$player."</td><td>".$stat['v']."</td><td>".$stat['p']."</td>";
				echo "</tr>";
				$i++;
			}
	}
?>
</table>
<?php getView("Footer.inc", null); ?>
</body>
