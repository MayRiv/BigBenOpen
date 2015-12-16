<?php getView("HeaderView.inc", null); ?>
<div id="feed"><h2>BigBen Rating</h2>
<?php
	echo "<p>Рейтинг игроков за период от $obj->date1 до $obj->date2.</p></div>";
?>
<table class="table_dark">
		<tr><th>#</th><th>Игрок</th><th>Сыграно игр</th><th>Победы</th><th>Количество лучших</th><th>Рейтинг</th></tr>
<?php
    //<tr><th>#</th><th>Игрок</th><th>Рейтинг</th><th>Сыграно игр</th><th>Победы</th><th>Количество лучших</th></tr>
	//if (($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
	{
		$i = 1;
		$others = array();
		foreach ($obj->players as $stat) 
			//if ($stat['t'] >= 15)		
			{
			
				//echo "<tr><td>$i</th><td>".$stat['stat']."</td><td>".(int)(1000 * $stat['r'])."</td><td>".$stat['t']."</td><td>";
				echo "<tr><td>$i</th><td>".$stat['p']."</td><td>".$stat['t']."</td><td>";
				$percent = round($stat['v'] / $stat['t'] * 100, 2);
				echo $stat['v']." ($percent%)";
				echo"</td><td>".$stat['b']."</td>";
				//if (($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
					echo "<td>".round($stat['r'], 2)."</td>";
				echo "</tr>";
				$i++;
			}
			/*else
			{
				$others[] = $stat;
			}*/
		/*echo "<tr><td colspan='6'>Игроки, сыгравшие менее 15 игр</td></tr>";
		foreach($others as $stat)
		{
			echo "<tr><td>$i</th><td>".$stat['stat']."</td><td>".(int)(1000 * $stat['r'])."</td><td>".$stat['t']."</td><td>";
				$percent = round($stat['v'] / $stat['t'] * 100, 2);
				echo $stat['v']."($percent%)";
				echo"</td><td>".$stat['b']."</td></tr>";
				$i++;
		}*/
	}
?>
</table>
<?php getView("Footer.inc", null); ?>
</body>
