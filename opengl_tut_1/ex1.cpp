#include <iostream>
using namespace std;
// GLEW
//#define GLEW_STATIC
//#include <GL/glew.h>

#include <glad/glad.h>


// GLFW test
#include <GLFW/glfw3.h>
// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 800;

// The MAIN function, from here we start the application and run the game loop
int main()
{
//    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    cout << "Starting GLFW context, OpenGL 3.3" << endl;
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    // osx specific
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    //glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    //if (glewInit() != GLEW_OK)
    
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }
    
    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);
    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        
        // Render
        // Clear the colorbuffer
        //glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    /*if (action == GLFW_PRESS){
        if (key == GLFW_KEY_G) {
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        }
        else if (key == GLFW_KEY_B){
            glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        }
        else if (key == GLFW_KEY_ESCAPE){
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        else{
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }*/
    
    switch (key) {
        case GLFW_KEY_C:
            glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
            break;
        case GLFW_KEY_R:
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
            break;
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        default:
            break;
    }
    
}
