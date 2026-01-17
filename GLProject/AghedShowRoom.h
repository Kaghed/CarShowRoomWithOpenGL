#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RectangularPrism.h"

class AghedShowRoom
{
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
	RectangularPrism garageDoorv;
	RectangularPrism glassDoorRight;
	RectangularPrism glassDoorLeft;
	RectangularPrism wallBackLeft;
	RectangularPrism wallBackRight;
	RectangularPrism wallBackTop;



	bool isClosed;

	float addingHeight = 100.0f;
	AghedShowRoom() :
		logo(100.0f, 200.0f, 10.0f, "textures/logo.png", 1.0f),

	
				wallBack(750.0f , 2000.0f, 10.0f, "textures/Ag_wall.jpg", 10.0f),

		wallRight(400.0f, 10.0f, 1800.0f, "textures/Ag_wall.jpg", 10.0f),
		wallLeft(400.0f, 10.0f, 1800.0f, "textures/Ag_wall.jpg", 10.0f),
		roof(10.0f, 2000.0f, 1800.0f, "textures/Ag_ceil.jpg", 20.0f),
		floor(10.0f, 2000.0f, 1800.0f, "textures/Ag_floor.jpg", 40.0f),
		
		wallBackLeft(400.0f, 750.0f, 10.0f, "textures/Ag_wall.jpg", 10.0f),
		wallBackRight(400.0f, 750.0f, 10.0f, "textures/Ag_wall.jpg", 10.0f),
		wallBackTop(200.0f, 550.0f, 10.0f, "textures/Ag_wall.jpg", 10.0f),

		
		frontWallLeft(400.0f, 950.0f, 5.0f, "textures/Ag_glass.png", 4.0f),
		frontWallRight(400.0f, 950.0f, 5.0f, "textures/Ag_glass.png", 4.0f),
		frontWallTop(300.0f, 100.0f, 5.0f, "textures/Ag_glass.png", 1.0f),

	
		garageDoorv(200.0f, 520.0f, 5.0f, "textures/Ag_garage.jpg", 10.0f),

	
		glassDoorRight(100.0f, 50.0f, 5.0f, "textures/glass.png", 1.0f),
		glassDoorLeft(100.0f, 50.0f, 5.0f, "textures/glass.png", 1.0f),

		isClosed(true)
	{
	}



	void draw(glm::mat4& view, glm::mat4& projection, float& doorSliding, float& doorOpenning, bool& isClosed );

	void glassDoor(float& doorSliding, bool isClosed, glm::mat4& view, glm::mat4& projection);
	void garageDoor(float& doorOpenning, bool isClosed, glm::mat4& view, glm::mat4& projection);



};