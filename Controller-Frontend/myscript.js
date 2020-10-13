$.ajaxSetup({timeout:100});

var combiKey = false;
var leftKey = false;
var rightKey = false;
var forwardKey = false;
var reverseKey = false;
var keyCounter = 0;

function readUrlAV (form) {
    TextVar = form.inputbox.value;
	VideoVar = "http://"+TextVar+":8080/video";
	AudioVar = "http://"+TextVar+":8080/audio.opus";
	document.getElementById("video").setAttribute('data', VideoVar);
	document.getElementById("audio").setAttribute('data', AudioVar);
}
function testConnexion () {
	/*var response = $.ajax({
		url: "http://192.168.4.1:80/?robot=TES",
		success: function(data) {
			alert("fff");
			alert(data);
			console.log('Data: ' + data);
			if (data == 1){
				alert("Verbindung erfolgreich aufgebaut");
			}
		}
	});*/
	
	$.get("http://192.168.4.1:80/?robot=TES");
	{Connection: close};
}

document.onkeydown = checkKeyDown;
document.onkeyup = checkKeyUp;

function checkKeyDown(e) {

    e = e || window.event;
	
	if (e.keyCode == '32') {
      	console.log('Event: ' + e.keyCode);
		$.get("http://192.168.4.1:80/", {robot: 'STP'});
		{Connection: close};
    }
	console.log('Counter: ' + keyCounter);
    if (e.keyCode == '38') {
        // up arrow
		// Must print "BYP" or "TES" or "ZUN" or "MOR" or "LAB" or "FWD" or "FWL" or "FWR" or "REV" or "REL" or "RER" or "STP" or "SWF" or "SIF"
		if (forwardKey == false && keyCounter < 1) {
			keyCounter++;
			console.log('Event: ' + e.keyCode);
			$.get("http://192.168.4.1:80/", {robot: 'FWD'});
			{Connection: close};
			forwardKey = true;
		}
		else if (combiKey == false) {
			if (leftKey == true) {
				console.log('Event: Left Forward');
				$.get("http://192.168.4.1:80/", {robot: 'FWL'});
				{Connection: close};
				combiKey = true;
			}
			else if (rightKey == true) {
				console.log('Event: Right Forward');
				$.get("http://192.168.4.1:80/", {robot: 'FWR'});
				{Connection: close};
				combiKey = true;
			}
		}
		
    }
    else if (e.keyCode == '40') {
        // down arrow
		if (reverseKey == false && keyCounter < 1) {
			keyCounter++;
			console.log('Event: ' + e.keyCode);
			$.get("http://192.168.4.1:80/", {robot: 'REV'});
			{Connection: close};
			reverseKey = true;
		}
		else if (combiKey == false) {
			if (leftKey == true) {
				console.log('Event: Left Reverse');
				$.get("http://192.168.4.1:80/", {robot: 'REL'});
				{Connection: close};
				combiKey = true;
			}
			else if (rightKey == true) {
				console.log('Event: Right Reverse');
				$.get("http://192.168.4.1:80/", {robot: 'RER'});
				{Connection: close};
				combiKey = true;
			}
			
		}
    }
    else if (e.keyCode == '37') {
       // left arrow
	   if (leftKey == false && keyCounter < 1) {
		   keyCounter++;
			console.log('Event: ' + e.keyCode);
			$.get("http://192.168.4.1:80/", {robot: 'LEF'});
			{Connection: close};
			leftKey = true;
		}
		else if (combiKey == false) {
			if (reverseKey == true) {
				console.log('Event: Left Reverse');
				$.get("http://192.168.4.1:80/", {robot: 'REL'});
				{Connection: close};
				combiKey = true;
			}
			else if (forwardKey == true) {
				console.log('Event: Left Forward');
				$.get("http://192.168.4.1:80/", {robot: 'FWL'});
				{Connection: close};
				combiKey = true;
			}
		}
	}
    else if (e.keyCode == '39') {
       // right arrow
	   if (rightKey == false && keyCounter < 1) {
		   keyCounter++;
		    console.log('Event: ' + e.keyCode);
			$.get("http://192.168.4.1:80/", {robot: 'RIG'})
			{Connection: close};
			rightKey = true;
		}
		else if (combiKey == false) {
			if (reverseKey == true) {
				console.log('Event: Right Reverse');
				$.get("http://192.168.4.1:80/", {robot: 'RER'});
				{Connection: close};
				combiKey = true;
			}
			else if (forwardKey == true) {
				console.log('Event: Right Forward');
				$.get("http://192.168.4.1:80/", {robot: 'FWR'});
				{Connection: close};
				combiKey = true;
			}
		}
	}
}

function checkKeyUp(e) {
    e = e || window.event;

    if ((e.keyCode == '38')||(e.keyCode == '40')||(e.keyCode == '37')||(e.keyCode == '39')) {
		switch(e.keyCode) {
		  case 37:
			console.log('Left Key Up');
			leftKey = false;
			break;
		  case 38:
			console.log('Forward Key Up');
			forwardKey = false;
			break;
		  case 39:
			console.log('Right Key Up');
			rightKey = false;
			break;
		  case 40:
			console.log('Reverse Key Up');
			reverseKey = false;
			break;
		  default:
			// code block
			console.log('Unknow KeyUp: ' + e.keyCode);
		} 
        // up arrow
		keyCounter--;
		setTimeout(stopRobot, 200);
    }
}

function stopRobot(){
	combiKey = false;
	console.log('Event: Stop' );
	$.get("http://192.168.4.1:80/", {robot: 'STP'});
	{Connection: close};
}

function sendQuery(cmd) {
  var checkBox = document.getElementById(cmd);
  if (cmd == 'ZUN' && checkBox.checked) {
	  if (document.getElementById('BYP').checked) {
		  document.getElementById('BYP').disabled = true;
		  document.getElementById('BYP_TXT').style.color = "#C8C8C8";
		  document.getElementById('BYP_SPAN').style.backgroundColor = "#ccc";
	  }
	  
	  document.getElementById('MOR').disabled = false;
	  document.getElementById('MOR_TXT').style.color = "#000000";
	  document.getElementById('LAB').disabled = false;
	  document.getElementById('LAB_TXT').style.color = "#000000";
	  document.getElementById('SWF').disabled = false;
	  document.getElementById('SWF_TXT').style.color = "#000000";
	  document.getElementById('SIF').disabled = false;
	  document.getElementById('SIF_TXT').style.color = "#000000";
  } 
  else if (cmd == 'ZUN' && checkBox.checked == false) {
	  if (document.getElementById('BYP').checked) {
		  document.getElementById('BYP').disabled = false;
		  document.getElementById('BYP_TXT').style.color = "#000000";
		  document.getElementById('BYP_SPAN').style.backgroundColor = "#2196F3";
	  }
	  
	  document.getElementById('MOR').disabled = true;
	  document.getElementById('MOR_TXT').style.color = "#C8C8C8";
	  document.getElementById('LAB').disabled = true;
	  document.getElementById('LAB_TXT').style.color = "#C8C8C8";
	  document.getElementById('SWF').disabled = true;
	  document.getElementById('SWF_TXT').style.color = "#C8C8C8";
	  document.getElementById('SIF').disabled = true;
	  document.getElementById('SIF_TXT').style.color = "#C8C8C8";
  }
  else if ((cmd == 'MOR' || cmd == 'LAB' || cmd == 'SWF' || cmd == 'SIF') && checkBox.checked == true) {
	  document.getElementById('ZUN').disabled = true;
	  document.getElementById('ZUN_SPAN').style.backgroundColor = "#ccc";
	  document.getElementById('ZUN_TXT').style.color = "#C8C8C8";
  }
  else if ((cmd == 'MOR' || cmd == 'LAB' || cmd == 'SWF' || cmd == 'SIF') && checkBox.checked == false) {
	  if (document.getElementById('MOR').checked == false && document.getElementById('LAB').checked == false && document.getElementById('SWF').checked == false && document.getElementById('SIF').checked == false){
		  document.getElementById('ZUN').disabled = false;
		  document.getElementById('ZUN_SPAN').style.backgroundColor = "#2196F3";
		  document.getElementById('ZUN_TXT').style.color = "#000000";
	  }
  } 
  
  $.get("http://192.168.4.1:80/?robot=" + cmd);
  {Connection: close};
} 