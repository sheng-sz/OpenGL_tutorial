#include<iostream>
using namespace std;
#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#include <glad/glad.h>

// GLFW test
#include <GLFW/glfw3.h>


int main()
{
    
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    // osx specific
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    int xx = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", nullptr, nullptr);
     xx = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
     xx = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    // Set the required callback functions
//    glfwSetKeyCallback(window, key_callback);
    
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    
    
    // Load texture
    int x,y,n;
    x=512;
    y=512;
    n=3;
    unsigned char *data = stbi_load("container.jpg", &x, &y, &n, 0);
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
    
    cout<< "done" << endl;
    
    return 0;
}