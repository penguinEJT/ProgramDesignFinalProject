#include "collisionbox.h"
#include <math.h>
#include <stdlib.h>
#include <raylib.h>

CollisionBox* CollisionBoxInit(Rectangle rec, float rotationAngle) {
    CollisionBox* box = (CollisionBox*)malloc(sizeof(CollisionBox));

    box->rec = rec;
    box->rotationAngle = rotationAngle;

    return box;
}

bool CheckCollsionBox(CollisionBox box1, CollisionBox box2) {
  
// Get centers of both boxes
    Vector2 center1 = { box1.rec.x + box1.rec.width / 2, box1.rec.y + box1.rec.height / 2 };
    Vector2 center2 = { box2.rec.x + box2.rec.width / 2, box2.rec.y + box2.rec.height / 2 };

    // Convert rotation angles to radians
    float theta1 = box1.rotationAngle * (PI / 180.0f);
    float theta2 = box2.rotationAngle * (PI / 180.0f);
    float cos1 = cosf(theta1), sin1 = sinf(theta1);
    float cos2 = cosf(theta2), sin2 = sinf(theta2);

    // Corners of box1 in local coordinates (relative to center)
    Vector2 local_corners1[4] = {
        { -box1.rec.width / 2, -box1.rec.height / 2 },
        {  box1.rec.width / 2, -box1.rec.height / 2 },
        { -box1.rec.width / 2,  box1.rec.height / 2 },
        {  box1.rec.width / 2,  box1.rec.height / 2 }
    };

    // Corners of box2 in local coordinates
    Vector2 local_corners2[4] = {
        { -box2.rec.width / 2, -box2.rec.height / 2 },
        {  box2.rec.width / 2, -box2.rec.height / 2 },
        { -box2.rec.width / 2,  box2.rec.height / 2 },
        {  box2.rec.width / 2,  box2.rec.height / 2 }
    };

    // Transform corners to world coordinates
    Vector2 world_corners1[4], world_corners2[4];
    for (int i = 0; i < 4; i++) {
        // Box1: Rotate and translate
        float x1 = local_corners1[i].x * cos1 - local_corners1[i].y * sin1;
        float y1 = local_corners1[i].x * sin1 + local_corners1[i].y * cos1;
        world_corners1[i].x = center1.x + x1;
        world_corners1[i].y = center1.y + y1;

        // Box2: Rotate and translate
        float x2 = local_corners2[i].x * cos2 - local_corners2[i].y * sin2;
        float y2 = local_corners2[i].x * sin2 + local_corners2[i].y * cos2;
        world_corners2[i].x = center2.x + x2;
        world_corners2[i].y = center2.y + y2;
    }

    // Define projection axes (normals of box1 and box2 edges)
    Vector2 axes[4] = {
        { cos1, sin1 },        // Box1 edge 1 normal
        { -sin1, cos1 },       // Box1 edge 2 normal
        { cos2, sin2 },        // Box2 edge 1 normal
        { -sin2, cos2 }        // Box2 edge 2 normal
    };

    // Project corners onto each axis and check for separation
    for (int i = 0; i < 4; i++) {
        Vector2 N = axes[i];
        float min1 = INFINITY, max1 = -INFINITY;
        float min2 = INFINITY, max2 = -INFINITY;

        // Project box1 corners
        for (int j = 0; j < 4; j++) {
            float proj = world_corners1[j].x * N.x + world_corners1[j].y * N.y;
            if (proj < min1) min1 = proj;
            if (proj > max1) max1 = proj;
        }

        // Project box2 corners
        for (int j = 0; j < 4; j++) {
            float proj = world_corners2[j].x * N.x + world_corners2[j].y * N.y;
            if (proj < min2) min2 = proj;
            if (proj > max2) max2 = proj;
        }

        // If projections don't overlap, no collision
        if (max1 < min2 || max2 < min1) return false;
    }

    // No separating axis found, collision exists
    return true;
}
