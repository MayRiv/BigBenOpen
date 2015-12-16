<?php
require("Logger.inc");
class Game
{
	public $gameId;
	public $roomId;
	public $date;
	public $status;
	public $players;
	public function __construct($par)
	{
		if (is_array($par))
			$this->initByPostArray($par);
		else
			$this->initByGameId($par);
	}
	public function saveToSql()
	{
		SQL("INSERT INTO `Games`(`GameId`, `RoomId`, `Master`, `CityVictory`, `date`) VALUES (?,?,?,?,?)", array($this->gameId,$this->roomId, $this->master, $this->status, $this->date));
		
		Logger::getInstance()->write("Game with id $this->gameId is added, room is $this->roomId, adder is " . $_SESSION['player']);
		foreach ($this->players as $playerName => $info)
		{	
			SQL("INSERT INTO `PlayerGame`(`Player`, `Game`, `Role`, `BestPlayer`, `Warnings`, `WasShotFirst`, `BestMove`, `Won`, `Place`) VALUES (?,?,?,?,?,?,?,?,?)", array($playerName, $this->gameId, $info['Role'], $info['BestPlayer'], $info['Warnings'], $info['WasShotFirst'], $info['BestMove'], $info['Won'], $info['Place']));
		}
	}
	public function update($gameId)
	{
		SQL("UPDATE `Games` SET `RoomId`=?,`Master`=?,`CityVictory`=?,`date`=? WHERE GameId=?", array($this->roomId, $this->master, $this->status, $this->date, $gameId));
		SQL("Delete from PlayerGame where Game=?", array($gameId));
		foreach ($this->players as $playerName => $info)
		{	
			SQL("INSERT INTO `PlayerGame`(`Player`, `Game`, `Role`, `BestPlayer`, `Warnings`, `WasShotFirst`, `BestMove`, `Won`, `Place`) VALUES (?,?,?,?,?,?,?,?,?)", array($playerName, $gameId, $info['Role'], $info['BestPlayer'], $info['Warnings'], $info['WasShotFirst'], $info['BestMove'], $info['Won'], $info['Place']));
		}
		Logger::getInstance()->write("Game with id $this->gameId has been updates, room is $this->roomId, updater is " . $_SESSION['player']);
	}

	private function initByPostArray($post)
	{
		$this->roomId = $post['RoomId'];
		$this->master = $_POST['Master'];
		if ($post['result'] === "City")
			$this->status = 1;
		if ($post['result'] === "Mafia")
			$this->status = -1;
		if ($post['result'] === "Draw")
			$this->status = 0;
		$this->date = $post['date'];
		$this->gameId = SQL("select max(GameId) as m from Games")->getAll()[0]['m'] + 1;
				
		$this->players = array();
		for ($i = 0; $i < 10; $i++)
		{
			$this->players[$post["Player$i"]] = array('Role'=>$post["Role$i"], 'WasShotFirst'=>0, 'BestMove'=> 0, 'BestPlayer'=>0, 'Won' => 0, 'Warnings' => $post["Warnings$i"], 'Place' => $i + 1);
			if(isset($post["Best$i"]))
				$this->players[$post["Player$i"]]['BestPlayer'] = 1;
			
			if (($this->status == 1 && ($post["Role$i"] === "Citizen" || $post["Role$i"] === "Sherif")) ||
			   ($this->status == -1 && ($post["Role$i"] === "Mafia" || $post["Role$i"] === "Don")))
					$this->players[$post["Player$i"]]['Won'] = 1;
					
		}
		$this->players[$post['BestMovePlayer']]['BestMove'] = $post['BestMovePoints'];
		$this->players[$post['BestMovePlayer']]['WasShotFirst'] = 1;
	}
	private function initByGameId($GameId)
	{
		$this->gameId = $GameId;
		$game = SQL("Select RoomId, Master, date, CityVictory as Status from Games where GameId=?", array($GameId))->getAll();
		if (count($game) == 1)
		{
			$this->roomId = $game[0]['RoomId'];
			$this->date = $game[0]['date'];
			$this->master = $game[0]['Master'];
			$this->status = $game[0]['Status'];
		
			$res = SQL("Select `Player`, `Game`, `Role`, `BestPlayer`, `Warnings`, `WasShotFirst`, `BestMove`, `Won`, `Place` from `PlayerGame` WHERE Game = ? order by Place ASC", array($GameId))->getAll();
			foreach($res as $p)
			{
				$this->players[$p['Player']] = array('Role'=>$p["Role"], 'WasShotFirst'=>$p["WasShotFirst"], 'BestMove'=> $p["BestMove"], 'BestPlayer'=> $p["BestPlayer"], 'Won' => $p["Won"], 'Warnings' => $p["Warnings"], 'Place' => $p['Place']);
			}
		} 
	}
	public function show()
	{
		getView("HeaderView.inc", NULL);
		echo '<body><table class="table_dark">';
		echo "<tr><th>Игрок</th><th>Роль</th><th>Лучший</th><th>Фолы</th></tr>";
		foreach ($this->players as $name =>$player) 
		{
			echo "<tr><td>$name</td><td>".$player['Role']."</td><td>".$player['BestPlayer']."</td><td>".$player['Warnings']."</td></tr>";
			if ($player['WasShotFirst'])
			{
				$firstBlood['Name'] =$name;
				$firstBlood['BestMove'] =$player['BestMove'];
			}
		}
		echo '</table><div id="feed">';
		if ($this->status == 1)
			$victoryTeam = "Город";
		if ($this->status == -1)
			$victoryTeam = "Мафия";
		if ($this->status == 0)
			$victoryTeam = "Ничья";
		if (isset($firstBlood))
			echo "<p>Первоубиенный ".$firstBlood['Name']." Попал в ".$firstBlood['BestMove']." черных игроков</p>";
		echo "<p>Победила команда: $victoryTeam</p>";
		echo "<p>Ведущий: ".$this->master."</p>";
		echo "<p><a href='?action=showGames&date=".$this->date."'>Назад</a></p>";
		if (($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
		{
			echo "<p><a href='?action=editGame&GameId=$this->gameId'><img src='Pictures/edit.png'></a>";
			//echo "<a href='?action=deleteGame&GameId=$this->gameId'><img src='Pictures/delete.png'></a></p></div>";
		}
		getView("Footer.inc", NULL);
		echo "</body>";
	}
	public function editShow()
	{
		getView("HeaderView.inc", NULL);
		echo "<form id='form' action='?action=editGame' method='post'>
		<input name='GameId' type='hidden'  value='$this->gameId'>
		<div id='feed'>
		<p>Выберите номер игрового зала
		<select name='RoomId'>";
		for($i = 1; $i < 5; $i++)
		{
			if ($i == $this->roomId)
				echo "<option selected>$i</option>";
			else
				echo "<option>$i</option>";
		}
		echo "</select></p>
		<p>Дата проведения игры <input type='date' name='date' value=$this->date /></p>
		<p>Ведущий: <input type='text' name='Master' list='masters_list' value=$this->master></p>
		<body><table>
		<tr><th>Игрок</th><th>Роль</th><th>Лучший</th><th>Фолы</th></tr>";
		$roles = array("Citizen", "Sherif","Mafia","Don");
		$i = 0;
		foreach ($this->players as $name =>$player) 
		{
			echo "<tr><td><input type='text' name=Player$i list='players_list' value='$name'></td><td>
			<select id='Role$i' name='Role$i'>";
			foreach ($roles as $role) {
				if ($role === $player['Role'])
					echo "<option selected>$role</option>";
				else 
					echo "<option>$role</option>";
			}
		echo "</select></td><td>";
		if ($player['BestPlayer'] > 0)
			echo "<input type='checkbox' checked name='Best$i'/></td><td>";
		else 
			echo "<input type='checkbox' name='Best$i'/></td><td>";
		echo "<select name='Warnings$i'>";
			for($c =0; $c < 5; $c++)
				if ($c==$player['Warnings'])
					echo "<option selected>$c</option>";
				else 
					echo "<option>$c</option>";

			echo "</select></td></tr>";
			if ($player['WasShotFirst'])
			{
				$firstBlood['Name'] =$name;
				$firstBlood['BestMove'] =$player['BestMove'];
			}
			$i++;
		}
		echo '</table>';

		if (isset($firstBlood))
			echo "<p>Первоубиенный <input type='text' name='BestMovePlayer' placeholder='Первоубиенный' list='players_list' value='".$firstBlood['Name']."' />";
			echo "Попал в <td><select name='BestMovePoints'>";
			for ($i = 0; $i < 4; $i++)
			{
				if ($i == $firstBlood['BestMove'])
					echo "<option selected value=$i>$i</option>";
				else if ($i != 1)
					echo "<option value=$i>$i</option>";
			}
		echo "</select> черных игроков</p>";
		if ($this->status == 1)
			$victoryTeam = "Город";
		if ($this->status == -1)
			$victoryTeam = "Мафия";
		if ($this->status == 0)
			$victoryTeam = "Ничья";
		echo "<p>Победила команда: </p>";
		echo "<select name=\"result\">";
		$teams = array("City"=>"Мирных жителей", "Mafia"=>"Мафии", "Draw"=> "Ничья");
		if ($this->status == 1)
			$victoryTeam = "City";
		if ($this->status == -1)
			$victoryTeam = "Mafia";
		if ($this->status == 0)
			$victoryTeam = "Draw";
		foreach ($teams as $team =>$message) {
			if ($team === $victoryTeam)
				echo "<option value='$team' selected>$message</option>";
			else
				echo "<option value='$team'>$message</option>";
		}
		echo "<p><input type='button' value='Update' onclick='bbr.trySend()'/></p>
	</form>";
		getView("Footer.inc", NULL);
		$res = SQL("select  Status, Name from Players join Statuses USING(StatusId)")->getAll();
		echo "<datalist id='players_list'>";
		foreach ($res as $player)
			if (!($player['Status'] === "Master" || $player['Status'] === "Admin"))
    			echo "<option>".$player['Name']."</option>";
		echo "</datalist>
		<datalist id='masters_list'>";
		foreach ($res as $player)
			if ($player['Status'] === "Master" || $player['Status'] === "Admin")
    				echo "<option>".$player['Name']."</option>";
		echo "</datalist>";
		echo "</body>";
	}

}
?>
