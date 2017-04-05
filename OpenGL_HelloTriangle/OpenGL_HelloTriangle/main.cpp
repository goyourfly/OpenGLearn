//
//  main.cpp
//  OpenGL_HelloTriangle
//
//  Created by 高宇飞 on 2017/4/5.
//  Copyright © 2017年 高宇飞. All rights reserved.
//

#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


GLchar * vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{"
"gl_Position = vec4(position,1.0f);\n"
"}\n";

GLchar * fragmentShaderSource =
"#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{"
"color = vec4(1.0f,0.5f,0.2f,1.0f);\n"
"}\n";

void key_callback(GLFWwindow* window,int key,int scancode,int action, int mode ){
    std::cout << "key press in:" << key <<  std::endl;
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(int argc) {
    // --------------------------Init window--------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if(window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    // --------------------------Setup Viewport-------------------------
    int width,height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    // VAO是一个存储VBO之类的数组
    GLuint VAO;
    glGenVertexArrays(1,&VAO);
    
    // 生成一个Vertex Buffer Object，大小为1
    GLuint VBO;
    glGenBuffers(1,&VBO);
    
    // 在BindVBO之前，先BindVAO
    glBindVertexArray(VAO);
    
    // 设置VBO的类型为ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 将数据传送给VBO
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    // 创建Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 绑定Shader程序
    glShaderSource(vertexShader,1,&vertexShaderSource, NULL);
    // 完成
    glCompileShader(vertexShader);
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    
    // 将两个shader链接起来
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    
    // 在Link之后就可以删除这两个Shader了
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // 告诉VertexShader我的数据源(VBO)是什么组织结构的
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    
    
    // ------------------------Loop and refresh UI----------------------
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        //...
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        //...
        
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}
