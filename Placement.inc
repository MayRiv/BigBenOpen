<?php
class Placement
{
	public $player;
	public $table;	
	function __construct($player)
	{
		$this->player = $player;
		$res = SQL("Select Tables from Player where Name = ?", array($player))->getAll();
		$this->tables = explode("-", $res[0]["Tables"]);
	}
}
?>