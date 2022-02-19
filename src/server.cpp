#include "server.h"
#include "control.h"
#include "htmlpages.h"
#include "led.h"
#include <WebServer.h>

namespace server {

WebServer server{80};

void init() {
    server.on("/", HTTP_GET, []() {
        server.send(200, "text/html", html);
        //        led::flash();
    });
    server.on("/control", HTTP_POST, []() {
        auto x = server.arg("x");
        auto y = server.arg("y");
        String response = "ok: x=";
        response += x;
        response += " y= ";
        response += y;
        server.send(200, "text", response);
        Control::instance().x = x.toFloat();
        Control::instance().y = y.toFloat();
        //        led::flash();
    });

    server.begin();
}

void handle() {
    server.handleClient();
}

} // namespace server
