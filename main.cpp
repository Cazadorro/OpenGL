#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_program.h"
#include "camera.h"
#include "texture2d.h"
#include "glutilprimitives.h"
#include "simplexnoise.h"
//#include "gradientnoise.h"

#include "contrib_active_interp.h"
#include "OctaveNoise.h"
#include "murmurhash3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void processInput(GLFWwindow *window, const float deltaTime);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

unsigned char *createTextureMemory(int width, int height){
    return new unsigned char[width*height * 4];
}

void accumTextureVals(int i, int j, int width, unsigned char* temp_texture, double d_noise){
    uint8_t noise = static_cast<uint8_t>(rint(d_noise));
    temp_texture[j*4 + (i * width * 4) + 0] = (noise);
    temp_texture[j*4 + (i * width * 4) + 1] = (noise);
    temp_texture[j*4 + (i * width * 4) + 2] = (noise);
    temp_texture[j*4 + (i * width * 4) + 3] = (255);
}

double accumulateNoise(int min_oct, int max_oct, int i, int j){
   static BaryNoise<GradientFixed4Contributor<MurmurHash3_64bit>, nonLinearActivationFunction, linearInterpolate>
            temp_1{GradientFixed4Contributor<MurmurHash3_64bit>(1)};
//    OctaveNoise<ValueFixedValueContributor<MurmurHash3_64bit>, nonLinearActivationFunction, linearInterpolate>
//            temp_1{ValueFixedValueContributor<MurmurHash3_64bit>(1)};
    double d_noise = 0;
    for(int oct = min_oct; oct <= max_oct; oct++){
        d_noise+= temp_1.noise(j/64.0f*(1<<oct), i/64.0f*(1<<oct))/(1<<oct);
    }
    return d_noise;
}

void mainfunc(int width, int height, unsigned char* temp_texture){
//    OctaveNoise<GradientFixed4Contributor<MurmurHash3_64bit>, nonLinearActivationFunction, linearInterpolate>
//        temp_1{GradientFixed4Contributor<MurmurHash3_64bit>(1)};
//    OctaveNoise<ValueFixedValueContributor<MurmurHash3_64bit>, nonLinearActivationFunction, linearInterpolate>
//            temp_1{ValueFixedValueContributor<MurmurHash3_64bit>(1)};


    int max_oct = 17;
    int min_oct = 0;
    for( int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            double d_noise = 0;
            d_noise += accumulateNoise(min_oct, max_oct, i, j);
            d_noise*= 0.5;
            accumTextureVals(i, j, width, temp_texture, d_noise);
        }
    }
}

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    //GLFW_CURSOR_NORMAL
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    ShaderProgram ourShader("../camera.vert", "../camera.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_verticies), quad_verticies, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load and create a texture
    // -------------------------
    TextureViewParams default_tex_params = {GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR};
    TextureViewParams special_tex_params = {GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST};
    Texture2D texture1("../resources/textures/container.jpg", default_tex_params);
    Texture2D texture2("../resources/textures/awesomeface.png", default_tex_params);


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setUniform("texture1", 0);
    ourShader.setUniform("texture2", 1);


    int width = 1024;
    int height = 1024;
    unsigned char *temp_texture = createTextureMemory(width, height);
    mainfunc(width, height, temp_texture);

    TextureSizeParams size_params = {width, height, GL_RGBA, GL_RGBA};
    Texture2D texture3(temp_texture, size_params,special_tex_params);


    // timing
    float deltaTime = 0.0f;    // time between current frame and last frame
    float lastFrame = 0.0f;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window, deltaTime);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        texture3.activate(GL_TEXTURE0);
        texture3.activate(GL_TEXTURE1);

        glm::vec4 temp{1, 2, 3, 4};
        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                                200.0f);
        ourShader.setUniform("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setUniform("view", view);

        // render boxes
        glBindVertexArray(VAO);
        //10
        for (unsigned int i = 0; i < 1; i++) {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setUniform("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, const float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.moveForward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.moveBackward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.moveLeft(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.moveRight(deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    static bool firstMouse = true;
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}