<?php
class PowerMap
{
	private $players;
	private $zeroPlayer;
	public $map;
	public function __construct($player)
	{
		$this->players = SQL("Select Name from Players")->getAll();
		$this->zeroPlayer = $player;
		$this->map = array();
		foreach ($this->players as $p) {
			$this->map[$p['Name']] =$this->getDomination($p['Name']);
		}
	}
	private function getDomination($player)
	{
		$res = SQL("SELECT COUNT( * ) AS total, SUM( w1 ) AS v1, SUM( w2 ) AS v2, SUM( WasShotFirst ) AS s FROM ( SELECT * FROM (SELECT player AS p1, Role AS r1, Won AS w1, Game, WasShotFirst FROM  `PlayerGame` JOIN Players ON ( player = Name )  WHERE player LIKE  ? ) t1 JOIN ( SELECT player AS p2, Role AS r2, Won AS w2, Game FROM  `PlayerGame` JOIN Players ON ( player = Name ) WHERE player LIKE  ? AND StatusId = 1) t2 USING ( Game )) G WHERE ((r1 LIKE  'Citizen' OR r1 LIKE  'Sherif') AND (r2 LIKE  'Mafia' OR r2 LIKE  'Don')) OR ((r1 LIKE  'Mafia' OR r1 LIKE  'Don') AND (r2 LIKE  'Citizen' OR r2 LIKE  'Sherif'))", array($this->zeroPlayer, $player))->getAll();
		if (count($res) > 0)
			return array($res[0]['v2'] - $res[0]['v1'], $res[0]['total']);
		else 
			return false;
	}
}

?>