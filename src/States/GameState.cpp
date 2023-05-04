#include "GameState.h"

//--------------------------------------------------------------
GameState::GameState() {
    foodSpawned = false;
    cellSize = 25;
    boardSizeWidth = 64;
    boardSizeHeight = 36;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
    loadObstacles();
}
//--------------------------------------------------------------
GameState::~GameState() {
    if(getIsPaused()){
    delete snake;
    delete entity;
    }
}
//--------------------------------------------------------------
void GameState::reset() {
    if(getIsPaused()){
        delete snake;
        delete entity;
        snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
        foodSpawned = false;
        obstaclesSpawned = false;
    }
    setFinished(false);
    setNextState("");
}
//--------------------------------------------------------------
void GameState::update() {
    
    if(snake->isCrashed() && !isGod) {
        score = 0; // resets score to 0 when player loses
        setIsPaused(true);
        this->setNextState("LoseState");
        this->setFinished(true);
        return;
    }

    if(snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY) {
        foodSpawned = false;
        score += 10;
        if(score != 110){snake->grow();} //different ifs with different scores set up which power up should exist
        if(score == 60){speedBoostAte = true;}
        if(score == 110){
            betterAppleAte = true; // these bool variables make it so only one power up is active at a time
            speedBoostAte = false;
        }
        if(score == 160){
            godModeAte = true;
            betterAppleAte = false;
        }
    }

    for(auto entity: obstacles){ // generates obstacles where there is no snake
        if(!isGod && snake->getHead()[0] == entity.getObstacleX()/25 && snake->getHead()[1] == entity.getObstacleY()/25){
            score = 0;
            this->setFinished(true);
            this->setNextState("LoseState");
            return;
        }
    }

    obstacleSpawner(); // checks if an obstacle should be drawn
    foodSpawner();
    if(!snake->getHitBorder()){ // if snake hits border in godMode makes it so it does not move
        if(ofGetFrameNum() % 6 == 0) {
            snake->update();
        }
    }

    if(speedBoostAte){// super speed power up
        if(usePower){// makes it so it only happens when b is pressed
            if(ofGetFrameNum() % 3 == 0 ){ // makes snake move faster
                snake->update();
            }
            if (ofGetElapsedTimef() - powerAge >= 15){ // power up ends after determined time
                speedBoostAte = false;
                usePower = false;// resets function
            }
        }
    }

    if(betterAppleAte){
        if(usePower){
            snake->grow();
            snake->grow();
            betterAppleAte = false;
            usePower = false;
        }
    }

    if(godModeAte){
        if(usePower){
            snake->godMode(true);
            isGod = true; // makes it so checkers don't work when godMode is active
            if(ofGetElapsedTimef() - powerAge >= 10){ // power up ends after determined time
                snake->godMode(false);
                isGod = false;
                godModeAte = false;
                usePower = false;
            }
        }
    }

}
//--------------------------------------------------------------
void GameState::draw() {
    drawBoardGrid();
    snake->draw();
    drawFood();
    drawObstacles(); // draws the obstacles
    ofSetColor(ofColor::white); // sets color of string to white
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWindowWidth()/2 - 50, 10); // draws score in game
    if(speedBoostAte){ofDrawBitmapString("Press 'b' to go faster!", ofGetWindowWidth()/2 - 50, 20);} //tells you which power up is available
    if(betterAppleAte){ofDrawBitmapString("Press 'b' to grow TWICE as long!", ofGetWindowWidth()/2 - 50, 20);}
    if(godModeAte){ofDrawBitmapString("Press 'b' to get ANGRY!", ofGetWindowWidth()/2 - 50, 20);}
}
//--------------------------------------------------------------
void GameState::keyPressed(int key) {

    //if(key != OF_KEY_LEFT && key != OF_KEY_RIGHT && key != OF_KEY_UP && key != OF_KEY_DOWN && key != 'a') { return; } 

    switch(key) {
        case OF_KEY_LEFT:
            snake->changeDirection(LEFT);
            break;
        case OF_KEY_RIGHT:
            snake->changeDirection(RIGHT);
            break;
        case OF_KEY_UP:
            snake->changeDirection(UP);
            break;
        case OF_KEY_DOWN:
            snake->changeDirection(DOWN);
            break;
        case 'a': // debug key 'a'
            score += 10; // adds 10 points to score
            break;
        case 'u':
            snake->undo();
            break;
        case 'p': // activates pause state
            setFinished(true);
            setNextState("PauseState");
            break;
        case 'b': // activates current power up
            if(speedBoostAte || betterAppleAte || godModeAte){usePower = true;}
            break;
    }
}
//--------------------------------------------------------------
void GameState::mousePressed(int x, int y, int button){}
//--------------------------------------------------------------
void GameState::foodSpawner() {
    if(!foodSpawned) {
        bool isInSnakeBody;
        do {
            isInSnakeBody = false;
            currentFoodX = ofRandom(1, boardSizeWidth-1);
            currentFoodY = ofRandom(1, boardSizeHeight-1);
            for(unsigned int i = 0; i < snake->getBody().size(); i++) {
                if(currentFoodX == snake->getBody()[i][0] and currentFoodY == snake->getBody()[i][1]) {
                    isInSnakeBody = true;
                }
            }
        } while(isInSnakeBody);
        foodSpawned = true;
        foodAge = ofGetElapsedTimef();
        foodDecay = 30;
    }
    else{ // makes food turn brown
        int currentTime = ofGetElapsedTimef();
        if(currentTime - foodAge >= foodDecay){
            foodSpawned = false;
            foodSpawner();
        }
        else{
            float decayLevel = (currentTime - foodAge) / foodDecay;
            foodColor = ofColor(255 * (1 - decayLevel), 255 * (1 - decayLevel) * 0.5, 0);

        }
    }
}
//--------------------------------------------------------------
void GameState::loadObstacles() {
    ofImage image; //loads images used in obstacle
    image.load("Mario.png");
    characters.push_back(image);
    image.load("Daisy.png");
    characters.push_back(image);
    image.load("Luma.png");
    characters.push_back(image);
    image.load("Luigi.png");
    characters.push_back(image);
    image.load("DonkeyKong.png");
    characters.push_back(image);
    image.load("Toadette.png");
    characters.push_back(image);
    image.load("Peach.png");
    characters.push_back(image);
    image.load("Rosalina.png");
    characters.push_back(image);
    image.load("Toad.png");
    characters.push_back(image);
    image.load("Yoshi.png");
    characters.push_back(image);
}
//--------------------------------------------------------------
void GameState::obstacleSpawner(){ //uses same logic as food spawner but for obstacles
    if(!obstaclesSpawned){
        for(int i = 0; i < 10; i++){
            currentEntityX = ofRandom(1, boardSizeWidth - 10);
            currentEntityY = ofRandom(1, boardSizeHeight - 10);
            StaticEntity entity(currentEntityX*cellSize, currentEntityY*cellSize, cellSize, cellSize, characters[ofRandom(10)]);
            obstacles.push_back(entity);
            obstaclesSpawned = true;
        }
    }
}
//--------------------------------------------------------------
void GameState::drawFood() {
    if(foodSpawned && score != 50 && score != 100 && score != 150) {
        ofSetColor(foodColor);
        ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
    } else if(foodSpawned && score == 50){ //speed boost
        powerAge = ofGetElapsedTimef(); // used for power up duration
        ofSetColor(ofColor::white);
        ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
    } else if(foodSpawned && score == 100){ //better apple
        ofSetColor(ofColor::orange);
        ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
    } else if(foodSpawned && score == 150){ //god mode
        powerAge =  ofGetElapsedTimef();
        ofSetColor(ofColor::yellow);
        ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
    }
}
//--------------------------------------------------------------
void GameState::drawObstacles(){// actually draws the obstacle using draw method from static entity
    ofSetColor(255,255,255);
    if(obstaclesSpawned){
        for(auto& obstacle : obstacles){
            obstacle.drawEntity();
        }
    }
}
//--------------------------------------------------------------
void GameState::drawStartScreen() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "Press any arrow key to start.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    return;
}
//--------------------------------------------------------------
void GameState::drawLostScreen() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "You lost! Press any arrow key to play again";
    string text2 = "or press ESC to exit.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    ofDrawBitmapString(text2, ofGetWidth()/2-8*text2.length()/2, ofGetHeight()/2+2);
    return;
}
//--------------------------------------------------------------
void GameState::drawBoardGrid() {
    
    ofDrawGrid(25, 64, false, false, false, true);
    
    // ofSetColor(ofColor::white);
    // for(int i = 0; i <= boardSize; i++) {
    //     ofDrawLine(i*cellSize, 0, i*cellSize, ofGetHeight());
    //     ofDrawLine(0, i*cellSize, ofGetWidth(), i*cellSize);
    // }
}
//--------------------------------------------------------------

