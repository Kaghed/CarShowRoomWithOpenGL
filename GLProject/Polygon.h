#pragma once
#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>

class Polygon {
public:
	Polygon(std::vector<glm::vec3> v, glm::vec3 c);
	void transformation(glm::mat4 t);
	void draw(Shader& shader);
	void deleteBuffers();

protected:
	glm::vec3 head;
	std::vector<glm::vec3> vertices;
	glm::vec3 color;
	glm::mat4 model;
	GLuint VAO;

protected:
	Polygon();
};

class PolygonWithTexture : public Polygon {
public:
	PolygonWithTexture(std::vector<glm::vec3> v, std::vector<glm::vec2> t, glm::vec3 c = glm::vec3(1.0f, 1.0f, 1.0f));
	void transformation(glm::mat4 t);
	void setTexture(GLuint& t);
	void draw(Shader& shader);
	void deleteBuffers();

protected:
	std::vector<float> vertices;
	glm::vec3 color;
	glm::mat4 model;
	GLuint texture;
	GLuint VAO;
	PolygonWithTexture();
};

class PolygonWithTransparency : public Polygon {
public:
	PolygonWithTransparency(std::vector<glm::vec3> v, glm::vec4 c);
	void draw(Shader& shader);

protected:
	glm::vec4 color;
	PolygonWithTransparency();
};

#endif // POLYGON_H