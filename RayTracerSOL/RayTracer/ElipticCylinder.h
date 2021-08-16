#pragma once
#include "SceneObject.h"
class ElipticCylinder :
    public SceneObject
{
private:
    float elipticX; //a
    float elipticY; //b

    float minY = FLT_MAX;
    float maxY = FLT_MIN;
    bool capClosed = false;

public:
    ElipticCylinder(float radius, float minY, float maxY);

    // Inherited via SceneObject
    virtual bool TestIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, OUT HitInfo& hit) override;
    glm::vec3 GetNormal(glm::vec3 hitPoint);

};

