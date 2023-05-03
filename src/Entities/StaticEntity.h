#pragma <once>

#include "Entity.h"
#include "ofMain.h"

class StaticEntity: public Entity {
    private:
        ofImage image;
        std::vector<ofImage> characters;

    public: 
        StaticEntity() : Entity(){}
        StaticEntity(int obstacleX, int obstacleY, int obstacleW, int obstacleH, ofImage image): Entity(obstacleX, obstacleY, obstacleW, obstacleH){
            this->image = image;
        }
        ~StaticEntity();

        void drawEntity();
        
        Entity* entity;

};