#include "Sky.h"
#include "stb_image.h"
#include <iostream>

using namespace std; 

Sky::Sky() : shader("./shaders/vs/LightSource2.vs","./shaders/fs/LightSource2.fs")
{
    float faceVertices[] = {
        -500.0f, -500.0f,  500.0f,  0.0f, 0.0f,
         500.0f, -500.0f,  500.0f,  1.0f, 0.0f,
         500.0f,  500.0f,  500.0f,  1.0f, 1.0f,
         500.0f,  500.0f,  500.0f,  1.0f, 1.0f,
        -500.0f,  500.0f,  500.0f,  0.0f, 1.0f,
        -500.0f, -500.0f,  500.0f,  0.0f, 0.0f,

        -500.0f, -500.0f, -500.0f,  1.0f, 0.0f,
         500.0f, -500.0f, -500.0f,  0.0f, 0.0f,
         500.0f,  500.0f, -500.0f,  0.0f, 1.0f,
         500.0f,  500.0f, -500.0f,  0.0f, 1.0f,
        -500.0f,  500.0f, -500.0f,  1.0f, 1.0f,
        -500.0f, -500.0f, -500.0f,  1.0f, 0.0f,

        -500.0f, -500.0f, -500.0f,  0.0f, 0.0f,
        -500.0f, -500.0f,  500.0f,  1.0f, 0.0f,
        -500.0f,  500.0f,  500.0f,  1.0f, 1.0f,
        -500.0f,  500.0f,  500.0f,  1.0f, 1.0f,
        -500.0f,  500.0f, -500.0f,  0.0f, 1.0f,
        -500.0f, -500.0f, -500.0f,  0.0f, 0.0f,

         500.0f, -500.0f, -500.0f,  1.0f, 0.0f,
         500.0f, -500.0f,  500.0f,  0.0f, 0.0f,
         500.0f,  500.0f,  500.0f,  0.0f, 1.0f,
         500.0f,  500.0f,  500.0f,  0.0f, 1.0f,
         500.0f,  500.0f, -500.0f,  1.0f, 1.0f,
         500.0f, -500.0f, -500.0f,  1.0f, 0.0f,

         -500.0f,  500.0f, -500.0f,  0.0f, 1.0f,
          500.0f,  500.0f, -500.0f,  1.0f, 1.0f,
          500.0f,  500.0f,  500.0f,  1.0f, 0.0f,
          500.0f,  500.0f,  500.0f,  1.0f, 0.0f,
         -500.0f,  500.0f,  500.0f,  0.0f, 0.0f,
         -500.0f,  500.0f, -500.0f,  0.0f, 1.0f,

         -500.0f, -500.0f, -500.0f,  0.0f, 0.0f,
          500.0f, -500.0f, -500.0f,  1.0f, 0.0f,
          500.0f, -500.0f,  500.0f,  1.0f, 1.0f,
          500.0f, -500.0f,  500.0f,  1.0f, 1.0f,
         -500.0f, -500.0f,  500.0f,  0.0f, 1.0f,
         -500.0f, -500.0f, -500.0f,  0.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(faceVertices), faceVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    vector<string> faces = {
    "textures/right.bmp",  
    "textures/left.bmp",   
    "textures/top.bmp",  
    "textures/bottom.bmp", 
    "textures/front.bmp",  
    "textures/back.bmp" 
    };

    textures.resize(faces.size());
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(static_cast<GLsizei>(faces.size()), textures.data());

    for (int i = 0; i < faces.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, textures[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            if (nrChannels == 3) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
            else {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
            glGenerateMipmap(GL_TEXTURE_2D);


        }
        else {
           cout << "sorry boss the sky texture load failed "<<endl;
        }
        stbi_image_free(data);


    }
}

void Sky::draw(const glm::mat4& view, const glm::mat4& projection)
{
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    shader.setVec4("objectColor", glm::vec4(1.0f));

    glBindVertexArray(VAO);

    int facesOrder[6]={4,5,1,0,2,3};


    for (int i = 0; i < 6; i++) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[facesOrder[i]]);
        glDrawArrays(GL_TRIANGLES, i * 6, 6);
    }

}