#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetWindowTitle("Snake");

    gameState = new GameState();
    menuState = new MenuState();
    currentState = menuState;
    music.load("Guatauba.wav");
    music.play();
    music.setLoop(true);

}

//--------------------------------------------------------------
void ofApp::update(){
    if(currentState->hasFinished()) {
        if(currentState->getNextState() == "GameState") {
            gameState->reset();
            currentState = gameState;
        } else if(currentState->getNextState() == "MenuState") {
            menuState->reset();
            currentState = menuState;
        }
    }
    currentState->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    currentState->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    currentState->keyPressed(key);
}
//--------------------------------------------------------------