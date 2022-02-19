#include "serversim.h"
#include "control.h"
#include "crow.h"
#include "htmlpages.h"
#include "server.h"
#include <iostream>
#include <memory>
#include <string>
#include <thread>

namespace {

auto app = crow::SimpleApp{};

void parse(std::string str) {
    auto eq = str.find("=");
    auto a = str.find("&");

    auto x = str.substr(eq + 1, a - eq - 1);

    eq = str.find("=", eq + 1);
    auto y = str.substr(eq + 1);

    Control::instance().x = std::stof(x);
    Control::instance().y = std::stof(y);
}

} // namespace

namespace server {

void init() {
    CROW_ROUTE(app, "/")([]() { return html; });

    CROW_ROUTE(app, "/control")
        .methods("POST"_method)([](const crow::request &req) {
            std::cout << req.body << std::endl;

            //            parse(req.body.c_str());
            parse(req.body);

            return crow::response{"ok"};
        });

    auto &app = ::app;

    auto thread =
        std::thread{[&app]() { app.port(8000).multithreaded().run(); }};
    thread.detach();
}

void handle() {
}

} // namespace server

void serversim::stop() {
    app.stop();
}
