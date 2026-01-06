#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RectangularPrism.h"


class Gallery {
public:
    RectangularPrism wallBack;
    RectangularPrism wallRight;
    RectangularPrism wallLeft;
    RectangularPrism roof;
    RectangularPrism floor;
    RectangularPrism frontWallLeft; 
    RectangularPrism frontWallRight;
    RectangularPrism frontWallTop; 
    RectangularPrism logo; 
    RectangularPrism base; 
    RectangularPrism stairs; 

    RectangularPrism doorRight; 
    RectangularPrism doorLeft; 



    bool isClosed; 


    Gallery() :
        logo(400.0f, 800.0f, 40, "textures/tom.jpg",1.0f),
        wallBack(1600.0f, 8000.0f, 40.0f, "textures/marble.jpg", 10.0f),
        wallRight(1600.0f, 40.0f, 7200.0f, "textures/marble.jpg", 10.0f),
        wallLeft(1600.0f, 40.0f, 7200.0f, "textures/marble.jpg", 10.0f),
        roof(40.0f, 8000.0f, 7200.0f, "textures/marble.jpg", 20.0f),
        floor(40.0f, 8000.0f, 7200.0f, "textures/wood.jpg", 40.0f),
        frontWallLeft(1600.0f, 3800.0f, 20.0f, "textures/glass.png", 4.0f),
        frontWallRight(1600.0f, 3800.0f, 20.0f, "textures/glass.png", 4.0f),
        frontWallTop(1200.0f, 400.0f, 20.0f, "textures/glass.png", 1.0f),
        base(150.0f, 8500.0f, 7800.0f, "textures/marble.jpg", 10.0f),
        stairs(80.0f,800.0f,80.0f,"textures/marble.jpg",2.0f),
        doorRight(400.0f,200.0f,20.0f,"textures/glass.png",1.0f),
        doorLeft(400.0f, 200.0f, 20.0f, "textures/glass.png", 1.0f)
        
    {}

    void draw(glm::mat4& view, glm::mat4& projection, float& doorSliding,bool& isClosed);

    void door(float& doorSliding,bool isClosed, glm::mat4& view, glm::mat4& projection);

 

};