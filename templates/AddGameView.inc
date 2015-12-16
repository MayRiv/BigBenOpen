<?php getView("HeaderView.inc", $obj);?>
<body>
<div id="inserter">
<div>
	
	<form id="form" action="?action=addGame" method="post">
		<div>
		<p>Выберите номер игрового зала
		<select name='RoomId'>
			<option selected>1</option>
			<option>2</option>
			<option>3</option>
			<option>4</option>
		</select></p>
		<p>Дата проведения игры <input type="date" name="date" value='<?=$obj['date']?>' /></p>
		<p>Ведущий: <input type='text' name='Master' id='Master' value='<?=$_SESSION["player"]?>'></p>
		<table>
		
		<tr><th>№</th><th>Игрок</th><th>Роль</th><th>Лучший</th><th>Фолы</th>
<?php	for ( $i = 0; $i < 10; $i++)	
	echo "<tr><td>".($i+1)."</td><td><input type='text'  id='Player$i' name=Player$i></td>
		<td><select id='Role$i' name='Role$i'>
			<option>Citizen</option>
			<option>Sherif</option>
			<option>Mafia</option>
			<option>Don</option>
		</select></td>
		<td><input type='checkbox' name='Best$i'/></td>
		<td><select name='Warnings$i'>
			<option>0</option>
			<option>1</option>
			<option>2</option>
			<option>3</option>
			<option>4</option>
		</select></td>
		</tr>"
?>
		
			<tr><td></td><td><input type='text' name='BestMovePlayer' id='FirstBlood' placeholder='Первоубиенный' list='players_list'/></td>
			<td><select name='BestMovePoints'>
				<option selected value="0">Не попал</option>
				<option value="2">Назвал 2</option>
				<option value="3">Назвал 3</option>
			</select></td></tr></div>
		</table></div>
<div>	
			Победила команда:
			<select name="result">
				<option value="City" selected>Мирных жителей</option>
				<option value="Mafia">Мафии</option>
				<option value="Draw">Ничья</option>
			</select>
			</div>
		<p><input type="button" value="Send" onclick="bbr.trySend()"/></p>
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
	}
	echo "$( \"#FirstBlood\" ).autocomplete({source: availableTags});";

	$admins = "var admins = [";
	foreach ($obj['players'] as $player)
    	if ($player['Status'] === "Master" || $player['Status'] === "Admin")
    		$admins .= '"'.$player["Name"].'",';
    $admins[strlen($admins) - 1] = ']';
    echo $admins.";";
	echo "$( \"#Master\" ).autocomplete({source: admins});";

?>
</script>

</div>
<?php getView("Footer.inc", $obj);?>

</body>
