<?php getView("HeaderView.inc", $obj);?>
<body>
	<table class="table_dark">
<?php
	if ($obj['type'] == "games")
	{
		$isAdmin = false;
		if (($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			$isAdmin = true;
		echo "<p><a href='?action=showGames'>Назад</a></p>";
		echo "<tr><th>Дата</th><th>Зал</th><th>Ведущий</th><th>Подробно</th>";
		if ($isAdmin)
		{
			echo "<th>Редактировать</th>";
			echo "<th>Удалить</th>";
		}
		echo "</tr>";
		foreach ($obj['games'] as $date => $games) {
			foreach ($games as $game) {
				echo "<tr><td>$date</td><td>".$game[2]."</td><td>$game[0]</td><td><a href='?action=showGame&GameId=$game[1]'>Игра №".$game[1]."</a></td>";
				if ($isAdmin)
				{
					echo "<td><a href='?action=editGame&GameId=$game[1]'><img src='Pictures/edit.png'></a></td>";
					//echo "<td><a href='?action=deleteGame&GameId=$game[1]'><img src='Pictures/delete.png'></a>";
					echo "<td><img src='Pictures/delete.png' onclick='bbr.tryDelete($game[1])' onMouseOver='this.style.cursor=\"pointer\"'/></td>";
				}
				echo "</tr>";
			}
		}
	}
	else if ($obj['type'] == "dates")
	{
		echo "<tr><th>Дата</th><th>Посмотреть игры</th></tr>";
		foreach ($obj['dates'] as $date) {
				echo "<tr><td>".$date['date']."</td><td><a href='?action=showGames&date=".$date['date']."'>Перейти к играм</a></td></tr>";
		}
	}

?>
	</table>
<?php getView("Footer.inc", $obj);?>

</body>
