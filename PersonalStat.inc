<?php
class PersonalStat
{
	public $player;
	public $games;
	public $citizensGameCount=0;	
	public $sherifGameCount=0;	
	public $mafiaGameCount=0;	
	public $donGameCount=0;
	public $citizensVictoryCount=0;	
	public $sherifVictoryCount=0;
	public $mafiaVictoryCount=0;
	public $donVictoryCount=0;
	public $firstBloodCount=0;
	public $averageBestMove = 0;
	public $bestVotes = 0;



	public $totalRedCountGames;
	public $totalRedVictoryGames;
	public $totalBlackCountGames;
	public $totalBlackVictoryGames;
	public $totalGamesCount;
	public $totalVictoryCount;

	public $compareResult;
	public $stat;
	public $roomGameCount;
	public function __construct($playerName)
	{
		$this->player = $playerName;
		$games  = SQL("Select Game, RoomId, Role, Won, WasShotFirst, BestMove, BestPlayer, date from PlayerGame join Games ON (Game=GameId) where player like ?", array($playerName))->getAll();
		$totalBestMove = 0;
		$this->roomGameCount = array("1"=>0, "2"=>0, "3"=>0);
		foreach($games as $game)
		{	
			$this->roomGameCount[$game['RoomId']]++;
			$this->games[] = $game['Game'];
			if ($game['Role'] == "Citizen")
			{
				$this->citizensGameCount++;
				if ($game['Won'])
					$this->citizensVictoryCount++;
			}
			if ($game['Role'] == "Sherif")
			{
				$this->sherifGameCount++;
				if ($game['Won'])
					$this->sherifVictoryCount++;
			}
			if ($game['Role'] == "Mafia")
			{
				$this->mafiaGameCount++;
				if ($game['Won'])
					$this->mafiaVictoryCount++;
			}
			if ($game['Role'] == "Don")
			{
				$this->donGameCount++;
				if ($game['Won'])
					$this->donVictoryCount++;
			}
			if ($game['WasShotFirst'])
			{
				$this->firstBloodCount++;
				$totalBestMove += $game['BestMove'];
			}
			if ($game['BestPlayer'])
				$this->bestVotes+= $game['BestPlayer'];
		}
		if($this->firstBloodCount)
			$this->averageBestMove = $totalBestMove / $this->firstBloodCount;


		$this->totalRedCountGames = $this->citizensGameCount + $this->sherifGameCount;
		$this->totalRedVictoryGames = $this->citizensVictoryCount + $this->sherifVictoryCount;
		$this->totalBlackCountGames = $this->mafiaGameCount + $this->donGameCount;
		$this->totalBlackVictoryGames = $this->mafiaVictoryCount + $this->donVictoryCount;
		$this->totalGamesCount = $this->totalRedCountGames + $this->totalBlackCountGames;
		$this->totalVictoryCount = $this->totalRedVictoryGames + $this->totalBlackVictoryGames;


		$role = "";
		$this->stat = array();
		//$weeks = SQL("select DATE_FORMAT(date, '%Y/%m/%d') AS date FROM Games GROUP BY DATE_FORMAT(date,'%Y-%u')")->getAll();
		//foreach ($weeks as $week) {
		//	$this->stat[$week['date']] = array('general','red','black','sherif','citizen', 'don', 'mafia');
		//}
		//$weekStatSQL= SQL("select DATE_FORMAT(date, '%d.%m.%Y') AS date, Sum(Won) v, count(*) t FROM PlayerGame join Games On(Game=GameId)  where player like ? ".$role." GROUP BY DATE_FORMAT(date,'%Y-%u') ", array($playerName))->getAll();
		$weekStatSQL= SQL("select DATE_FORMAT(date, '%Y/%m/%d') AS date, Sum(Won) v, count(*) t FROM PlayerGame join Games On(Game=GameId)  where (player like ?) ".$role." GROUP BY DATE_FORMAT(date,'%Y-%u') ", array($playerName))->getAll();
		foreach ($weekStatSQL as $ws) {
			$this->stat[$ws['date']]['general']['total'] = $ws['t'];
			$this->stat[$ws['date']]['general']['victories'] = $ws['v'];
		}
		/*$role = "And (Role = 'Sherif' OR Role = 'Citizen')";
		$weekStatSQL= SQL("select DATE_FORMAT(date, '%Y/%m/%d') AS date, Sum(Won) v, count(*) t FROM PlayerGame join Games On(Game=GameId)  where (player like ?) ".$role." GROUP BY DATE_FORMAT(date,'%Y-%u') ", array($playerName))->getAll();
		foreach ($weekStatSQL as $ws) {
			$this->stat[$ws['date']]['red']['total'] = $ws['t'];
			$this->stat[$ws['date']]['red']['victories'] = $ws['v'];
		}

		$role = "And (Role = 'Don' OR Role = 'Mafia') ";
		$weekStatSQL= SQL("select DATE_FORMAT(date, '%Y/%m/%d') AS date, Sum(Won) v, count(*) t FROM PlayerGame join Games On(Game=GameId)  where (player like ?) ".$role." GROUP BY DATE_FORMAT(date,'%Y-%u') ", array($playerName))->getAll();
		foreach ($weekStatSQL as $ws) {
			$this->stat[$ws['date']]['black']['total'] = $ws['t'];
			$this->stat[$ws['date']]['black']['victories'] = $ws['v'];
		}*/
		
	}
}
?>