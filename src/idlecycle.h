#pragma once

struct IdleCycle {
    // Update and return new phase
    void update(float phase);

private:
    double phase = 0.;
};
