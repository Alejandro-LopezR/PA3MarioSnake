#include "StaticEntity.h"

StaticEntity::~StaticEntity() {}

void StaticEntity::drawEntity(){
    image.draw(obstacleX, obstacleY, obstacleW, obstacleH); // drarws the obstacles
}