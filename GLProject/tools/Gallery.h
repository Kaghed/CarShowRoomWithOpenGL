#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RectangularPrism.h"
#include "GalleryFace.h"

class Gallery {
public:
    RectangularPrism logo;
    RectangularPrism wallBack;
    RectangularPrism wallRight;
    RectangularPrism wallLeft;
    RectangularPrism roof;
    RectangularPrism floor;
    GalleryFace wallFront;

    Gallery()
        : logo(50.0f, 125.0f, 5.0f, "textures/download.jpg", 1.0f),
        wallBack(1600.0f, 8000.0f, 40.0f, "textures/marble.jpg", 10.0f),
        wallRight(1600.0f, 40.0f, 7200.0f, "textures/marble.jpg", 10.0f),
        wallLeft(1600.0f, 40.0f, 7200.0f, "textures/marble.jpg", 10.0f),
        roof(40.0f, 8000.0f, 7200.0f, "textures/marble.jpg", 20.0f),
        floor(40.0f, 8000.0f, 7200.0f, "textures/wood.jpg", 40.0f),
        wallFront(1600.0f, 7200.0f, "textures/window.png", "textures/door.jpg") 
    {}

    void draw(glm::mat4& view, glm::mat4& projection, float doorAngle);

    void update(float deltaTime);
};