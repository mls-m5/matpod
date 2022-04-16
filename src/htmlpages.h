#pragma once

namespace server {

auto html = R"_(
<html>
<body>
<input id="y" type="range" min="-1" max="1" step=".1" onchange="setX(this.value)">
<input id="x" type="range" min="-1" max="1" step=".1" onchange="setY(this.value)">


<script>
"use strict"

var connectionAddr = "/control";

var x = 0;
var y = 0;

function setX(value) {
    x = value;
    sendControls(x, y)
}

function setY(value) {
    y = value;
    sendControls(x, y)
}

function sendControls(x, y) {
    post(connectionAddr, `x=${x}&y=${y}`, console.log)
}

function keydown(event) {
    let xRange = document.getElementById("x");
    let yRange = document.getElementById("y");

    if (event.key === "ArrowUp") {
        xRange.value += xRange.value;
    }
}

function post(url, data, success, fail) {
    var req = new XMLHttpRequest();
    req.open("POST", url);
    req.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    req.addEventListener("load", function() {
        if (req.readyState == 4 && (req.status == "200" || req.status == "201")) {
            if (typeof success === "function") {
                success(this.responseText);
            }
        }
        else {
            if (typeof fail === "function") {
                fail(this.responseText);
            }
        }
    });
    req.send(data);
}

document.addEventListener("keydown", keydown);

var gamepads = {};



function gamepadHandler(event, connecting) {
  var gamepad = event.gamepad;
  // Note:
  // gamepad === navigator.getGamepads()[gamepad.index]

  console.log(event)

  if (connecting) {
    gamepads[gamepad.index] = gamepad;
  } else {
    delete gamepads[gamepad.index];
  }
}

window.addEventListener("gamepadconnected", function(e) { gamepadHandler(e, true); }, false);
window.addEventListener("gamepaddisconnected", function(e) { gamepadHandler(e, false); }, false);

let gamepadAxis = [0, 0];

function updateAxis(newAxis) {
    if (newAxis[0] == gamepadAxis[0] && newAxis[1] == gamepadAxis[1]) {
        return;
    }
    gamepadAxis = newAxis;
    sendControls(gamepadAxis[0], gamepadAxis[1]);
}

function gameLoop() {
  let gp = navigator.getGamepads ? navigator.getGamepads() : (navigator.webkitGetGamepads ? navigator.webkitGetGamepads() : []);
  if (!gp) {
    return;
  }

  try {
//     console.log(gamepads[0].axes[1]);
     console.log(gp);
     for (let gamepad of gp) {
         if (gamepad === null) {
             continue;
         }
//         console.log(gamepad.axes);
         updateAxis([gamepad.axes[3], -gamepad.axes[1]]);
     }
  }
  catch (e) {
//     console.log("no gamepad");
  }
}

setInterval(gameLoop, 100);

</script>
</body>
</html>
)_";

}
