//$.ajaxSetup({timeout:100});
var cmds = ["TES", "FWL", "FWD", "FWR", "LEF", "RIG", "REL", "REV", "RER", "ZUN", "MOR", "LAB", "BYP", "SWF", "STP"];

function executeRequest(number){
  sendQuery(cmds[number]);
}

function sendQuery(name) {
  console.log("cmd: " + name);
  $.get("http://192.168.4.1:80/?robot=" + name);
  /*if (name != "STP"){
    setTimeout(function(){
    }, 100);
  }*/
  {Connection: close};
}