<?php
class Rating
{
	public $players;
	public $rating;
	public $date1;
	public $date2;
	public function __construct()
	{
		$this->date1 = $date1;
		$this->date2 = $date2;
		$res = SQL("select Won as v, Role as r, DryVictory as d, player, BestMove as b from PlayerGame join Games ON(Game=GameId) group by player")->getAll();
		foreach ($res as $row) {
			$this->players[$row['player']][] = array('b' => $row['b'], 'v' => $row['v'], 'r'=>$row['r'], 'd'=>$row['d']);
		}
		$this->rating = array();
		$this->calculateRating();
		//if (($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			usort($this->players, "cmp");
	}
	private function calculateRating()
	{
		foreach ($this->players as $player => $games) {
			if (!isset($this->rating[$player]))
			{
				$this->rating[$player] = array('p'=>0, 'v'=>0);
			}
			foreach ($games as $game) {
				$this->rating[$player]['p'] += Rating::getRating($game);
				$this->rating[$player]['v'] += $game['v'];
				echo $this->rating[$player]['p'] ;
		
			}
		}

	}
	public static function getRating($game)
	{

		$result = 0;
		if ($game['v'])
		{
			$result += 1;
			if ($game['r'] === "Sherif" || $game['r'] === "Don")
				$result +=0.25;
			if ($game['d'])
				$result +=0.25;
		}
		if ($game['b'] == 2)
			$result += 0.25;
		if ($game['b'] == 3)
			$result += 0.5;
		return $result;

	}
	
}
function cmp($a, $b)
	{
	    if ($a['p'] == $b['p']) {
	        return 0;
	    }
	    return ($a['p'] < $b['p']) ? 1 : -1;
	}
?>