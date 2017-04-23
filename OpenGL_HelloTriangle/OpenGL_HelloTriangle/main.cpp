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
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"


//GLchar * vertexShaderSource =
//"#version 330 core\n"
//"layout (location = 0) in vec3 position;\n"
//"void main()\n"
//"{"
//"gl_Position = vec4(position,1.0f);\n"
//"}\n";
//
//GLchar * fragmentShaderSource =
//"#version 330 core\n"
//"out vec4 color;\n"
//"uniform vec4 outColor;"
//"void main()\n"
//"{"
//"color = outColor;\n"
////"color = vec4(1.0f,0.5f,0.2f,1.0f);\n"
//"}\n";

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
    
    glEnable(GL_DEPTH_TEST);
    
    
//    GLfloat vertices[] = {
//         0.5f,  0.5f, 0.0f, // TR
//         0.5f, -0.5f, 0.0f, // BR
//        -0.5f,  0.5f, 0.0f, // TL
//        
//         0.5f, -0.5f, 0.0f, // BR
//        -0.5f, -0.5f, 0.0f, // BL
//        -0.5f,  0.5f, 0.0f, // TL
//    };
    
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
    
//    // 创建Shader
//    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    // 绑定Shader程序
//    glShaderSource(vertexShader,1,&vertexShaderSource, NULL);
//    // 完成
//    glCompileShader(vertexShader);
//    
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
//    glCompileShader(fragmentShader);
//    
//    // 将两个shader链接起来
//    GLuint shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram,vertexShader);
//    glAttachShader(shaderProgram,fragmentShader);
//    glLinkProgram(shaderProgram);
//    
//    // 在Link之后就可以删除这两个Shader了
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);

    GLchar* vPath = "/Users/gaoyufei/Dev/workspace/mine/OpenGLearn/OpenGL_HelloTriangle/OpenGL_HelloTriangle/shaders/default.vs";
    GLchar* fPath = "/Users/gaoyufei/Dev/workspace/mine/OpenGLearn/OpenGL_HelloTriangle/OpenGL_HelloTriangle/shaders/default.frag";
    
    Shader ourShader(vPath,fPath);
    
    
    GLchar* vPath2 = "/Users/gaoyufei/Dev/workspace/mine/OpenGLearn/OpenGL_HelloTriangle/OpenGL_HelloTriangle/shaders/light.vs";
    GLchar* fPath2 = "/Users/gaoyufei/Dev/workspace/mine/OpenGLearn/OpenGL_HelloTriangle/OpenGL_HelloTriangle/shaders/light.frag";
    
    Shader lightShader(vPath2,fPath2);
    
    
    // 告诉VertexShader我的数据源(VBO)是什么组织结构的
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
    
    
    glm::vec3 viewPos(0.0f,0.0f,-3.0f);
    
    glm::mat4 view;
    view = glm::translate(view, viewPos);
    
    glm::mat4 projection;
    float screenWidth = width;
    float screenHeight = height;
    projection = glm::perspective(45.0f, screenWidth/screenHeight,0.1f,100.0f);
    
    GLuint lightVAO;
    glGenVertexArrays(1,&lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    
    glm::vec3 lightPos(-0.3f, 0.3f, 2.0f);
    
    // ------------------------Loop and refresh UI----------------------
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClearColor(0.0f,0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        
        //...

        ourShader.Use();
        
        
        GLint matAmbientLoc  = glGetUniformLocation(ourShader.Program, "material.ambient");
        GLint matDiffuseLoc  = glGetUniformLocation(ourShader.Program, "material.diffuse");
        GLint matSpecularLoc = glGetUniformLocation(ourShader.Program, "material.specular");
        GLint matShineLoc    = glGetUniformLocation(ourShader.Program, "material.shininess");
        
//        glUniform3f(matAmbientLoc,  1.0f, 0.5f, 0.31f);
//        glUniform3f(matDiffuseLoc,  1.0f, 0.5f, 0.31f);
//        glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
//        glUniform1f(matShineLoc,    32.0f);
        
//        white rubber	0.05	0.05	0.05	0.5	0.5	0.5	0.7	0.7	0.7	.078125
//        glUniform3f(matAmbientLoc,  0.05f, 0.05f, 0.05f);
//        glUniform3f(matDiffuseLoc,  0.05f, 0.05f, 0.05f);
//        glUniform3f(matSpecularLoc, 0.7f, 0.7f, 0.7f);
//        glUniform1f(matShineLoc,    0.078125f);
        
//        jade	0.135	0.2225	0.1575	0.54	0.89	0.63	0.316228	0.316228	0.316228	0.1
        glUniform3f(matAmbientLoc,  0.135f, 0.2225f, 0.1575f);
        glUniform3f(matDiffuseLoc,  0.54f, 0.89f, 0.63f);
        glUniform3f(matSpecularLoc, 0.316228f, 0.316628f, 0.316628f);
        glUniform1f(matShineLoc,    1.0f);
        
        
        GLint lightAmbientLoc  = glGetUniformLocation(ourShader.Program, "light.ambient");
        GLint lightDiffuseLoc  = glGetUniformLocation(ourShader.Program, "light.diffuse");
        GLint lightSpecularLoc = glGetUniformLocation(ourShader.Program, "light.specular");
        
        glUniform3f(lightAmbientLoc,  0.2f, 0.2f, 0.2f);
        glUniform3f(lightDiffuseLoc,  0.5f, 0.5f, 0.5f); // Let's darken the light a bit to fit the scene
        glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);

        
        GLint objectColorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
        GLint lightColorLoc  = glGetUniformLocation(ourShader.Program, "lightColor");
        glUniform3f(objectColorLoc, 1.0f, 1.0f, 0.31f);
        glUniform3f(lightColorLoc,  1.0f, 1.0f, 1.0f); // Also set light's color (white)
        
        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        glm::mat4 model;
        model = glm::rotate(model, (GLfloat)glfwGetTime() * 0.2f, glm::vec3(0.5f, 0.5f, 0.5f));
//        GLfloat scale = (sin(glfwGetTime()) + 1) / 2 + 0.5f;
//        model = glm::scale(model, glm::vec3(scale));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        
        GLint viewLoc = glGetUniformLocation(ourShader.Program,"view");
        glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
        
        GLint projectionLoc = glGetUniformLocation(ourShader.Program,"projection");
        glUniformMatrix4fv(projectionLoc,1,GL_FALSE,glm::value_ptr(projection));
        
        GLint lightPosLoc = glGetUniformLocation(ourShader.Program, "lightPos");
//        GLfloat lightX = sin(glfwGetTime() * 2);
//        GLfloat lightZ = cos(glfwGetTime() * 2);
//        lightPos = glm::vec3(lightX,0,lightZ);
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
        
        GLint viewPosLoc = glGetUniformLocation(ourShader.Program,"viewPos");
        glUniform3f(viewPosLoc, viewPos.x,viewPos.y,viewPos.z);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        
        // light
        
        lightShader.Use();

        
        model = glm::mat4();
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.05f));
        
        modelLoc = glGetUniformLocation(lightShader.Program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        
        viewLoc = glGetUniformLocation(lightShader.Program,"view");
        glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
        
        projectionLoc = glGetUniformLocation(lightShader.Program,"projection");
        glUniformMatrix4fv(projectionLoc,1,GL_FALSE,glm::value_ptr(projection));

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        
        

        //...
        
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}
