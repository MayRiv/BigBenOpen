<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<form action="?action=getPlacing" method="post">
  			<p><input type="text" id="Player" name="Player" placeholder="Введите ник"></p>
  			<p><input type="submit" value="Показать рассадку"></p>
 	</form>
</div>
<table class="table_dark">
    <tr><th>Раунд</th><th>Стол</th>
<?php
  var_dump($obj);
  if ($obj['placement'])
    foreach ($obj['placement']->tables as $round=> $table) {
       echo "<tr><td>$round</td><td>$table</td></tr>";
    }
   
?>
</table>
<script type="text/javascript">
<?php
$names = "var availableTags = [";
	foreach ($obj['players'] as $player)
    	$names .= '"'.$player["Name"].'",';
    $names[strlen($names) - 1] = ']';
    echo $names.";";
?>
$( "#Player" ).autocomplete({source: availableTags});
</script>


<?php getView("Footer.inc", null); ?>
</body>

