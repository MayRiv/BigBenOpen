var bbr = (function() {

	var version;
	function checkRoles()
	{
		var arr = [];
		countMaf = 0;
		countSherif = 0;
		countDon = 0;
		countCit = 0;
		for (i=0; i < 10; i++){
			var role = document.getElementById('Role'+i).value
			if(role=="Don")
				countDon++;
			if(role=="Citizen")
				countCit++;
			if(role=="Mafia")
				countMaf++;
			if(role=="Sherif")
				countSherif++;
			
		}
		if (countSherif == 1 && countDon == 1 && countCit == 6 && countMaf == 2)
		return true;
		else return false;
	}

  return {
	trySend: function() {
		if (checkRoles())
			document.getElementById('form').submit()
		else
			alert("Invalid Roles");

	},
	compare: function(player){
		player =  document.getElementById('ComparePlayer').value;

		var xhr = new XMLHttpRequest();

		var body = 'name=' + encodeURIComponent(player);

		xhr.open("POST", '?action=compare', true)
		xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded')

		xhr.onreadystatechange = function() { 
			if (xhr.readyState == 4) { 
		        if(xhr.status == 200) { 
		        	document.getElementById("CompareDiv").innerHTML = xhr.responseText; // Выводим ответ сервера
		        }
		    }
		};

		xhr.send(body);
	},
	tryDelete: function(gameId){
		if (confirm("Вы действительно хотиле удалить игру " + gameId + "?"))
		{
			window.location = "?action=deleteGame&GameId=" + gameId;
		}
	},
	tryGetDomination: function(){
		document.location.href = "?action=getDomination&ComparePlayer1=" + encodeURIComponent(document.getElementById('ComparePlayer1').value) + "&ComparePlayer2=" + encodeURIComponent(document.getElementById('ComparePlayer2').value) //.submit()encodeURIComponent	
	},
	generateAutocompleter: function(fieldMame, values)
	{
		return new autoComplete({
	   		selector: 'input[name='+fieldMame+']',
	    	minChars: 2,
	    	source: function(term, suggest){
		        term = term.toLowerCase();
				var choices = values;
		        var matches = [];
		        for (i=0; i<choices.length; i++)
		            if (~choices[i].toLowerCase().indexOf(term)) matches.push(choices[i]);
		        suggest(matches);
	    	}
		});
	}
}

})();