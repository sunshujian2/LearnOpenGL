/*
-------------------------------
  Copyright <2018>[Tim Hu]
  file:coordinate_systems.cpp
  Date:Fri Jan  5 12:39:19 CST 2018 
------------------------------ 
*/

/*
稍微向后倾斜至地板方向
离我们有一些距离
有透视效果
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

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
// const float screenWidth = WIDTH, screenHeight = HEIGHT;

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
  /*
  GLfloat vertices[] = {
    
    0.5f,   0.5f, 0.0f,  1.0f,  1.0f,  // 右上角
    0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  // 左下角
    -0.5f,  0.5f, 0.0f,  0.0f,  1.0f   // 左上角
  };
  */
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
  /*
  unsigned int indices[] = {
    0, 1, 3,    // 第一个三角形
    1, 2, 3     // 第二个三角形
  };
  */
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

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
  //              indices, GL_STATIC_DRAW);

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

  // 渲染loop
  // ==============================================================
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    // 渲染
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // 清空颜色缓冲, 深度缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 绑定纹理, 会自动把纹理赋值给片段着色器的采样器
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    ourShader.use();

    // /*
    // 矩阵定义
    // ==================
    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);
    // 模型矩阵, 变换到世界空间
    model = glm::rotate(model,
                        (float)glfwGetTime() * glm::radians(50.0f),
                        glm::vec3(0.5f, 1.0f, 0.0f));
    // 观察矩阵, 将矩阵向我们想要进行移动场景的反方向移动
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // 投影矩阵, 场景中适用透视投影
    projection = glm::perspective(glm::radians(45.0f),
                                  (float)WIDTH/ (float)HEIGHT,
                                  0.1f, 100.0f);
    // 将矩阵传入着色器
    unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
    unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
    unsigned int projLoc = glGetUniformLocation(ourShader.ID, "projection");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    // */

    // /*
    glBindVertexArray(VAO);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    //  */

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
}


