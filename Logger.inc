<?php
class Logger
{
	private $fp;
	private static $_instance;
	public static  function getInstance()
	{
		if (Logger::$_instance == null) Logger::$_instance = new Logger("history.log");
		return Logger::$_instance;
	}

	private function __construct($logPath)
	{
		$this->fp = fopen($logPath, "a");
	}
	public function write($line)
	{
		fwrite($this->fp, "[".date("F j, g:i a")."]  ".urldecode($line)."\n");
	}
	public function save()
	{
		fclose($this->fp);
	}
}

?>