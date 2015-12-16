<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<form action="?action=login" method="post">
  			<p><input type="text" id="Player" name="Player" placeholder="Введите ник"></p>
			<p><input type="password" name="Password" placeholder="Введите пароль"></p>
  			<p><input type="submit" value="Войти"></p>
 	</form>
</div>
<script type="text/javascript">
<?php
$names = "var choices = [";
        	foreach ($obj as $player)
    			$names .= "'".$player['Name']."',";
    		$names[strlen($names) - 1] = ']';
    		echo $names.";";
?>
</script>
 
<script type="text/javascript">
<?php
$names = "var availableTags = [";
	foreach ($obj as $player)
    	$names .= '"'.$player["Name"].'",';
    $names[strlen($names) - 1] = ']';
    echo $names.";";
?>
$( "#Player" ).autocomplete({source: availableTags});
</script>


<?php getView("Footer.inc", null); ?>
</body>

