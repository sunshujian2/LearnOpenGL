// Copyright <2017>[Tim Hu]


// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// #include <GL/glut.h>
#include <learnopengl/shader_s.h>
#include <math.h>
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
  // 设置当前的上下文
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

  // Build and compile our shader program
  Shader ourShader("shader.vs", "shader.fs");

  // set up vertex data (and buffer(s) and configure vertex attributes)
  // ----------------------------------------------------------------
  // 设置顶点数据和属性指针
  // 顶点输入
  GLfloat vertices[] = {
    // 位置              //颜色
    -0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,         // Left, red
    0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,         // Right, green
    0.0f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f          // Down, blue
  };
  // 生成一个VBO顶点对象，VBO顶点数组对象
  GLuint VBO, VAO;
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  // 先绑定顶点数组对象，再绑定和设置顶点缓存和属性指针
  glBindVertexArray(VAO);
  // 把顶点数组复制到缓存中供OpenGL使用
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
               vertices, GL_STATIC_DRAW);
  // 更新VAO中的顶点格式
  // 设置顶点位置属性指针
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // 设置颜色属性指针
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                        6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  // 绑定到GL_ARRAY_BUFFER目标上
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);  // Unbind VAO

  // ==============================================================
  // 实现简单的游戏循环
  while (!glfwWindowShouldClose(window)) {   // 要求被退出时函数返回True
    // 是否触发事件
    glfwPollEvents();
    // Render
    // 清空颜色缓冲
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 查询uniform地址不要求你之前使用过着色程序
    // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    // 但是更新Uniform之前需要使用程序
    ourShader.use();
    // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f)
    // ourShader.setBool("ourColor", true)
    
    // Draw first triangles
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // 交换screen buffer
    glfwSwapBuffers(window);
  }
  // Properly de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

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

// ..


/*
int main_sub() {
  
  // 顶点属性的上限
  // int nrAttributes;
  // glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  // std::cout << "Maxium nr of vertex attributes supported: "
  //           << nrAttributes << std::endl;
  

  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  std::cout << "Maximum nr of vertex attributes supported: "
            << nrAttributes << std::endl;   // 0????

  // 向量运算
  vec2 somevec;
  vec4 differentVec = someVec.xyzz;
}
*/
