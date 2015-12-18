<?php
require("DBManager.inc");
$host = "mysql.hostinger.com.ua";
$dbName = "u825515718_open";
$user = "u825515718_open";
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
class Table
{
	public $id;
	public $rounds;	
	function __construct($id)
	{
		$this->id = $id;
	}
	public function setPlayer($round, $player)
	{
		if (!isset($this->rounds[$round]) || !in_array($player, $this->rounds[$round]))
			$this->rounds[$round][] = $player; 
	}
	public function checkTable()
	{
		for ($i = 0; $i < 7; $i++)
		{
			if (count($this->rounds[$i]) != 10)
				return 0;
		}
		return 1;
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
$tables = array();
for ($i = 0; $i < 10; $i++)
{
	$tables[] = new Table($i);
}
for ($i = 0; $i < 100; $i++)
{
	for($j = 0; $j < 7; $j++)
	{
		$tables[$players[$i]->table[$j]]->setPlayer($j,$players[$i]->id);
	}
}
$result = true;
for ($i = 0; $i < 10; $i++)
{
	if (!$tables[$i]->checkTable())
		$result = false;
}
if ($result)
	echo "Success.";
else 
	echo "Failure";

for ($i=0; $i < 100; $i++) { 
	$tables = "";
	foreach ($players[$i]->table as $value) {
		
		$tables .=  $value . "-";
		
	}
	$tables[strlen($tables)-1] = '';
	SQL("UPDATE Players SET Tables = ? where id = ?", array($tables, $players[$i]->id));
}
?>
