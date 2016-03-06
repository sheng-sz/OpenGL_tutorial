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
    
    //shader
    const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
    const GLchar* fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(0.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
    
    const GLchar* fragmentShaderSource1 = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
    "}\n\0";
    
    GLuint vshader;
    vshader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader,1,&vertexShaderSource,nullptr);
    glCompileShader(vshader);
    
    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader,1,&fragmentShaderSource,nullptr);
    glCompileShader(fshader);
    
    GLuint fshader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader1,1,&fragmentShaderSource1,nullptr);
    glCompileShader(fshader1);
    
    GLuint shader = glCreateProgram();
    glAttachShader(shader,fshader);
    glAttachShader(shader,vshader);
    glLinkProgram(shader);
    
    GLuint shader1 = glCreateProgram();
    glAttachShader(shader1,fshader1);
    glAttachShader(shader1,vshader);
    glLinkProgram(shader1);
    
    glDeleteShader(vshader);
    glDeleteShader(fshader);
    
    glDeleteShader(fshader1);

    
    
    //vertex stuff
    GLfloat vert[]={
        -0.8f,0.4f,0.0f,
        -0.2f,0.6f,0.0f,
        0.5f,-0.5f,0.0f,
        0.9f,0.9f,0.0f,
        0.9f,0.8f,0.0f,
        -0.8f,-0.8f,0.0f
    };
    
    GLuint ind[]={
        0,1,3,
        1,5,3
    };
    
    //initualize buffer id
    GLuint VBO;
    glGenBuffers(1,&VBO);
    
    GLuint VAO;
    glGenVertexArrays(1,&VAO);
    
    GLuint EBO;
    glGenBuffers(1,&EBO);
    
    glBindVertexArray(VAO);
    
        //bind buffer VBO to GL_array_buffer object
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        // pass vertices to buffer
        glBufferData(GL_ARRAY_BUFFER,sizeof(vert),vert,GL_STATIC_DRAW);
    
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(ind),ind,GL_STATIC_DRAW);
    
        //setup vertex attribute
    
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)(0*sizeof(GLfloat)));
        glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    
    
    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        // Render
        // Clear the colorbuffer
        //glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //draw with array object
        glUseProgram(shader1);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);
        
        //draw with element buffer
        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glDrawArrays(GL_LINE,0,2);
        glBindVertexArray(0);
        
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
