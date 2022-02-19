#pragma once

namespace server {

auto html = R"_(
<html>
<body>
<input type="range" min="-1" max="1" step=".1" onchange="setX(this.value)">
<input type="range" min="-1" max="1" step=".1" onchange="setY(this.value)">


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
</script>
</body>
</html>
)_";

}
