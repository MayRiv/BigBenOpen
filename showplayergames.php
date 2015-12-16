<?php
require("DBManager.inc");
require("viewer.inc");
getView("HeaderView.inc", null);
$host = "mysql.hostinger.com.ua";
$dbName = "u825515718_bbrat";
$user = "u825515718_bbrat";
$password = "B1gBenMafia";
DBManager::getInstance()->connect($host, $dbName, $user, $password);



echo "<html><body><div id='feed' style='margin-left: 300px;'><div style='text-align:left'>";
$res = SQL("Select player as Name, game as Id from PlayerGame group by Name order by player")->getAll();
foreach ($res as  $player) {
	echo "<p><a href='/?action=editGame&GameId=".$player['Id']."'>".$player['Name']."</a></p>";
}
echo "</div></div></body></html>";
?>