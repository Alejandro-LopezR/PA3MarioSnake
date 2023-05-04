#include "Snake.h"
#include "ofMain.h"

Snake::Snake(int segmentSize, int boardSizeW, int boardSizeH) {
    body.push_back({8, 9});
    body.push_back({9, 9});
    body.push_back({10, 9});
    body.push_back({11, 9});
    this->direction = LEFT;
    this->crashed = false;
    this->segmentSize = segmentSize;
    this->boardSizeWidth = boardSizeW;
    this->boardSizeHeight = boardSizeH;
}

Snake::~Snake() {
    // TODO Auto-generated destructor stub
}

void Snake::update() {
    vector<int> oldHead = this->getHead();

    switch(this->direction) {
        case LEFT: {
            this->body[0][0] -= 1;
            break;
        }
        case DOWN: {
            this->body[0][1] += 1;
            break;
        }
        case RIGHT: {
            this->body[0][0] += 1;
            break;
        }
        case UP: {
            this->body[0][1] -= 1;      
            break;
        }
    }

    if(oldHead[0] == -1 || oldHead[0] == boardSizeWidth || oldHead[1] == -1 || oldHead[1] == boardSizeHeight) {
        if(!isGod){
            crashed = true;
            hitBorder = false;
            return;
        } else{
            crashed = false;
            hitBorder = true;
            return;
        }
    }


    int prevX = oldHead[0];
    int prevY = oldHead[1];
    for (int i = 1; i < this->body.size(); i++) {
        int currX = this->body[i][0];
        int currY = this->body[i][1];
        this->body[i][0] = prevX;
        this->body[i][1] = prevY;
        prevX = currX;
        prevY = currY;
    }

    if(!isGod){checkSelfCrash();}
}

void Snake::draw() { //changed snake to wiggler from Mario
    if(!isGod){
        for (int i = 0; i < body.size(); i++) {
            int curX = this->body[i][0];
            int curY = this->body[i][1];
            ofSetColor(255, 230, 0); // changed color of body to yellow
            ofDrawCircle((curX * 25) + 13, (curY * 25) + 13, 12);
            ofSetColor(77, 47, 7); //inner circle
            ofDrawCircle((curX * 25) + 9, (curY * 25) + 11, 8);
            ofSetColor(215, 122, 0); // outer circle
            ofDrawCircle((curX * 25) + 9, (curY * 25) + 11, 5);
            ofSetColor(255, 230, 0); // changed color of head to yellow
            ofDrawCircle((this->body[0][0] * 25) + 13, (this->body[0][1] * 25) + 13, 12); // head
            if (i == 0) { // draw nose on the head
                ofSetColor(48, 29, 4);
                int noseX, noseY, cheekX1, cheekY1, cheekX2, cheekY2;
                int cheekSize = 8;
                switch(this->direction) {
                    case LEFT: {
                        noseX = (curX * 25) + 29;
                        noseY = (curY * 25) + 13;
                        break;
                    }
                    case DOWN: {
                        noseX = (curX * 25) + 13;
                        noseY = (curY * 25) + 29;
                        cheekX1 = noseX - 7;
                        cheekY1 = (curY * 25) + 18;
                        cheekX2 = noseX + 7;
                        cheekY2 = (curY * 25) + 18;
                        break;
                    }
                    case RIGHT: {
                        noseX = (curX * 25) - 7;
                        noseY = (curY * 25) + 13;  
                        break;
                    }
                    case UP: {
                        noseX = (curX * 25) + 13;
                        noseY = (curY * 25) - 7;  
                        cheekX1 = (curX * 25) + 20;
                        cheekY1 = (curY * 25) + 8;
                        cheekX2 = (curX * 25) + 6;
                        cheekY2 = (curY * 25) + 8;
                        break;
                    }
                }
                ofDrawCircle(noseX, noseY, 8);//nose
                ofSetColor(255, 230, 0);
                ofDrawCircle(cheekX1, cheekY1, 6);//cheek
                ofDrawCircle(cheekX2, cheekY2, 6);//cheek
            }
        }
    } else {
        for (int i = 0; i < body.size(); i++) {
            int curX = this->body[i][0];
            int curY = this->body[i][1];
            ofSetColor(255, tint, tint); // changed color of body to yellow
            ofDrawCircle((curX * 25) + 13, (curY * 25) + 13, 12);
            ofSetColor(255, tint, tint); //inner circle
            ofDrawCircle((curX * 25) + 9, (curY * 25) + 11, 8);
            ofSetColor(255, tint, tint); // outer circle
            ofDrawCircle((curX * 25) + 9, (curY * 25) + 11, 5);
            ofSetColor(255, tint, tint); // changed color of head to yellow
            ofDrawCircle((this->body[0][0] * 25) + 13, (this->body[0][1] * 25) + 13, 12); // head
            if (i == 0) { // draw nose on the head
                ofSetColor(255, tint, tint);
                int noseX, noseY, cheekX1, cheekY1, cheekX2, cheekY2;
                int cheekSize = 8;
                switch(this->direction) {
                    case LEFT: {
                        noseX = (curX * 25) + 29;
                        noseY = (curY * 25) + 13;
                        break;
                    }
                    case DOWN: {
                        noseX = (curX * 25) + 13;
                        noseY = (curY * 25) + 29;
                        cheekX1 = noseX - 7;
                        cheekY1 = (curY * 25) + 18;
                        cheekX2 = noseX + 7;
                        cheekY2 = (curY * 25) + 18;
                        break;
                    }
                    case RIGHT: {
                        noseX = (curX * 25) - 7;
                        noseY = (curY * 25) + 13;  
                        break;
                    }
                    case UP: {
                        noseX = (curX * 25) + 13;
                        noseY = (curY * 25) - 7;  
                        cheekX1 = (curX * 25) + 20;
                        cheekY1 = (curY * 25) + 8;
                        cheekX2 = (curX * 25) + 6;
                        cheekY2 = (curY * 25) + 8;
                        break;
                    }
                }
                ofDrawCircle(noseX, noseY, 8);//nose
                ofSetColor(255, tint, tint);
                ofDrawCircle(cheekX1, cheekY1, 6);//cheek
                ofDrawCircle(cheekX2, cheekY2, 6);//cheek
            }
        }
    }
}

void Snake::changeDirection(Direction d) {

    if(this->direction == LEFT and d == RIGHT)
        return;
    if(this->direction == RIGHT and d == LEFT) 
        return;
    if(this->direction == UP and d == DOWN) 
        return;
    if(this->direction == DOWN and d == UP)
        return;
    
    this->direction = d;
}

void Snake::checkSelfCrash() {
    std::vector<std::vector<int>> snake = this->body;
    vector<int> head = snake[0];
    for(int i = 1; i < snake.size(); i++) {
        if(head[0] == snake[i][0] and head[1] == snake[i][1]) {
            crashed = true;
            return;
        }
    }
}

void Snake::grow() {
    vector<int> newSegment = this->getTail();
    this->body.push_back(newSegment);
}

bool Snake::godMode(bool change) {// makes it so the crash checkers don't work when gogMode is active
    return isGod = change;
}

void Snake::undo(){
    if(this->body.size() > 2){
        this->body.pop_back(); // removes end of snake
    }
}