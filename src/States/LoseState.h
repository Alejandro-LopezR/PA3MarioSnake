#pragma once

#include "State.h"
#include "ofMain.h"

class LoseState : public State {// crates what you see when lose state is activated

public:
    LoseState();
    ~LoseState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);

    ofImage gameOver;

};
