#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/shader_m.h>
#include "RectangularPrism.h"

class GalleryFace {
public:
    unsigned int VAO, VBO, texture;
    Shader shader; 
    float doorWidth = 600.0f;
    float doorHeight = 300.0f;

    RectangularPrism* door;

    GalleryFace(float h, float w, const char* wallTex, const char* doorTex);


    void draw(const glm::vec3& pos, glm::mat4& view, glm::mat4& projection, float openAngle, float alpha=1.0f);
}; 