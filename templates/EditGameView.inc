<?php getView("HeaderView.inc", NULL); ?>
		<form id='form' action='?action=editGame' method='post'>
		<input name='GameId' type='hidden'  value='<?=$obj["game"]->gameId?>'>
		<div id='feed'>
		<p>Выберите номер игрового зала
		<select name='RoomId'>
		<?php
		for($i = 1; $i < 5; $i++)
		{
			if ($i == $obj["game"]->roomId)
				echo "<option selected>$i</option>";
			else
				echo "<option>$i</option>";
		}
		?>
		</select></p>
		<p>Дата проведения игры <input type='date' name='date' value='<?=$obj["game"]->date?>' /></p>
		<p>Ведущий: <input type='text' name='Master' id='Master' value='<?=$obj["game"]->master?>'></p>
		<body><table>
		<tr><th>Игрок</th><th>Роль</th><th>Лучший</th><th>Фолы</th></tr>
		<?php
		$roles = array("Citizen", "Sherif","Mafia","Don");
		$i = 0;
		foreach ($obj["game"]->players as $name =>$player) 
		{
			echo "<tr><td><input type='text' name=Player$i id='Player$i'  value='$name'></td><td>
			<select id='Role$i' name='Role$i'>";
			foreach ($roles as $role) {
				if ($role === $player['Role'])
					echo "<option selected>$role</option>";
				else 
					echo "<option>$role</option>";
			}
		echo "</select></td><td>";
		if ($player['BestPlayer'] > 0)
			echo "<input type='checkbox' checked name='Best$i'/></td><td>";
		else 
			echo "<input type='checkbox' name='Best$i'/></td><td>";
		echo "<select name='Warnings$i'>";
			for($c =0; $c < 5; $c++)
				if ($c==$player['Warnings'])
					echo "<option selected>$c</option>";
				else 
					echo "<option>$c</option>";

			echo "</select></td></tr>";
			if ($player['WasShotFirst'])
			{
				$firstBlood['Name'] =$name;
				$firstBlood['BestMove'] =$player['BestMove'];
			}
			$i++;
		}

		echo '</table>';

		if (isset($firstBlood))
			echo "<p>Первоубиенный <input type='text' name='BestMovePlayer' id='FirstBlood' placeholder='Первоубиенный' value='".$firstBlood['Name']."' />";
			echo "Попал в <td><select name='BestMovePoints'>";
			for ($i = 0; $i < 4; $i++)
			{
				if ($i == $firstBlood['BestMove'])
					echo "<option selected value=$i>$i</option>";
				else if ($i != 1)
					echo "<option value=$i>$i</option>";
			}
		echo "</select> черных игроков</p>";
		if ($obj["game"]->status == 1)
			$victoryTeam = "Город";
		if ($obj["game"]->status == -1)
			$victoryTeam = "Мафия";
		if ($obj["game"]->status == 0)
			$victoryTeam = "Ничья";
		echo "<p>Победила команда: </p>";
		echo "<select name=\"result\">";
		$teams = array("City"=>"Мирных жителей", "Mafia"=>"Мафии", "Draw"=> "Ничья");
		if ($obj["game"]->status == 1)
			$victoryTeam = "City";
		if ($obj["game"]->status == -1)
			$victoryTeam = "Mafia";
		if ($obj["game"]->status == 0)
			$victoryTeam = "Draw";
		foreach ($teams as $team =>$message) {
			if ($team === $victoryTeam)
				echo "<option value='$team' selected>$message</option>";
			else
				echo "<option value='$team'>$message</option>";
		}
		?>

		<p><input type='button' value='Update' onclick='bbr.trySend()'/></p>
	</form>

	<script type="text/javascript">
<?php
$names = "var availableTags = [";
	foreach ($obj['players'] as $player)
    	$names .= '"'.$player["Name"].'",';
    $names[strlen($names) - 1] = ']';
    echo $names.";";
	for ($i=0; $i < 10; $i++) { 
		echo "$( \"#Player$i\" ).autocomplete({source: availableTags});";
	echo "$( \"#FirstBlood\" ).autocomplete({source: availableTags});";
}

$admins = "var admins = [";
	foreach ($obj['players'] as $player)
    	if ($player['Status'] === "Master" || $player['Status'] === "Admin")
    		$admins .= '"'.$player["Name"].'",';
    $admins[strlen($admins) - 1] = ']';
    echo $admins.";";
	echo "$( \"#Master\" ).autocomplete({source: admins});";
?>
</script>
