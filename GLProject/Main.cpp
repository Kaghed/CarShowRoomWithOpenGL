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
#include "AghedShowRoom.h"
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
float doorOpenningAg = 0.0f;
float doorSlidingAg = 0.0f;
bool isClosedAg = true;
bool rotateBus = false;
float busAngle = 0.0f;
bool Rbressed = false;
int AgLight = 0;


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
    AghedShowRoom aghed;

    Shader modelShader("shaders/vs/Model.vs", "shaders/fs/Model.fs");
    Shader ourShader("./shaders/vs/L6.vs", "./shaders/fs/L6.fs");
    Shader lightSource("./shaders/vs/LightSource2.vs", "./shaders/fs/LightSource2.fs");
    Shader allShader("./shaders/vs/L5.vs", "./shaders/fs/L5-Model.fs");
    

    stbi_set_flip_vertically_on_load(false);
    Model ourModel("models/parking/scene.gltf");
    Model fountain("models/fountain/scene.gltf"); 
    Model streetLight("models/street_light/scene.gltf");

    Model Bus("./models/indonesia_ecolin_bus1/scene.gltf");
    Model Bench("./models/BusBench/scene.gltf");
    Model Stop("./models/Bus3/scene.gltf");
    Model Stage("./models/Stage/scene.gltf");
    Model StageLight1("./models/StageLight/scene.gltf");
    Model StageLight2("./models/StageLight/scene.gltf");





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

        ///// aghed
#pragma region Aghed
        glm::mat4 model1 = glm::mat4(1.0f);
        model1 = glm::translate(model1, glm::vec3(3600.0f, 230.0f + 110.0f, -3500.0f));
        model1 = glm::scale(model1, glm::vec3(300.0f));

        modelShader.setMat4("model", model1);
        Bench.Draw(modelShader);

        glm::mat4 model2 = glm::mat4(1.0f);

        model2 = glm::translate(model2, glm::vec3(4500.0f, 230.0f + 190.0f, -5200.0f));
        model2 = glm::scale(model2, glm::vec3(300.0f));

        modelShader.setMat4("model", model2);

        Stop.Draw(modelShader);

        glm::mat4 model3 = glm::mat4(1.0f);

        model3 = glm::translate(model3, glm::vec3(5300.0f, 230.0f + 20.0f, -3500.0f));

        model3 = glm::rotate(model3, busAngle, glm::vec3(0, 1, 0));
        model3 = glm::scale(model3, glm::vec3(170.0f));

        modelShader.setMat4("model", model3);
        Stage.Draw(modelShader);

        glm::mat4 model4 = glm::mat4(1.0f);
        model4 = glm::translate(model4, glm::vec3(6200.0f, 240.0f, -3500.0f));

        model4 = glm::rotate(model4, 5.0f, glm::vec3(0, 1, 0));
        model4 = glm::scale(model4, glm::vec3(10.0f));

        modelShader.setMat4("model", model4);
        StageLight1.Draw(modelShader);


        glm::mat4 model5 = glm::mat4(1.0f);

        model5 = glm::translate(model5, glm::vec3(5300.0f, 250.0f, -3500.0f));

        if (rotateBus) {
            busAngle += deltaTime / 3;
        }

        model5 = glm::rotate(model5, busAngle, glm::vec3(0, 1, 0));
        model5 = glm::scale(model5, glm::vec3(100.0f));

        allShader.use();
     
        allShader.setMat4("view", view);
        allShader.setMat4("projection", projection);
        allShader.setMat4("model", model5);

        allShader.setVec3("lightPos1", glm::vec3(6200.0f, 240.0f, -3500.0f));
  
        glm::vec3 stageLight1Pos = glm::vec3(6200.0f, 240.0f, -3500.0f);
        glm::vec3 busPos = glm::vec3(5300.0f, 250.0f, -3500.0f);

        allShader.setVec3("spotPos", stageLight1Pos);
        allShader.setVec3("spotDir", glm::normalize(busPos - stageLight1Pos)); 
        allShader.setFloat("innerCutOff", glm::cos(glm::radians(30.0f)));
        allShader.setFloat("outerCutOff", glm::cos(glm::radians(45.0f)));  
        allShader.setVec3("spotColor", glm::vec3(1.0f, 1.0f, 1.0f));
        allShader.setVec3("viewPos", camera.Position);
 
        allShader.setVec3("objectColor", glm::vec3(1.0f));

        allShader.setInt("lightMode", AgLight);


     

#pragma endregion Aghed


        gallery.draw(view, projection, doorSliding, isClosed);
       aghed.draw(view, projection, doorSlidingAg, doorOpenningAg, isClosedAg);
       Bus.Draw(allShader);


        ourShader.use();

 

        





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


    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && !Rbressed) {
        rotateBus = !rotateBus;
        Rbressed = true;
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) {
        Rbressed = false;
    }

    static bool Lpressed = false;



    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && !Lpressed) {
        AgLight++;
        if (AgLight > 2) AgLight = 0; 
        Lpressed = true;
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE) {
        Lpressed = false;
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