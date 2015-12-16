<?php
class GlobalStat
{
	public $top;
	private $roleSQLCount;
	private $topSQL;
	public function __construct()
	{
		$this->roleSQLCount = "SELECT MAX(t) as m from (SELECT count(*) t from PlayerGame where Role=? group by player) s";
		$this->topSQL = "SELECT player, w / t * 100 as r, t, b from (SELECT player, count(*) t, SUM(Won) w, SUM(BestPlayer) b from PlayerGame JOIN Players ON (player = Name ) WHERE StatusId !=2 AND StatusId !=0 AND Role=? group by player) s where t > ? order by r DESC limit 3";
		$this->getStatRole("Sherif");
		$this->getStatRole("Don");
		$this->getStatRole("Mafia");
		$this->getStatRole("Citizen");
		$count = SQL("SELECT MAX(t) as m from (SELECT count(*) t from PlayerGame group by player) s")->getAll()[0]['m'];
		$this->top["Голосование за лучших"] = SQL("SELECT player, b / t * 100 as r, t, b from (SELECT player, count(*) t, SUM(BestPlayer) b from PlayerGame  group by player) s where t > ? order by r DESC limit 3", array( $count / 3))->getAll();
	}
	private function getStatRole($role)
	{
		$count = array();
		$count[$role] = SQL($this->roleSQLCount, array($role))->getAll()[0]['m'];
		$this->top[$role] = SQL($this->topSQL, array($role, $count[$role] / 3))->getAll();

	}
}

?>