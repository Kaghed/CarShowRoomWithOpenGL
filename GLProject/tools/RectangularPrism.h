#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<learnopengl/shader_m.h>
#include<glm/gtc/matrix_transform.hpp>
#include<stb_image.h>
#include<vector>
#include<string>
#include<iostream>


class RectangularPrism {
public:
    unsigned int VAO, VBO, texture;
    Shader shader; 
    float alpha=1.0f; 
    float h, w, d;

    RectangularPrism(float height, float width, float depth, const char* texPath, float tiling);
    void draw(const glm::vec3& pos, glm::mat4& view, glm::mat4& projection, bool blending = false);
    void setTexture(const char* texturePath);
};