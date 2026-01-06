#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>
#include <vector>
#include <string>

using namespace std;

class Sky {
public:
    Sky();
    void draw( glm::mat4& view,  glm::mat4& projection);

private:
    GLuint VAO, VBO;
    vector<GLuint> textures;
    Shader shader;
};