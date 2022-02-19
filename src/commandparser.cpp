#include "commandparser.h"
#include "control.h"

void parse(StrView str) {
    if (str.empty()) {
        return;
    }

    if (str.front() == '"') {
        ++str.data;
        --str.len;
    }
    if (str.back() == '\"') {
        --str.len;
    }

    auto space = str.find(' ');
    if (space != StrView::npos) {
        auto a = StrView{str.data, space};
        auto b = str.substr(space + 1, str.len - 1);

        auto x = a.toFloat();
        auto y = b.toFloat();

        Control::instance().x = x;
        Control::instance().y = y;
    }
}
