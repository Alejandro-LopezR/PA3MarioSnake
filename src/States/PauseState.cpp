#include "PauseState.h"

//--------------------------------------------------------------
PauseState::PauseState(){}
//--------------------------------------------------------------
PauseState::~PauseState(){}
//--------------------------------------------------------------
void PauseState::reset(){
    setFinished(false);
    setNextState("");
    return;
}
//--------------------------------------------------------------
void PauseState::update(){}
//--------------------------------------------------------------
void PauseState::draw(){
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    string text = "Press here to continue.";
    ofSetColor(ofColor::red);
    ofDrawRectangle(ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-9, 8*text.length(), -15);
    ofSetColor(ofColor::white);
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    return;
}
//--------------------------------------------------------------
void PauseState::keyPressed(int key){}
//--------------------------------------------------------------
void PauseState::mousePressed(int x, int y, int button){
    string text = "Press here to continue.";
    if(x >= ofGetWidth()/2-8*text.length()/2 && x <= ofGetWidth()/2+8*text.length()/2 && y >= ofGetHeight()/2-24 && y <= ofGetHeight()/2 && button == 0){
        setFinished(true);
        setNextState("GameState");
        return;
    }
}