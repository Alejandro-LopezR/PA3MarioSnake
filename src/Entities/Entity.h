#pragma <once>

#include <iostream>
using namespace std;

class Entity{
    protected:
        int currentObstacleX;
        int currentObstacleY;
    public:
        int getObstacleX() { return currentObstacleX; }
        int getObstacleY() { return currentObstacleY; }

        virtual void drawObstacle() = 0;
};