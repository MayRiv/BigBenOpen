	
<?php

class DataSet
{
private $STH;
private $arr;
private $current = 0;

public function __construct($ST)
{
	$this->STH = $ST;
	$this->STH->setFetchMode(PDO::FETCH_ASSOC);
	$this->arr = $this->STH->FetchAll();
}

public function getAll()
{
	return $this->arr;
}

public function next()
{
	if($this->current < count($this->arr))
	{
		$temp = $this->arr[$this->current];
		$this->current++;
		return $temp;
	}
}

public function getLast()
{
	return $this->arr[$this->current-1];
}

public function getColumn($number)
{
	$temp = array();
	foreach($this->arr as $row)
	{
		array_push($temp,$row[$number]);
	}
return $temp;
}

public function WriteAll()
{
	foreach($this->arr as $row)
	{
		foreach($row as $cell)
		{
			echo $cell.' ';
		}
	echo '<br>';
	}
}

public function WriteColumn($number)
{
	foreach($this->arr as $row)
	{
		echo $row[$number].'<br>';
	}
}
}

?>