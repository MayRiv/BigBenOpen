<?php
class Placement
{
	public $player;
	public $tables;	
	function __construct($player)
	{
		$this->player = $player;
		$res = SQL("Select Tables from Players where Name = ?", array($player));//->getAll();
		$this->tables = explode("-", $res[0]["Tables"]);
	}
}
?>