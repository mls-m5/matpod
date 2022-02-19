#include "server.h"
#include "control.h"
#include "htmlpages.h"
#include <WebServer.h>

namespace server {

WebServer server{80};

void init() {
    server.on("/", HTTP_GET, []() {
        server.sendHeader("Connection", "close");
        server.send(200, "html", html);
    });
    server.on("/", HTTP_POST, []() {
        server.send(200, "text", "ok");
        Control::instance().x = server.arg("x").toFloat();
        Control::instance().y = server.arg("y").toFloat();
    });
}

} // namespace server
