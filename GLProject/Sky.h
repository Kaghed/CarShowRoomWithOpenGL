#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>
#include <vector>
#include <string>
#include <vector>
#include <string>

using namespace std;

class Sky {
public:
    Sky();
    void draw(const glm::mat4& view, const glm::mat4& projection);

private:
    GLuint VAO, VBO;
    vector<GLuint> textures;
    Shader shader;
};