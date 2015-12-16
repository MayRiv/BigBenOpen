<?php
function getView($name,$obj)
{
	ob_start();
	require('templates/'.$name);
	ob_end_flush();
}

?>