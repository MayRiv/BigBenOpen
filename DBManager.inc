<?php
require("DataSet.inc");

class DBManager
{
	private static $instance;
	private $DBH;

	private function __construct(){}

	public static function getInstance()
	{
		if(is_null(self::$instance))
		{
			self::$instance = new self();
		}
	return self::$instance;
}

public function connect($host,$dbname,$user,$password)
{
	try
	{
		$this->DBH = new PDO("mysql:host=$host;dbname=$dbname;", $user, $password, array(PDO::MYSQL_ATTR_INIT_COMMAND => "SET NAMES utf8")); 
		$this->DBH->exec('SET NAMES utf8');

	}
	catch(PDOException $e)
	{
		WriteError($e->getMessage());
		die();
	}
}

public function SQLE($query, $params = null)
{
	try
	{ 
		if(!is_null($params))
		{
			$STH = $this->DBH->prepare($query);
			$STH->execute($params); 
		}
		else
		{
			$STH = $this->DBH->query($query); 
		}
	}
	catch(PDOException $e)
	{
		WriteError($e->getMessge());
	}
}

public function SQL($query, $params = null)
{
	try
	{ 
		if(!is_null($params))
		{
			$STH = $this->DBH->prepare($query);
			$STH->execute($params);
			return new DataSet($STH);
		}
		else
		{
			$STH = $this->DBH->query($query);
			return new DataSet($STH);
		}
	}
	catch(PDOException $e)
	{
		WriteError($e->getMessge());
	}
}

public function DSQL($query, $params = null)
{
	$result = "";
	if(is_null($params))
	{
		$result = $query;
	}
	else
	{
		if(isset($params[0]))
		{
			$lines = explode('?',$query); 
			$n = count($lines);
			for($i = 0; $i < $n - 1; $i++)
			{ 
				$result .= $lines[$i].$this->DBH->quote($params[$i]);
			}
			$result .= $lines[$n-1];
		}
		else
		{
			$result = $query;
			foreach($params as $key => $value )
			{
				$result = str_replace(':'.$key, $this->DBH->quote($value), $result);
			}
		}
	}
	echo $result;
}

private function WriteError($error)
{
	echo $error;
}
}

function SQLE($query)
{
	DBManager::getInstance()->SQLE($query);
}
function SQL($query, $params = null)
{
	return DBManager::getInstance()->SQL($query, $params);
}
function DSQL($query, $params = null)
{
	return DBManager::getInstance()->DSQL($query, $params);
}
?>