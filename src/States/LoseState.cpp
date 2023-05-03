#include "LoseState.h"

//--------------------------------------------------------------
LoseState::LoseState() {
    gameOver.load("GameOver.png");

}   
//--------------------------------------------------------------
LoseState::~LoseState() {

}
//--------------------------------------------------------------
void LoseState::reset() {
    setFinished(false);
    setNextState("");
    return;
}
//--------------------------------------------------------------
void LoseState::update() {

}
//--------------------------------------------------------------
void LoseState::draw() {
    gameOver.draw(0,0,ofGetWidth(),ofGetHeight());
    // string text = "Press any arrow key to play again.";
    // ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    return;
}
//--------------------------------------------------------------
void LoseState::keyPressed(int key) {
    // if(key == OF_KEY_LEFT || key == OF_KEY_RIGHT || key == OF_KEY_UP || key == OF_KEY_DOWN) {
    //     setFinished(true);
    //     setNextState("GameState");
    //     return;
    // }
}
//--------------------------------------------------------------
void LoseState::mousePressed(int x, int y, int button){}
