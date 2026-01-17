#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include<learnopengl/model.h>
#include "stb_image.h"
#include <iostream>

using namespace std;
using namespace glm;


#include "Sky.h"
#include "Ground.h"
#include "Gallery.h";
#include"RectangularPrism.h"

int SCR_WIDTH = 1800;
int SCR_HEIGHT = 800;

Camera camera(vec3(0.0f, 400.0f, 15.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

GLFWwindow* initWindow();
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


float doorSliding = 0.0f;
bool isClosed = false;





int main() {



    glfwInit();
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "its clearly a fucking window", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "failed to downlad glad " << endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);



    Ground ground;
    Sky sky;
    Gallery gallery;

    Shader modelShader("shaders/vs/Model.vs", "shaders/fs/Model.fs");
    stbi_set_flip_vertically_on_load(false);
    Model ourModel("models/parking/scene.gltf");
    Model fountain("models/fountain/scene.gltf"); 
    Model streetLight("models/street_light/scene.gltf");





    while (!glfwWindowShouldClose(window)) {
        modelShader.use(); 
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 1000000.0f);
        mat4 view = camera.GetViewMatrix();

        ground.draw(view, projection);
        sky.draw(view, projection);

        mat4 model = mat4(1.0f);
        model = translate(model, vec3(600.0f, 55.0f, 13500.0f));
        model = rotate(model, radians(180.0f), vec3(0.0f, 1.0f, 0.0f));
        model = scale(model, vec3(200.0f, 250.0f, 150.0f));
        modelShader.setMat4("model", model);
        ourModel.Draw(modelShader);

        model = mat4(1.0f);
        model = translate(model, vec3(0.0f, 25.0f, 10000.0f));
        model = rotate(model, radians(180.0f), vec3(0.0f, 1.0f, 0.0f));
        model = scale(model, vec3(1.5f, 1.50f, 1.5f));
        modelShader.setMat4("model", model);
        fountain.Draw(modelShader);

        model = mat4(1.0f);
        model = translate(model, vec3(600.0f, 30.0f, 7700.0f));
        model = rotate(model, radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
        model = scale(model, vec3(80.5f, 80.50f, 80.5f));
        modelShader.setMat4("model", model);
        streetLight.Draw(modelShader);

        model = mat4(1.0f);
        model = translate(model, vec3(-800.0, 30.0f, 7700.0f));
        model = rotate(model, radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
        model = scale(model, vec3(80.5f, 80.50f, 80.5f));
        modelShader.setMat4("model", model);
        streetLight.Draw(modelShader);

        gallery.draw(view, projection, doorSliding, isClosed);



 

        





        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        if (isClosed == false) {
            isClosed = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        if (isClosed == true) {
            isClosed = false;
        }
    }


}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}