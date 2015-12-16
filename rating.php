<?php
require("DBManager.inc");
define ("DEV", 0);
	if (DEV)
	{
		$host = "localhost";
		$dbName = "u825515718_bbrat";
		$user = "root";
		$password = "";
	}
	else
	{
		$host = "mysql.hostinger.com.ua";
		$dbName = "u825515718_bbrat";
		$user = "u825515718_bbrat";
		$password = "B1gBenMafia";
	}	
	DBManager::getInstance()->connect($host, $dbName, $user, $password);
	$players = SQL("SELECT player, p / t AS r, t FROM ( SELECT player, ( SUM( Won ) *2 + SUM( BestPlayer ) * 0.5 + SUM( BestMove ) * 0.25) p, COUNT( * ) t FROM PlayerGame JOIN Players ON ( player = Name ) WHERE StatusId !=2 GROUP BY player ) s WHERE t >10  ORDER BY r DESC")->getAll();
	foreach ($players as $p) {
		SQL("INSERT IGNORE INTO `Rating`(`Player`, `Rating`, `GameCount`, `Date`) VALUES (?,?,?,?)", array($p['player'], $p['r'], $p['t'], date("Y-m-d")));
	}
?>