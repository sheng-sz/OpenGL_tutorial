#include <iostream>
using namespace std;
// GLEW
//#define GLEW_STATIC
//#include <GL/glew.h>

#include <glad/glad.h>
#include "shader_class1.cpp"
// GLFW test
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 1000, HEIGHT = 1000;

GLfloat my_mixer = 0.3f;


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
    
    
    int wid_framebuffer, height_framebuffer;
    glfwGetFramebufferSize(window, &wid_framebuffer, &height_framebuffer);
    glViewport(0, 0, wid_framebuffer, height_framebuffer);
    
//     Define the viewport dimensions
//    glViewport(0, 0, 800, 800);
    
//    //shader
//    const GLchar* vertexShaderSource = "#version 330 core\n"
//    "layout (location = 0) in vec3 position;\n"
//    "void main()\n"
//    "{\n"
//    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
//    "}\0";
//    const GLchar* fragmentShaderSource = "#version 330 core\n"
//    "out vec4 color;\n"
//    "void main()\n"
//    "{\n"
//    "color = vec4(0.0f, 0.5f, 0.2f, 1.0f);\n"
//    "}\n\0";
//    
//    const GLchar* fragmentShaderSource1 = "#version 330 core\n"
//    "out vec4 color;\n"
//    "void main()\n"
//    "{\n"
//    "color = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
//    "}\n\0";
    
//    GLuint vshader;
//    vshader=glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vshader,1,&vertexShaderSource,nullptr);
//    glCompileShader(vshader);
//    
//    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fshader,1,&fragmentShaderSource,nullptr);
//    glCompileShader(fshader);
//    
//    GLuint fshader1 = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fshader1,1,&fragmentShaderSource1,nullptr);
//    glCompileShader(fshader1);
//    
//    GLuint shader = glCreateProgram();
//    glAttachShader(shader,fshader);
//    glAttachShader(shader,vshader);
//    glLinkProgram(shader);
//    
//    GLuint shader1 = glCreateProgram();
//    glAttachShader(shader1,fshader1);
//    glAttachShader(shader1,vshader);
//    glLinkProgram(shader1);
//    
//    glDeleteShader(vshader);
//    glDeleteShader(fshader);
//    
//    glDeleteShader(fshader1);
    
    
    // Compile shader
    Shader ourShader("/Users/shengzhang/Desktop/Projects/OpenGL/opengl_tut_1/opengl_tut_1/vshader.cpp", "/Users/shengzhang/Desktop/Projects/OpenGL/opengl_tut_1/opengl_tut_1/fshader.cpp");

    // Load Texture
    int x,y,n;
//    x=512;
//    y=512;
    n=3;
    unsigned char *data = stbi_load("awesomeface.png", &x, &y, &n, 3);
    if (data==nullptr) {
        std::cout<< "image loading failed" << std::endl;
    }
    GLuint texture;
    //glGenTextures(# of textures, address)
    glGenTextures(1,&texture);
    
    glBindTexture(GL_TEXTURE_2D,texture);
    
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,x,y,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D,0);
    
    // texture 2
    
    unsigned char* data1 = stbi_load("container.jpg", &x, &y, &n, 0);
    if (data1==nullptr) {
        std::cout<< "image loading failed" << std::endl;
    }
    GLuint texture1;
    //glGenTextures(# of textures, address)
    glGenTextures(1,&texture1);
    
    glBindTexture(GL_TEXTURE_2D,texture1);
    
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,x,y,0,GL_RGB,GL_UNSIGNED_BYTE,data1);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data1);
    glBindTexture(GL_TEXTURE_2D,0);
	
    //vertex stuff
//    GLfloat vert[]={
//        -1.0f,-1.0f,0.0f,
//        1.0f,-1.0f,0.0f,
//        1.0f,1.0f,0.0f,
//        0.9f,0.9f,0.0f,
//        0.9f,0.8f,0.0f,
//        -0.8f,-0.8f,0.0f
//    };
//    GLfloat vert[] = {
//        // Positions          // Colors           // Texture Coords
//        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
//        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left
//    };
    
    
    GLfloat vert[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    
    glm::vec3 cubePositions[] = {
        glm::vec3( -0.2f,  0.0f,  2.0f),
        glm::vec3( -1.0f,  1.0f, -7.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };
    
    GLuint ind[]={
        0,1,3,
        1,2,3
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
        //position
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)(0*sizeof(GLfloat)));
        glEnableVertexAttribArray(0);
        //color
//        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
//        glEnableVertexAttribArray(1);
        //texture coordinates
        glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

    
    glBindVertexArray(0);
    
//    glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
//    glm::mat4 trans;
//    trans = glm::translate(trans, glm::vec3(1.0f,1.0f,0.0f));
//    vec = trans * vec ;
//    std::cout<<vec.x<<vec.y<<vec.z<<std::endl;
    
    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        glEnable(GL_DEPTH_TEST);
        
        // Render
        // Clear the colorbuffer
        //glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //Draw vertex mesh -- polygon mode
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        //Bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,texture);
        glUniform1i(glGetUniformLocation(ourShader.Program,"myTexture"),0);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,texture1);
        glUniform1i(glGetUniformLocation(ourShader.Program,"myTexture1"),1);
        
        glUniform1f(glGetUniformLocation(ourShader.Program,"my_mixer"),my_mixer);
        
        //Call shader program
        ourShader.Use();
        
//        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
//        trans = glm::translate(trans, glm::vec3(0.3f,0.3f,0.0f));

//        glUseProgram(shader1);
        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES,0,36);
//        glBindVertexArray(0);
        
        //draw with element buffer
//        glUseProgram(shader);
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
//        glBindVertexArray(0);
        GLfloat radius = 10.0f;
        GLfloat camX = sin(glfwGetTime()) * radius;
        GLfloat camZ = cos(glfwGetTime()) * radius;
        glm::vec3 worldUP = glm::vec3(0.0f,1.0f,0.0f);
        glm::vec3 worldOrigin = glm::vec3(0.0f,0.0f,0.0f);

        glm::mat4 view; // world space to view space
        view = glm::lookAt(glm::vec3(camX,0.0f,camZ),
                           worldOrigin,
                           worldUP);
        
//        view = glm::translate(view, glm::vec3(0.8f,0.4f,-15.0f));
        
        glm::mat4 projection;
        projection = glm::perspective(45.0f, (GLfloat)WIDTH/(GLfloat)HEIGHT, 0.1f, 100.0f);
        
        
        glUniformMatrix4fv(glGetUniformLocation(ourShader.Program,"view"),1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.Program,"projection"),1,GL_FALSE,glm::value_ptr(projection));
        
        for (int i=0; i<10; i++) {
            glm::mat4 model; // model space to world space
            
            model = glm::translate(model, cubePositions[i]);
//            GLfloat angle = 50.0 * i;
            model = glm::rotate(model, -16.0f*i, glm::vec3(1.0f,0.0f,0.0f));
            
            glUniformMatrix4fv(glGetUniformLocation(ourShader.Program,"model"),1,GL_FALSE,glm::value_ptr(model));
            glm::mat4 trans;
            // rotation
            trans = glm::rotate(trans, (GLfloat)glfwGetTime() * 60.0f, glm::vec3(0.2*i, 0.7*i, 1.0));
            trans = glm::rotate(trans, 60.0f, glm::vec3(0.2*i, 0.7*i, 1.0));
            glUniformMatrix4fv(glGetUniformLocation(ourShader.Program,"transform"),1, GL_FALSE,glm::value_ptr(trans));
            
            glDrawArrays(GL_TRIANGLES,0,36);
        }
        
        
        

//        glm::mat4 trans1;
//        trans1 = glm::translate(trans1, glm::vec3(-0.3f,-0.3f,0.0f));
//        trans1 = glm::scale(trans1, sin((GLfloat)glfwGetTime()) * glm::vec3(1.0f,1.0f,0.0f));
//        glUniformMatrix4fv(glGetUniformLocation(ourShader.Program,"transform"),1, GL_FALSE,glm::value_ptr(trans1));
//
//        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        
        glBindVertexArray(0);
        
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if (action == GLFW_PRESS){
     if (key == GLFW_KEY_G) {
     glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
     }
     if (key == GLFW_KEY_B){
     glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
     }
     if (key == GLFW_KEY_ESCAPE){
         std::cout<<"test"<<std::endl;
     glfwSetWindowShouldClose(window, GL_TRUE);
     }
    
    if (key==GLFW_KEY_K) {
        std::cout<<"k"<<std::endl;

        my_mixer += 0.1;
    }
        
        if (key==GLFW_KEY_J) {
            std::cout<<"j"<<std::endl;
            
            my_mixer -= 0.1;
        }
    }
    
    
//    if (action==GLFW_PRESS) {
//        switch (key) {
//            case GLFW_KEY_C:
//                glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
//                break;
//            case GLFW_KEY_R:
//                glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
//                break;
//            case GLFW_KEY_ESCAPE:
//                glfwSetWindowShouldClose(window, GL_TRUE);
//                break;
//            case GLFW_KEY_J:
//                my_mixer = my_mixer - 0.1f;
//                break;
//            case GLFW_KEY_K:
//                my_mixer = my_mixer + 0.1f;
//            default:
//                break;
//        }
//    }
    
}
