#pragma <once>

#include<iostream>
using namespace std;
class Entity{ //entity class which is inherited by StaticEntity
    public:
        int obstacleX;
        int obstacleY;
        int obstacleW;
        int obstacleH;

        Entity(): obstacleX(0), obstacleY(0), obstacleW(0),obstacleH(0){}

        Entity(int obstacleX, int obstacleY, int obstacleW, int obstacleH) : obstacleX(obstacleX), obstacleY(obstacleY), obstacleW(obstacleW),obstacleH(obstacleH){} //Entity constructor
        virtual ~Entity() {}
		
        virtual void drawEntity() = 0; //entity method


        //getters
        int getObstacleX() { return obstacleX; }
        int getObstacleY() { return obstacleY; }
        int getObstacleW() { return obstacleW; }
        int getObstacleH() { return obstacleH; }

        //setters
        void setObstacleX(int obstacleX){
            this->obstacleX = obstacleX;
        }
        void setObstacleY(int obstacleY){
            this->obstacleY = obstacleY;
        }


};