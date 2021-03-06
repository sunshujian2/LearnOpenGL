/*
-------------------------------
  Copyright <2018>[Tim Hu]
  file:camera_mouse_zoom.cpp
  Date:Sat Jan  6 20:53:13 CST 2018
------------------------------ 
*/

/*
视角移动
- 俯仰角(pitch), 偏航角(Yaw), 滚轮角(Roll)

缩放
*/

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// stb_image.h
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <learnopengl/shader_s.h>
#include <math.h>
#include <iostream>

// include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// timing
float deltaTime = 0.0f;    // 现在这一帧和上一帧的时差
float lastFrame = 0.0f;

bool firstMouse = true;                        // 鼠标是否被移动
float pitch = 0.0f, yaw =  -90.0f;             // 偏转角
float lastX = WIDTH / 2, lastY = HEIGHT / 2;   // 鼠标位置
float fov = 45.0f;                     // 鼠标滚轮竖直滚动的大小


// 实例化GLFW窗口
int main() {
  std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
  // Init GLFW
  glfwInit();
  // Sel all the required options for GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL",
                                        nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  // 设置当前的上下文
  glfwMakeContextCurrent(window);
  // 注册函数至适合的回调
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  // 注册鼠标回调函数
  glfwSetCursorPosCallback(window, mouse_callback);
  // 注册滚轮回调函数
  glfwSetScrollCallback(window, scroll_callback);



  // 初始化GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }


  // 建立和编译着色程序
  // ===================
  Shader ourShader("shader_texture.vs", "shader_texture.fs");
  // 设置顶点数据和属性指针
  // =====================
  // 顶点输入
  GLfloat vertices[] = {
    // -------位置----   -----纹理坐标--
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
    // 10个立方体位置
  glm::vec3 cubePostions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
  };
  // 生成一个VBO顶点对象，VBO顶点数组对象
  GLuint VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // 先绑定顶点数组对象，再绑定和设置顶点缓存和属性指针
  glBindVertexArray(VAO);

  // 把顶点数组复制到缓存中供OpenGL使用
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
               vertices, GL_STATIC_DRAW);

  // 设置顶点位置属性指针
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // 设置纹理属性指针
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                        5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  // 加载和创建纹理
  // =============
  unsigned int texture1, texture2;

  // texture1
  // -------------
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);      // bind texture1
  // 设置环绕参数
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // 设置过滤参数
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // 加载图片stbi_image库
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(
      "../../../resources/textures/container.jpg",
      &width, &height, &nrChannels, 0);
  // 生成纹理
  if (data) {
    // 图片导入成功
    glTexImage2D(GL_TEXTURE_2D,
               0, GL_RGB, width, height,
               0, GL_RGB, GL_UNSIGNED_BYTE, data);
    // 为当前绑定的纹理自动生成所需要的多级渐远纹理
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    // 图片导入失败
    std::cout << "Failed to load texture1" << std::endl;
  }
  // 释放图像内存
  stbi_image_free(data);

  // texture2
  // ----------------
  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  // 设置环绕参数
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // 设置过滤参数
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // 加载图片stbi_image库
  data = stbi_load(
      "../../../resources/textures/awesomeface.png",
      &width, &height, &nrChannels, 0);
  // 生成纹理
  if (data) {
    // 图片导入成功
    glTexImage2D(GL_TEXTURE_2D,
               0, GL_RGBA, width, height,
               0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    // 为当前绑定的纹理自动生成所需要的多级渐远纹理
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    // 图片导入失败
    std::cout << "Failed to load texture2" << std::endl;
  }
  // 释放图像内存
  stbi_image_free(data);
  // 激活着色器前先设置uniform
  ourShader.use();
  glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
  glUniform1i(glGetUniformLocation(ourShader.ID, "texture2"), 1);

  // 开启深度缓冲
  glEnable(GL_DEPTH_TEST);

  // 隐藏鼠标并捕捉, 光标停留在窗口中，除非失去焦点
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // 渲染loop
  // ==============================================================
  while (!glfwWindowShouldClose(window)) {
    // 前一frame时间
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // 输入
    // -----
    processInput(window);

    // 渲染
    // -----
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // 清空颜色缓冲, 深度缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 绑定纹理, 会自动把纹理赋值给片段着色器的采样器
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // 激活着色器
    ourShader.use();

    // 矩阵定义
    // ==================

    // 摄像机位置
    // Look At
    glm::mat4 view;
    view = glm::lookAt(cameraPos,                    // 位置
                       cameraPos + cameraFront,      // 目标
                       cameraUp);                    // 上向量
    ourShader.setMat4("view", view);
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(fov),
                                  (float)WIDTH/ (float)HEIGHT,
                                  0.1f, 100.0f);
    ourShader.setMat4("projection", projection);

    // 渲染盒子
    glBindVertexArray(VAO);
    // /*
    for (unsigned int i = 0; i < 10; i++) {
      glm::mat4 model(1.0f);
      model = glm::translate(model, cubePostions[i]);
      float angle = (i%3 == 0 || i == 0) ? (20.0f * (i+1) * glfwGetTime()) : 0;
      model = glm::rotate(model, glm::radians(angle),
                           glm::vec3(1.0f, 0.3f, 0.5f));
      ourShader.setMat4("model", model);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    // */

    // 交换screen buffer
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  // Properly de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  // 释放GLFW分配的内存
  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions;
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  // 当用户按下esc键, 我们设置window窗口的windowShouldCloseni属性为True
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  // ...
  float cameraSpeed = 1.5f * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    cameraPos += cameraSpeed * cameraFront;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    cameraPos -= cameraSpeed * cameraFront;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    cameraPos -= glm::normalize(
        glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    cameraPos += glm::normalize(
        glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    cameraPos += (3 * cameraSpeed) * cameraUp;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  // ...

  if (firstMouse) {      // firstMouse boo类型，在初次进入时为true
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }


  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;    // 相反, 因为y坐标从底部往顶部增大
  lastX = xpos;
  lastY = ypos;

  float sensitivity = 0.05f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  // 摄像机限制
  pitch = (pitch > 89.0f) ? 89.0f:pitch;
  pitch = (pitch < -89.0f) ? -89.0f:pitch;

  // 设置偏航角

  // 4, 通过俯仰角和偏航角来计算得到真正的方向向量
  glm::vec3 front;
  front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  front.y = sin(glm::radians(pitch));
  front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  // std::cout << "front.x = " << front.x << '\n'
  //           << "front.y = " << front.y << '\n'
  //           << "front.z = " << front.z << std::endl;
  cameraFront = glm::normalize(front);

  // 第四步为什么不放在主循环中?
  // 鼠标没有移动前, cameraFront是不会改变的
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  if (fov >= 1.0f && fov <= 45.0f) fov -= yoffset;
  if (fov <= 1.0f) fov = 1.0f;
  if (fov >= 45.0f) fov = 45.0f;
}
