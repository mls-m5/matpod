#pragma once

// Global changable values used by many different cycle types
// That is for example idle cycle and walk cycle
struct SharedValues {
    float legBottomAngle = -1.f;
    float stepHeight = .8f;
};

SharedValues &sharedValues();
