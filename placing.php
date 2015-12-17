<?php
require("DBManager.inc");
$host = "mysql.hostinger.com.ua";
$dbName = "u907137641_open";
$user = "u907137641_open";
$password = "konoplya_1";
DBManager::getInstance()->connect($host, $dbName, $user, $password);
class Player 
{
	public $id;
	public $table;	
	function __construct($id)
	{
		$this->id = $id;
	}
	public function setTable($talbeNumber)
	{
		$this->table[] = $talbeNumber; 
	}
}
$players = array();
for ($i=0; $i < 100; $i++) { 
	$player = new Player($i + 1);
	$player->setTable((int) ($i / 10));
	$players[] = $player;
}

for ($i=1; $i < 7; $i++) { 
	for ($j=0; $j < 10; $j++) { 
		for ($k=0; $k < 10; $k++) { 
			$players[$j * 10 + $k]->setTable(($j + $i * $k) % 10);
		}
	}
}


for ($i=0; $i < 100; $i++) { 
	$tables = "";
	foreach ($players[$i]->table as $value) {
		
		$tables .=  $value . "-";
		
	}
	$tables[strlen($tables)-1] = '';
	SQL("UPDATE Players SET Tables = ? where id = ?", array($tables, $players[$i]->id));
}
?>