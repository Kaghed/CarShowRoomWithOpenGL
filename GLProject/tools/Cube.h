#pragma once
#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>
#include "Polygon.h"

class Cube {
public:
	Cube();

	Cube(glm::vec3 center, float edge, glm::vec3 color);

	void transformation(glm::mat4 t);

	void draw(Shader& shader);

private:
	glm::vec3 center;
	float edge;
	glm::vec3 color;
	glm::mat4 model;
	std::vector<Polygon> faces;
};

#endif // CUBE_H