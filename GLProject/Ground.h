#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>
#include<iostream>
#include<stb_image.h>

class Ground {
public:
    unsigned int VBO, VAO;
    unsigned int texture;
    Shader shader;

    Ground();
    void draw( glm::mat4& view,  glm::mat4& projection);
};