#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>

class Ground {
public:
    unsigned int VBO, VAO;
    unsigned int texture;
    Shader shader;

    Ground();
    void draw(const glm::mat4& view, const glm::mat4& projection);
};