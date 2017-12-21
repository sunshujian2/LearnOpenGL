// Copyright <2017>[Tim Hu]


// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// #include <GL/glut.h>

#include <iostream>

// Function prototypes
void key_callback(GLFWwindow* window, int key,
                  int scancode, int action, int mode);
// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

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
  // 设置未当前的上下文
  glfwMakeContextCurrent(window);
  // 注册函数至适合的回调
  glfwSetKeyCallback(window, key_callback);


  // 初始化GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }
  // 设置窗口维度(Dimension)
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  // 实现简单的游戏循环
  while (!glfwWindowShouldClose(window)) {   // 要求被退出时函数返回True
    // 是否触发事件
    glfwPollEvents();

    // Render
    // 清空颜色缓冲
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 交换颜色缓冲
    glfwSwapBuffers(window);
  }

  // 释放GLFW分配的内存
  glfwTerminate();
  return 0;
}

void key_callback(GLFWwindow* window, int key,
                  int scancode, int action, int mode) {
  // 当用户按下esc键, 我们设置window窗口的windowShouldCloseni属性为True
  // 关闭应用程序
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}


