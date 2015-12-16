<?php
require_once("DBManager.inc");
class Field
{
	private $name;
	private $type;		//int double varchar text bool date
	private $caption;
	private $value;
	private $defaultValue;
	private $isAutoInc;
	private $isVisible;
	private $isVisibleBrowse;
	private $formPrefix;
	private $cssClass;
	
	private $isLookup;
	private $lookupVariants;
	private $lookupInfo;


	public function __construct($name, $type, $caption, $formPrefix, 
		$cssClass, $defaultValue = "", $isVisibleBr = true, $isVisible = true, $value = "",  
		$isAutoInc = false)
	{
		$this->name = $name;
		$this->caption = $caption;
		$this->value = $value;
		$this->defaultValue = $defaultValue;
		$this->isAutoInc = $isAutoInc;
		$this->isVisible = $isVisible;
		$this->isVisibleBrowse = $isVisibleBr;
		$this->formPrefix = $formPrefix;
		$this->cssClass = $cssClass;
		$this->isLookup = false;

		if(is_array($type))
		{
			$this->isLookup = true;
			$this->lookupInfo = $type;
			$this->type = 'lookup';
			$captionfield = (isset($this->lookupInfo['captionfield'])) 
					? ", ".$this->lookupInfo['captionfield'] 
					: "";

			DBManager::getInstance()->connect("localhost", "maska9", "root", "");

			$this->lookupVariants =  SQL("select ".$this->lookupInfo['field'].$captionfield." from ".$this->lookupInfo['table'])->getAll();

			if($this->lookupInfo['isRequired'] == false)
			{
				$this->lookupVariants[] = array($this->lookupInfo['field'] => "", $this->getLookupCaption() => "");
			}			
		}
		else
		{
			$this->type = $type;
		}
	}
	
	public function createControl($myValue = null, $findValue = null)
	{
		$t = $this->type;
		$value = $this->getHTMLValue();
		if(is_null($myValue) == false)
		{
			$value = $myValue;
		}

		switch($t)
		{
			case "bool":
			{
				return '<input type = "checkbox" name = "'.$this->formPrefix.$this->name.'" class = "'.$this->cssClass.'" checked = "'.$value.'" />';
				break;
			}
			case "date":
			{
				return '<input type = "datetime" name = "'.$this->formPrefix.$this->name.'" class = "'.$this->cssClass.'" value = "'.$value.'" />';
				break;
			}
			case "text":
			{
				return '<textarea name="'.$this->formPrefix.$this->name.'">'.$value.'</textarea>';
				break;
			}
			case "html":
			{
				return "<textarea class = 'ckeditor' name='".$this->formPrefix.$this->name."' rows = '10' cols = '70'>"
				.$value."</textarea>";				
				break;
			}
			case "lookup":
			{
				$result = "<select name = '".$this->formPrefix.$this->name."' class = '".$this->cssClass."'>";
				if(!is_null($findValue) && !is_null($myValue) && $this->name == $findValue)
				{
					foreach ($this->lookupVariants as $variant) 
					{
						$t = ($variant[$this->lookupInfo['field']] == $myValue) ? 'selected' : '' ;						
						$result .= "<option value='".$variant[$this->lookupInfo['field']]."' ".$t." >"
											.$variant[$this->getLookupCaption()]."</option>";						
					}		
				}
				else
				{
					foreach ($this->lookupVariants as $variant) 
					{
						$result .= "<option value='".$variant[$this->lookupInfo['field']]."'>"
											.$variant[$this->getLookupCaption()]."</option>";						
					}		
				}	
				$result .= "</select>"; 
				return $result;
				break;
			}
			default:
			{
				return '<input type = "textbox" name = "'.$this->formPrefix.$this->name.'" class = "'.$this->cssClass.'" value = "'.$value.'" />';
			}
		}
		
	}

	public function getShortValue()
	{
		return substr($this->value, 0, 200);
	}

	public function getSQLValue()
	{
		return $this->value;
	}

	public static function prepareValue($value)
	{
		if($value == "")
		{
			return "-";
		}
		else
		{
			return mb_substr(strip_tags($value), 0 , 100, 'UTF-8');
		}
	}

	public function getHTMLValue()
	{
		switch($this->type)
		{
			case "int":
				return intval($this->value);
				break;
			case "double":
				return doubleval($this->value);
				break;
			case "varchar":
				return preg_quote($this->value); 
				break;
			case "html":
				return $this->value;
				break;
			case "text":
				return $this->value;
				break;
			case "date":
				return $this->value;
				break;
			case "bool":
				return $this->value;
				break;
			default:
				return $this->defaultValue;
		}
	}

	public function getCaption()
	{
		return $this->caption;
	}

	public function isVisible()
	{
		return $this->isVisible;
	}
	public function isVisibleBrowse()
	{
		return $this->isVisibleBrowse;
	}

	public function isAutoInc()
	{
		return $this->isAutoInc;
	}

	public function getName()
	{
		return $this->name;
	}

	public function getType()
	{
		return $this->type;
	}

	public function isLookup()
	{
		return $this->isLookup;
	}

	public function getLookupInfo()
	{
		return $this->lookupInfo;
	}

	public function getLookupCaption()
	{
		if(isset($this->lookupInfo)) 
		{	
			if(isset($this->lookupInfo['captionfield']))
			{
				return $this->lookupInfo['captionfield']; 
			}
			else
			{
				return $this->lookupInfo['field'];
			} 
		}
		return $this->lookupInfo;
	}
}
?>
