#include "AghedShowRoom.h"

float mergingUp = 190.0f;
float mergingBack = -3500.0f;
float mergingRight = 5500.0f;
void AghedShowRoom::draw(glm::mat4& view, glm::mat4& projection,
    float& doorSliding, float& doorOpenning, bool& isClosed)
{
 


    floor.draw(glm::vec3(0.0f+mergingRight , 37.5f + mergingUp, 0.0f + mergingBack), view, projection);
 
 
    float backZ = -1795.0f + mergingBack;
    
    wallBackLeft.draw(glm::vec3(-1270.0f + mergingRight, 450.0f + mergingUp, backZ), view, projection);
    wallBackRight.draw(glm::vec3(1270.0f + mergingRight, 450.0f + mergingUp, backZ), view, projection);
    wallBackTop.draw(glm::vec3(0.0f + mergingRight, 650.0f + mergingUp, backZ), view, projection);
 

    wallRight.draw(glm::vec3(2000.0f + mergingRight, 437.5f + mergingUp, 0.0f +mergingBack), view, projection);
    wallLeft.draw(glm::vec3(-2000.0f + mergingRight, 437.5 + mergingUp, 0.0f + mergingBack), view, projection);


   roof.draw(glm::vec3(0.0f + mergingRight, 837.5f + mergingUp, 0.0f + mergingBack), view, projection);


    garageDoor(doorOpenning, isClosed, view, projection);
    logo.draw(glm::vec3(0.0f + mergingRight, 600.0f + mergingUp, 1850.0f + mergingBack), view, projection);
    
    glassDoor(doorSliding, isClosed, view, projection );
   

 
    frontWallRight.draw(glm::vec3(1050.0f + mergingRight, 437.5f + mergingUp, 1805.0f + mergingBack), view, projection);
    frontWallLeft.draw(glm::vec3(-1050.0f + mergingRight, 437.5f + mergingUp, 1805.0f + mergingBack), view, projection);
    frontWallTop.draw(glm::vec3(0.0f + mergingRight, 537.5f + mergingUp, 1805.0f + mergingBack), view, projection);

 
}

void AghedShowRoom::glassDoor(float& doorSliding, bool isClosed, glm::mat4& view, glm::mat4& projection) {
    if (isClosed == true)
    {
        if (doorSliding > 0)
        {
            doorSliding -= 5.0f;

        }
    }
    else
    {
        if (doorSliding < 200)
        {
            doorSliding += 5.0f;
        }

    }
    glassDoorRight.draw(glm::vec3(-50 - doorSliding + mergingRight, 130.0f+mergingUp, 1805.0f + mergingBack), view, projection);
    glassDoorLeft.draw(glm::vec3(50 + doorSliding + mergingRight, 130.0f + mergingUp, 1805.0f + mergingBack), view, projection);


}

void AghedShowRoom::garageDoor(float& doorOpenning, bool isClosed,
    glm::mat4& view, glm::mat4& projection)
{
    float backZ = -1795.0f + mergingBack;
    if (isClosed == true)
    {
        if (doorOpenning > 0)
        {
            doorOpenning -= 5.0f;

        }
    }
    else
    {
        if (doorOpenning < 400)
        {
            doorOpenning += 5.0f;
        }

    }

    garageDoorv.draw(glm::vec3(mergingRight, 250.0f + mergingUp + doorOpenning, backZ), view, projection);
}

