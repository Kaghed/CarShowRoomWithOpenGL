#include "Ground.h"

using namespace std; 

Ground::Ground()
    : shader("./shaders/vs/LightSource2.vs","./shaders/fs/LightSource2.fs")
{
    float vertices[] = {
    -20000.0f, 0.0f, -20000.0f,    0.0f,    0.0f,
     20000.0f, 0.0f, -20000.0f,  400.0f,    0.0f,
     20000.0f, 0.0f,  20000.0f,  400.0f,  400.0f,

     20000.0f, 0.0f,  20000.0f,  400.0f,  400.0f,
    -20000.0f, 0.0f,  20000.0f,    0.0f,  400.0f,
    -20000.0f, 0.0f, -20000.0f,    0.0f,    0.0f
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); 

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("textures/asphalt.jpg", &width, &height, &nrChannels, 0);

    if (data) {
       
        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else {
        cout << "unfoutunatly failed to load ground texture" << endl;
    }
}

void Ground::draw( glm::mat4& view,  glm::mat4& projection)
{
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    shader.setVec4("objectColor", glm::vec4(1.0f));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}