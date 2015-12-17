<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<form action="?action=getPlacing" method="post">
  			<p><input type="text" id="Player" name="Player" placeholder="Введите ник"></p>
  			<p><input type="submit" value="Показать рассадку"></p>
 	</form>
</div>

<?php
  if ($obj['placement'])
    echo "wasap.";
?>
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

