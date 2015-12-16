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
$res = SQL("Select  Name from Players order by Name DESC")->getAll();
foreach ($res as  $player) {
	echo "<p>".$player['Name']."</p>";
}
echo "</div></div></body></html>";
?>