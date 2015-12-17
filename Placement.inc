<?php
class Placement
{
	public $player;
	public $tables;	
	function __construct($player)
	{
		$this->player = $player;
		$res = DSQL("Select Tables from Player where Name = ?", array($player));//->getAll();
		$this->tables = explode("-", $res[0]["Tables"]);
	}
}
?>