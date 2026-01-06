#include"RectangularPrism.h"

using namespace std; 





	RectangularPrism::RectangularPrism(float h, float w, float d, const char* texturePath, float t) : shader("./shaders/vs/LightSource2.vs", "./shaders/fs/LightSource2.fs") {
        float vertices[] = {
            -w, -h,  d,   0.0f, 0.0f,
             w, -h,  d,   t,    0.0f,
             w,  h,  d,   t,    t,

             w,  h,  d,   t,    t,
            -w,  h,  d,   0.0f, t,
            -w, -h,  d,   0.0f, 0.0f,

            -w, -h, -d,   t,    0.0f,
            -w,  h, -d,   t,    t,
             w,  h, -d,   0.0f, t,

             w,  h, -d,   0.0f, t,
             w, -h, -d,   0.0f, 0.0f,
            -w, -h, -d,   t,    0.0f,

            -w,  h,  d,   t,    t,
            -w,  h, -d,   0.0f, t,
            -w, -h, -d,   0.0f, 0.0f,

            -w, -h, -d,   0.0f, 0.0f,
            -w, -h,  d,   t,    0.0f,
            -w,  h,  d,   t,    t,

             w,  h,  d,   0.0f, t,
             w, -h, -d,   t,    0.0f,
             w,  h, -d,   t,    t,

             w, -h, -d,   t,    0.0f,
             w,  h,  d,   0.0f, t,
             w, -h,  d,   0.0f, 0.0f,

             -w,  h, -d,   0.0f, t,
             -w,  h,  d,   0.0f, 0.0f,
              w,  h,  d,   t,    0.0f,

              w,  h,  d,   t,    0.0f,
              w,  h, -d,   t,    t,
             -w,  h, -d,   0.0f, t,

             -w, -h, -d,   t,    t,
              w, -h,  d,   0.0f, 0.0f,
             -w, -h,  d,   t,    0.0f,

              w, -h,  d,   0.0f, 0.0f,
             -w, -h, -d,   t,    t,
              w, -h, -d,   0.0f, t
        };

        glGenVertexArrays(1, &VAO); 
        glGenBuffers(1, &VBO); 

        glBindVertexArray(VAO); 
        glBindBuffer(GL_ARRAY_BUFFER, VBO); 
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); 
        glEnableVertexAttribArray(0); 

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float))); 
        glEnableVertexAttribArray(2); 

        setTexture(texturePath); 



	}


     void RectangularPrism::setTexture(const char* texturePath) {

        glGenTextures(1, &texture); 
        glBindTexture(GL_TEXTURE_2D, texture); 
       
        int width, hieght, nrChannels; 

        unsigned char* data = stbi_load(texturePath, &width, &hieght, &nrChannels,0);

        if (data) {

            if (nrChannels == 3) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, hieght,0,GL_RGB,GL_UNSIGNED_BYTE,data);
            }
            else if(nrChannels==4) {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, hieght, 0, GL_RGBA, GL_UNSIGNED_BYTE,data);
            }

                glGenerateMipmap(GL_TEXTURE_2D);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                stbi_image_free(data);
        }
        else {
            cout << "sorry boss the texture failed to load " << endl; 
        }


    }

    void RectangularPrism::draw(const glm::vec3& pos, glm::mat4& view,glm::mat4& projection) {
        shader.use();
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setVec4("objectColor", glm::vec4(1.0f, 1.0f, 1.0f, alpha));

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,36);


    }



