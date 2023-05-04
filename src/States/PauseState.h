#pragma <once>

#include "State.h"
#include "ofMain.H"

class PauseState: public State { // creates what you see when pause state is activated
    public:
        PauseState();
        ~PauseState();
        void reset();
        void update();
        void draw();
        void keyPressed(int key);
        void mousePressed(int x, int y, int button);
};