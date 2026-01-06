#include"Gallery.h"


void Gallery::draw(glm::mat4& view, glm::mat4& projection,float& doorSliding,bool& isClosed)
{

    
    floor.draw(glm::vec3(0.0f, 150.0f, 0.0f), view, projection);


    wallBack.draw(glm::vec3(0.0f, 1750.0f, -7200.0f), view, projection);

    wallRight.draw(glm::vec3(8000.0f, 1750.0f, 0.0f), view, projection);
    wallLeft.draw(glm::vec3(-8000.0f, 1750.0f, 0.0f), view, projection);

    roof.draw(glm::vec3(0.0f, 3350.0f, 0.0f), view, projection);


    door(doorSliding,isClosed, view, projection);

    frontWallRight.draw(glm::vec3(4200.0f, 1750.0f, 7220.0f), view, projection);
    frontWallLeft.draw(glm::vec3(-4200, 1750.0f, 7220.0f), view, projection);
    frontWallTop.draw(glm::vec3(0.0f, 2150.0f, 7220.0f), view, projection);


   
  
    logo.draw(glm::vec3(0.0f, 2400.0f, 7400.0f), view, projection); 

    base.draw(glm::vec3(0.0f, 0.0f, 0.0f), view, projection);

    stairs.draw(glm::vec3(0.0f, 0.0f, 7850.0f),view,projection);
    
    
 
}

void Gallery::door(float& doorSliding,bool isClosed,glm::mat4& view, glm::mat4& projection) {
    if (isClosed==false)
    {
        if (doorSliding>0)
        {
            doorSliding -= 5.0f; 

        }
    }else
    {
        if (doorSliding<400)
        {
            doorSliding += 5.0f;
        }

    }
    doorRight.draw(glm::vec3(-200 - doorSliding, 550.0f, 7180.0f), view, projection);
    doorLeft.draw(glm::vec3(200 + doorSliding, 550.0f, 7180.0f), view, projection);


}




