#pragma <once>

#include "Entity.h"
#include "ofMain.h"

class StaticEntity: public Entity { //inherits from entity
    private:
        ofImage image;
        std::vector<ofImage> characters;

    public: 
        StaticEntity() : Entity(){}
        StaticEntity(int obstacleX, int obstacleY, int obstacleW, int obstacleH, ofImage image): Entity(obstacleX, obstacleY, obstacleW, obstacleH){ // inherits x, y, widht, and height values from entity
            this->image = image; //only custom variable for static entity
        }
        ~StaticEntity();

        void drawEntity();
        
        Entity* entity;

};