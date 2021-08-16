#pragma once
#include "SceneObject.h"
class Cuboid :
    public SceneObject
{   
public :
    Cuboid(glm::vec3 corner1, glm::vec3 corner2);
    Cuboid(/*CUBE CONSTRUCTOR*/glm::vec3 center, int width );
    Cuboid(glm::vec3 dimensions /*X as Length , Y as Height, Z as Width */);

    //TODO MOVE / ROTATE / SCALE

    glm::vec3 firstCorner;
    glm::vec3 secondCorner;


    
   
    
public:
    // Inherited via SceneObject
    virtual bool TestIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, OUT HitInfo& hit) override;

};

