#include "Polygon.h"

#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>
#include <vector>

Polygon::Polygon(std::vector<glm::vec3> v, glm::vec3 c) {
	vertices = v;
	head = v.at(0);
	color = c;
	model = glm::mat4(1.0f);

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);

	// position attribute
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

	// normal attribute
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(1);
	this->VAO = VAO;
}

void Polygon::transformation(glm::mat4 t) {
	model = t;
}

void Polygon::draw(Shader& shader)
{
	shader.setVec4("objectColor", glm::vec4(color, 1.0f));
	shader.setMat4("model", model);
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());
}

void Polygon::deleteBuffers() {
	glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
}

Polygon::Polygon() {
	vertices = {};
	head = glm::vec3();
	color = glm::vec3();
	model = glm::mat4(1.0f);
	VAO = 0;
}

PolygonWithTexture::PolygonWithTexture(std::vector<glm::vec3> v, std::vector<glm::vec2> t, glm::vec3 c) {
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].length(); j++)
			vertices.push_back(v[i][j]);
		for (int j = 0; j < t[i].length(); j++)
			vertices.push_back(t[i][j]);
	}
	color = c;
	model = glm::mat4(1.0f);
	texture = 0;

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);

	// position attribute
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2); //2 is to work with the Model class
	this->VAO = VAO;
}

void PolygonWithTexture::transformation(glm::mat4 t) {
	model = t;
}

void PolygonWithTexture::setTexture(GLuint& t) {
	texture = t;
}

void PolygonWithTexture::draw(Shader& shader)
{
	shader.setVec3("objectColor", color);
	shader.setMat4("model", model);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 5);
}

void PolygonWithTexture::deleteBuffers() {
	glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
}

PolygonWithTexture::PolygonWithTexture() {
	vertices = {};
	texture = 0;
	head = glm::vec3();
	color = glm::vec3();
	model = glm::mat4(1.0f);
	VAO = 0;
}

PolygonWithTransparency::PolygonWithTransparency(std::vector<glm::vec3> v, glm::vec4 c) {
	vertices = v;
	std::vector<glm::vec3> normals = {};
	head = v.at(0);
	color = c;
	model = glm::mat4(1.0f);

	GLuint VBO, NBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &NBO);

	// position attribute
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

	for (int i = 0; i < v.size(); i++) {
		glm::vec3 A = v[i % v.size()];
		glm::vec3 B = v[(i + 1) % v.size()];
		glm::vec3 C = v[(i + 2) % v.size()];
		glm::vec3 U = B - A;
		glm::vec3 V = C - A;
		normals.push_back(glm::normalize(glm::cross(U, V)));
	}

	// normal attribute
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(1);
	this->VAO = VAO;
}

void PolygonWithTransparency::draw(Shader& shader)
{
	shader.setVec4("objectColor", color);
	shader.setMat4("model", model);
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());
}

PolygonWithTransparency::PolygonWithTransparency() {
	vertices = {};
	head = glm::vec3();
	color = glm::vec4();
	model = glm::mat4(1.0f);
	VAO = 0;
}