<?php getView("HeaderView.inc", $obj);?>
<body>
<div id="feed">
	<table class="table_dark">
		<tr>
		<th rowspan='2'>Раунды</th>
 		<?php foreach ($obj['stat'] as $player => $stat)
    			echo "<th colspan='3'>$player</th>";
		?>
   		</tr>
   		<tr>
			<?php for($i = 0; $i < count($obj['stat']); $i++)
				echo "<th>Роль</th><th>Лучшие ход</th><th>Лучшие голоса</th>"
			?>
		<tr>
			
		<?php
		for ($i = 0; $i < 10; $i++)
		{
			echo "<tr><td>".($i+1)."</td>";
			foreach ($obj['stat'] as $player => $stat) {
				echo "<td>".$stat[$i][0]."</td><td>".$stat[$i][1]."</td><td>".$stat[$i][2]."</td>";
			}
			echo "</tr>";
		}
		?>
		<tr><td>Сумма</td>
		<?php
		$teamSum = 0;

		foreach ($obj['stat'] as $player => $stat)
		{
			$teamSum += $obj['sum'][$player];
    		echo "<td colspan='3'>".$obj['sum'][$player]."</th>";
    	}
    	echo "</tr>";
    	echo "<tr><td>Суммарный рейтинг</td><td colspan='".count($obj['stat'])."'>$teamSum</td>";
		?>
		
	</table>
	
</div>
<?php getView("Footer.inc", $obj);?>

</body>