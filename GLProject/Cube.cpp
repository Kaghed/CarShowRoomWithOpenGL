#include "Cube.h"

#include <vector>
#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Polygon.h"

using namespace std;
using namespace glm;

Cube::Cube(vec3 center, float edge, vec3 color) {
	this->center = center;
	this->edge = edge;
	this->color = color;
	faces = {};
	model = mat4(1.0f);

	vector<vec3> vertices1 = {};
	vertices1.push_back(vec3(center.x - (edge / 2), center.y - (edge / 2), center.z - (edge / 2)));
	vertices1.push_back(vec3(center.x - (edge / 2), center.y - (edge / 2) + edge, center.z - (edge / 2)));
	vertices1.push_back(vec3(center.x - (edge / 2) + edge, center.y - (edge / 2) + edge, center.z - (edge / 2)));
	vertices1.push_back(vec3(center.x - (edge / 2) + edge, center.y - (edge / 2), center.z - (edge / 2)));
	Polygon Face1(vertices1, color);
	Polygon Face2(vertices1, color);

	std::vector<vec3> vertices3 = {};
	vertices3.push_back(vec3(center.x - (edge / 2), center.y - (edge / 2), center.z - (edge / 2)));
	vertices3.push_back(vec3(center.x - (edge / 2), center.y - (edge / 2), center.z - (edge / 2) + edge));
	vertices3.push_back(vec3(center.x - (edge / 2) + edge, center.y - (edge / 2), center.z - (edge / 2) + edge));
	vertices3.push_back(vec3(center.x - (edge / 2) + edge, center.y - (edge / 2), center.z - (edge / 2)));
	Polygon Face3(vertices3, color);
	Polygon Face4(vertices3, color);

	std::vector<vec3> vertices5 = {};
	vertices5.push_back(vec3(center.x - (edge / 2), center.y - (edge / 2), center.z - (edge / 2) + edge));
	vertices5.push_back(vec3(center.x - (edge / 2), center.y - (edge / 2) + edge, center.z - (edge / 2) + edge));
	vertices5.push_back(vec3(center.x - (edge / 2), center.y - (edge / 2) + edge, center.z - (edge / 2)));
	vertices5.push_back(vec3(center.x - (edge / 2), center.y - (edge / 2), center.z - (edge / 2)));
	Polygon Face5(vertices5, color);

	std::vector<vec3> vertices6 = {};
	Polygon Face6(vertices5, color);

	faces.push_back(Face1);
	faces.push_back(Face2);
	faces.push_back(Face3);
	faces.push_back(Face4);
	faces.push_back(Face5);
	faces.push_back(Face6);
}

void Cube::transformation(glm::mat4 t) {
	model = t;
}

void Cube::draw(Shader& shader)
{
	faces[0].transformation(model);
	faces[2].transformation(model);
	faces[4].transformation(model);

	faces[1].transformation(translate(model, vec3(0.0f, 0.0f, edge)));
	faces[3].transformation(translate(model, vec3(0.0f, edge, 0.0f)));
	faces[5].transformation(translate(model, vec3(edge, 0.0f, 0.0f)));


	faces[0].draw(shader);
	faces[1].draw(shader);
	faces[2].draw(shader);
	faces[3].draw(shader);
	faces[4].draw(shader);
	faces[5].draw(shader);
}