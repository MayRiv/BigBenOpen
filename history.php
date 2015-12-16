<?php
	$fp = fopen("history.log", "r");
	echo "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8' /></head><body><div id='feed'>";
	while(!feof($fp)) { 
	   	echo fgets($fp) . "<br />";
	}
	echo "</div></body></html>";
	fclose($fp);

?>
