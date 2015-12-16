<?php
class Rating
{
	public $players;
	public $date1;
	public $date2;
	public function __construct($date1, $date2)
	{
		$this->date1 = $date1;
		$this->date2 = $date2;
		$res = SQL("SELECT player, t, b, v, m FROM ( SELECT player, COUNT( * ) t, SUM( BestPlayer ) b, SUM( Won ) v, SUM( BestMove ) * 0.25 m FROM PlayerGame JOIN Games ON ( Game = GameId ) JOIN Players ON (player = Name ) WHERE StatusId !=2 AND StatusId !=0 AND DATE BETWEEN CAST(  ? AS DATE )  AND CAST(  ? AS DATE )  GROUP BY player) s ORDER BY  `s`.`m` DESC", array($date1, $date2))->getAll();
		foreach ($res as $row) {
			$this->players[] = array('p'=>$row['player'],'t'=>$row['t'], 'b' => $row['b'], 'v' => $row['v'], 'm'=>$row['m'], 'r'=>0);
		}

		$this->calculateRating();
		//if (($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			usort($this->players, "cmp");
	}
	private function calculateRating()
	{
		
		for ($i=0; $i < count($this->players); $i++) { 
			$s = $this->players[$i];

			
// count - кол-во сыгранных игр этим игроком 
// win, lose, best - obvious 
// power - возведение в степень. 

// bestmove - лучший ход. За 2х bestmove = 0.5, за 3х bestmove = 0.75; За 1го bestmove = 0 


			$this->players[$i]['r'] = Rating::getRating($s);
		}
	}
	public static function getRating($s)
	{
		static $constForSign = 20;
		static $constKoefWin = 1.6;

		$bestResult = ($s['b']+$s['m']);
		$lose = $s['t'] - $s['v']; 
		$koefWinStreak = $s['v']-$lose+$bestResult*0.5; 
		$winStreak = ($koefWinStreak)*pow(($koefWinStreak/$s['t']), 2); 
		$result = $s['v']*$constKoefWin-$lose+$bestResult+$winStreak; 
		$result += $constForSign;
		$result = sqrt(abs($result));
		return $result;
	}
	
}
function cmp($a, $b)
	{
	    if ($a['r'] == $b['r']) {
	        return 0;
	    }
	    return ($a['r'] < $b['r']) ? 1 : -1;
	}
?>