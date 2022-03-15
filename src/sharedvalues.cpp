#include "sharedvalues.h"

SharedValues &sharedValues() {
    static auto values = SharedValues{};
    return values;
}
