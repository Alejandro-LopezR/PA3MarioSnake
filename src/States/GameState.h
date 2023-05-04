#pragma once

#include "State.h"
#include "Snake.h"
#include "ofMain.h"
#include "StaticEntity.h"

class GameState : public State {
    public:
        GameState();
        ~GameState();
        void reset();
        void update();
        void draw();
        void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void foodSpawner();
        void loadObstacles();
        void obstacleSpawner();
        void drawFood();
        void drawObstacles();
        void drawStartScreen();
        void drawLostScreen();
        void drawBoardGrid();

        Snake* snake;
        StaticEntity* entity;
        std::vector<ofImage> characters;
        std::vector<StaticEntity> obstacles;
        
        bool foodSpawned = false;
        bool obstaclesSpawned = false;
        bool speedBoostAte = false;
        bool betterAppleAte = false;
        bool godModeAte = false;
        bool usePower = false;
        bool isGod = false;

        float foodAge;
        int foodDecay;
        int powerAge;


        ofColor foodColor;

        int currentFoodX;
        int currentFoodY;

        int currentEntityX;
        int currentEntityY;
        int obstacleW;
        int obstacleH;

        int score = 0; // used for score display and lose state

        int boardSizeWidth, boardSizeHeight;
        int cellSize; // Pixels
};