var start = document.getElementById("start-button");
var stop = document.getElementById("stop-button");
var statusContainer = document.getElementById("status-container");

var startURL = window.location.href + "start"
var stopURL = window.location.href + "stop"

var xhttp = new XMLHttpRequest();

xhttp.onreadystatechange = function() {
  if (this.readyState == 4 && this.status == 200) {
    statusContainer.innerHTML = this.responseText;
    console.log(this.responseText);
  }
}


start.addEventListener('click', function(e) {
  e.preventDefault();

  xhttp.open("GET", "start", true);
  xhttp.send();
});

stop.addEventListener('click', function(e) {
  e.preventDefault();

  xhttp.open("GET", "stop", true);
  xhttp.send();
});

function updateStatus() {
  xhttp.open("GET", "status", true)
  xhttp.send();
}

setInterval(updateStatus, 1000);
