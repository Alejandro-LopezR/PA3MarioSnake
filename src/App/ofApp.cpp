#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetWindowTitle("Snake");

    gameState = new GameState();
    menuState = new MenuState();
    loseState = new LoseState();
    pauseState = new PauseState();
    currentState = menuState;
    music.load("GustyGarden.wav");
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
        } else if(currentState->getNextState() == "PauseState"){
            pauseState->reset();
            currentState = pauseState;
        }else if(currentState->getNextState() == "LoseState"){
            loseState->reset();
            currentState = loseState;
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
void ofApp::mousePressed(int x, int y, int button){
    currentState->mousePressed(x, y, button);
}