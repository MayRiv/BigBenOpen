<?php
class Domination
{
	public $BRed;
	public $BBlack;
	public $BR;
	public $RB;
	public $comparePlayer1;
	public $comparePlayer2;
	public $games;
	public $status;
	public function __construct($p1, $p2)
	{
		$this->comparePlayer1 = $p1;
		$this->comparePlayer2 = $p2;

		$s1 = SQL("Select StatusId from Players where Name Like ?", array($p1))->getAll()[0]['StatusId'];
		$s2 = SQL("Select StatusId from Players where Name Like ?", array($p2))->getAll()[0]['StatusId'];
		if ($p1 === $_SESSION['player'])
			$s1 = 1;
		if ($p2 == $_SESSION['player'])
			$s2 = 1;
		if ($s1 == 1 && $s2 == 1)
		{
			$this->BRed = SQL("select count(*) as total, SUM(w1) as v1, SUM(w2) as v2 from (SELECT * FROM ( SELECT player as p1,Role as r1, Won as w1, Game FROM  `PlayerGame`  join Players ON(player = Name) WHERE player LIKE  ?) t1
										JOIN (SELECT player as p2,Role as r2, Won as w2, Game FROM  `PlayerGame` join Players ON(player = Name) WHERE player LIKE  ?) t2 
										USING ( Game )) G where (r1 like 'Citizen' or r1 like 'Sherif') and (r2 like 'Citizen' or r2 like 'Sherif')", array($this->comparePlayer1, $this->comparePlayer2))->getAll()[0];
			$this->BBlack= SQL("select count(*) as total, SUM(w1) as v1, SUM(w2) as v2 from (SELECT * FROM ( SELECT player as p1,Role as r1, Won as w1, Game FROM  `PlayerGame` join Players ON(player = Name) WHERE player LIKE  ?) t1
										JOIN (SELECT player as p2,Role as r2, Won as w2, Game FROM  `PlayerGame`  join Players ON(player = Name) WHERE player LIKE  ?) t2 
										USING ( Game )) G where (r1 like 'Mafia' or r1 like 'Don') and (r2 like 'Mafia' or r2 like 'Don')", array($this->comparePlayer1, $this->comparePlayer2))->getAll()[0];
			$this->BR= SQL("select count(*) as total, SUM(w1) as v1, SUM(w2) as v2, SUM(WasShotFirst) as s from (SELECT * FROM ( SELECT player as p1,Role as r1, Won as w1, Game FROM  `PlayerGame` join Players ON(player = Name)  WHERE player LIKE  ?) t1
										JOIN (SELECT player as p2,Role as r2, Won as w2, Game, WasShotFirst FROM  `PlayerGame` join Players ON(player = Name) WHERE player LIKE  ?) t2 
										USING ( Game )) G where (r1 like 'Mafia' or r1 like 'Don') and (r2 like 'Citizen' or r2 like 'Sherif')", array($this->comparePlayer1, $this->comparePlayer2))->getAll()[0];
			$this->RB= SQL("select count(*) as total, SUM(w1) as v1, SUM(w2) as v2, SUM(WasShotFirst) as s from (SELECT * FROM ( SELECT player as p1,Role as r1, Won as w1, Game, WasShotFirst FROM  `PlayerGame` join Players ON(player = Name) WHERE player LIKE  ?) t1
										JOIN (SELECT player as p2,Role as r2, Won as w2, Game FROM  `PlayerGame` join Players ON(player = Name) WHERE player LIKE  ?) t2 
										USING ( Game )) G where (r1 like 'Citizen' or r1 like 'Sherif') and (r2 like 'Mafia' or r2 like 'Don')", array($this->comparePlayer1, $this->comparePlayer2))->getAll()[0];

			$this->games = SQL("SELECT Game as id FROM ( SELECT player, Game FROM  `PlayerGame`  WHERE player LIKE  ?) t1
										JOIN (SELECT player, Game FROM  `PlayerGame`  WHERE player LIKE  ?) t2 
										USING ( Game )", array($this->comparePlayer1, $this->comparePlayer2))->getAll();
			$this->status = true;
		}
		else 
			$this->status = false;
	}
}

?>