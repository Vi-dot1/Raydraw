#pragma once

namespace Program {

enum class State {DEFAULT};

struct pState
{
    State state = State::DEFAULT;
};

const pState& getProgramState();
const State& getState();

}