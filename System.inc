<?php
require("Game.inc");
require("PersonalStat.inc");
require("GlobalStat.inc");
require("PowerMap.inc");
require ("Domination.inc");
require("Rating.inc");
require_once("Logger.inc");
class System 
{
	private static $_instance;
	public static  function getInstance()
	{
		if (System::$_instance == null) System::$_instance = new System();
		return System::$_instance;
	}

	private function __construct()
	{
		# code...
	}
	public function getRating()
	{
		//$maxGameCount = SQL("select max(t) total from (SELECT COUNT( * ) t FROM PlayerGame JOIN Players ON ( player = Name ) WHERE StatusId !=2 GROUP BY player) t")->getAll()[0]['total'];
		//$players = SQL("SELECT player, p /(t * 3.25 + ? - t) AS r, t, b FROM ( SELECT player, ( SUM( Won ) *2 + SUM( BestPlayer ) * 0.5 + SUM( BestMove ) * 0.25) p, COUNT( * ) t, SUM(BestPlayer) b FROM PlayerGame JOIN Players ON ( player = Name ) WHERE StatusId !=2 GROUP BY player ) s  ORDER BY r DESC", array($maxGameCount))->getAll();

		/*$players = SQL("SELECT player, p / t AS r, t, b, v FROM (SELECT player, (SUM( Won ) *2 + SUM( BestPlayer ) * 1.5 + SUM( BestMove ) * 0.25
) p, COUNT( * ) t, SUM( BestPlayer ) b, SUM( Won ) v FROM PlayerGame
JOIN Games ON(Game=GameId)
JOIN Players ON ( player = Name ) 
WHERE StatusId !=2 AND StatusId != 0 AND DATE <= CAST(  '2015-11-11' AS DATE ) 
GROUP BY player
) s
ORDER BY r DESC, b DESC")->getAll();*/
		/*$players = SQL("SELECT player, p / t AS r, t, b, v FROM (SELECT player, (SUM( Won ) *2 + SUM( BestPlayer ) * 1.5 + SUM( BestMove ) * 0.25
) p, COUNT( * ) t, SUM( BestPlayer ) b, SUM( Won ) v FROM PlayerGame
JOIN Games ON(Game=GameId)
JOIN Players ON ( player = Name ) 
WHERE StatusId !=2 AND StatusId != 0 AND DATE BETWEEN CAST(  '2015-11-12' AS DATE ) AND CAST('2015-11-21' AS DATE)
GROUP BY player
) s
ORDER BY player DESC,r DESC, b DESC")->getAll();*/
/*$players = SQL("SELECT player, t, b, v FROM (SELECT player, (SUM( Won ) *2 + SUM( BestPlayer ) * 1.5 + SUM( BestMove ) * 0.25
) p, COUNT( * ) t, SUM( BestPlayer ) b, SUM( Won ) v FROM PlayerGame
JOIN Games ON(Game=GameId)
JOIN Players ON ( player = Name ) 
WHERE StatusId !=2 AND StatusId != 0 AND DATE BETWEEN CAST(  '2015-11-12' AS DATE ) AND CAST('2015-11-30' AS DATE)
GROUP BY player
) s
ORDER BY player ASC, b DESC")->getAll();*/
		$r = new Rating('2015-11-12', '2015-12-9');
		getView("RatingView.inc", $r);
	}
	public function showAdminPanel()
	{
		if ($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin"))	
			getView("AdminPanelView.inc", null);
		else 
			header("Location: ?action=getRating");
	}
	public function getPersonalStat()
	{
		if (!$_SESSION['isAuth'])
		{
			$players = SQL("Select Name from Players")->getAll();
			getView("Auth.inc",$players);
		}
		else
		{
			$stat = new PersonalStat($_SESSION['player']);
			if (isset($_POST['name']))
			{
				$player = $_POST["name"];

				$stat->compare($player);		
			}
			getView("PersonalStatView.inc", $stat);
		}
	}
	public function getGlobalStat()
	{
		$stat = new GlobalStat();
		getView("GlobalStatView.inc", $stat);
	}
	public function login()
	{
		if ($_SERVER['REQUEST_METHOD'] == 'POST')
		{
			$account = SQL("select  Status, Password from Players join Statuses USING(StatusId) where Name like ?", array($_POST['Player']))->getAll();
			if (isset($account[0]) && MD5($_POST['Password']) === $account[0]['Password'])
			{
				
				$_SESSION['isAuth'] = 1;
				$_SESSION['player'] = $_POST['Player'];
				$_SESSION['status'] = $account[0]['Status'];
				header("Location: ?action=getPersonalStat");
			}
			else echo "Wrong password or login";
		}
		else
		{
			$players = SQL("Select Name from Players")->getAll();
			getView("Auth.inc",$players);
		}
	}
	public function changePassword()
	{
		
		if (!($_SESSION['isAuth']))
			header("Location: ?action=getRating");
		else
		{
			if ($_SERVER['REQUEST_METHOD'] == 'GET')
			{
				getView("ChangePasswordView.inc", NULL);
			}
			else
			{
				$oldPass = MD5($_POST['OldPass']);
				if ($oldPass === SQL("select Password from Players where Name like ?", array($_SESSION['player']))->getAll()[0]['Password'])
				{
					if ($_POST['NewPass1'] === $_POST['NewPass2'])
					{
						SQL("Update Players SET Password=? where Name like ?", array(MD5($_POST['NewPass1']),$_SESSION['player']));
					}
				}
				header("Location: ?action=getPersonalStat");
			}
		}
	}
	public function logout()
	{
		$_SESSION['isAuth'] = 0;
		header("Location: ?action=getRating");
	}
	public function addGame()
	{
		if (!($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			header("Location: ?action=getRating");
		else
		{
			if ($_SERVER['REQUEST_METHOD'] == 'GET')
			{
				$players = SQL("select  Status, Name from Players join Statuses USING(StatusId)")->getAll();
				$obj = array('players'=>$players,'date'=>date("Y-m-d"));
				getView("AddGameView.inc",$obj);
			}
			else
			{
				$game = new Game($_POST);
				$game->saveToSql();
				header("Location: ?action=showAdminPanel");
			}
		}
	}
	public function deleteGame()
	{

		if (!($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			header("Location: ?action=getRating");
		else
		{
			if ($_SERVER['REQUEST_METHOD'] == 'GET')
			{
				$players = SQL("delete from Games where gameid=?", array($_GET['GameId']));
				$players = SQL("delete from PlayerGame where game=?", array($_GET['GameId']));
				Logger::getInstance()->write("Game with id ".$_GET['GameId']." has been deleted, deleter is " . $_SESSION['player']);
				header("Location: ?action=showGames");
			}
		}
	}

	public function addPlayer()
	{
		if (!($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			header("Location: ?action=getRating");
		else
		{
			if ($_SERVER['REQUEST_METHOD'] == 'GET')
			{
				$players = SQL("Select Name from Players")->getAll();
				getView("AddPlayerView.inc", $players);
			}
			else
			{
				if ($_POST['Status'] == 1)
					$pass = MD5("player");
				else
					$pass = MD5("bbmaster123");
				SQL("INSERT IGNORE INTO `Players`(`Name`, `Password`, `StatusId`) VALUES (?,?,?)", array($_POST['Name'],$pass, $_POST['Status']));
				Logger::getInstance()->write("Player ".$_POST['Name']." has been added to system, Status is ".$_POST['Status']." adder is " . $_SESSION['player']);
				header("Location: ?action=showAdminPanel");
			}
		}
	}
	public function showGames()
	{
		$games = null;
		if (isset($_GET['date']))
		{
			$games = array();
			$res = SQL("select GameId, Master, date, RoomId from Games  where date = ? order by roomId", array($_GET['date']))->getAll();
			foreach($res as $game)
			{
				$games[$game['date']][] = array($game['Master'], $game['GameId'], $game['RoomId']);		
			}
			getView("ShowGamesView.inc", array('type'=>"games", 'games'=>$games));
		}	
		else
		{
			$dates = SQL("select DISTINCT(date) from Games order by date DESC")->getAll();	
			getView("ShowGamesView.inc", array('type'=>"dates", 'dates'=>$dates));
		}
		
	}
	public function showGame()
	{
		$gameId = (int)$_GET['GameId'];
		$game = new Game($gameId);
		$game->show();
	}
	public function editGame()
	{
		if (!($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			header("Location: ?action=getRating");
		else
		{
			if ($_SERVER['REQUEST_METHOD'] == 'GET')
			{	
				$players = SQL("select  Status, Name from Players join Statuses USING(StatusId)")->getAll();
				$data['players'] = $players;
				$gameId = (int)$_GET['GameId'];
				$game = new Game($gameId);
				$data['game'] = $game;
				getView("EditGameView.inc", $data);
				//$game->editShow();
			}
			if ($_SERVER['REQUEST_METHOD'] == 'POST')
			{
				$gameId = (int)$_POST['GameId'];
				$game = new Game($_POST);
				$game->update($gameId);
				header("Location: ?action=showGame&GameId=$gameId");
			}
		}
	}
	public function getDomination()
	{
		$players = SQL("Select Name from Players")->getAll();
		$data['players'] = $players;

		if (isset($_GET['ComparePlayer1']) && isset( $_GET['ComparePlayer2']))
		{		
				$data['domination'] = new Domination($_GET['ComparePlayer1'], $_GET['ComparePlayer2']);
		}
		getView("DominationView.inc", $data);
	}
	public function getPowerMap()
	{
		if ($_SESSION['isAuth'])
		{
			$pm = new PowerMap($_SESSION['player']);
			getView("PowerMapView.inc", $pm);
		}
		
		else
			getView("Auth.inc",$players);
	}

}

?>
