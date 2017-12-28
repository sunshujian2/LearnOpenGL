// Copyright <2017>[Tim Hu]
// 创建相同的两个三角形，但对它们的数据使用不同的VAO和VBO
// 放在同一个数组中，但需要各自绑定和各自绘制， 也可以匹配不同的顶点数组


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

// 顶点着色器
const GLchar* vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 position;\n"
  "void main() {\n"
  "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
  "}\n\0";

// 片段着色器
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main() {\n"
    "color = vec4(1.0f, 0.5, 0.2f, 1.0f);\n"
    "}\n\0";

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


  // 建立和编译着色器
  // 创建顶点着色器
  GLuint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // 源码附加到着色器对象上
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // 检测glComplieShader是否编译成功
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // 创建片段着色器
  GLuint fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  // 源码附加到着色器对象上
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // 检测glComplieShader是否编译成功
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // 把两个着色器对象链接到用来渲染的着色程序中
  GLuint shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  // 删除着色器
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // 设置顶点数据和属性指针
  // 顶点输入, 绘制两个彼此相连的三角形
  GLfloat firstTriangleVertices[] = {
    // 第一个triangle
    0.5f,   0.5f, 0.0f,    // 右上角
    0.1f,  -0.5f, 0.0f,    // 右下角
    -0.5f,  0.3f, 0.0f,    // 左下角
  };

  GLfloat secondTriangleVertices[] = {
    // 第二个triangle
    -0.5f, -0.5f, 0.0f,    // 左下角
    -0.1f,  0.5f, 0.0f,    // 左上角
    0.5f,  -0.3f, 0.0f     // 右下角
  };


  // 生成一个VBO顶点对象，VBO顶点数组对象
  GLuint VBOs[2], VAOs[2];
  glGenBuffers(2, VBOs);       // 对数组的引用是指向数组第一个数的指针
  glGenVertexArrays(2, VAOs);
  // ===========FirstTrianglevertices绑定==============
  // 先绑定顶点数组对象，再绑定和设置顶点缓存和属性指针
  glBindVertexArray(VAOs[0]);
  // 把顶点数组复制到缓存中供OpenGL使用
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangleVertices),
               firstTriangleVertices, GL_STATIC_DRAW);
  // 设置顶点属性指针
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // glBindBuffer(GL_ARRAY_BUFFER, 0);  // 不需要unbind, 在新的一行重新绑定

  // ===========SecondTrianglevertices绑定==============
  // 先绑定顶点数组对象，再绑定和设置顶点缓存和属性指针
  glBindVertexArray(VAOs[1]);
  // 把顶点数组复制到缓存中供OpenGL使用
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangleVertices),
               secondTriangleVertices, GL_STATIC_DRAW);
  // 设置顶点属性指针
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // glBindBuffer(GL_ARRAY_BUFFER, 0); // 同样不需要

  // 不注释这行代码会以线框模式绘制
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // 实现简单的游戏循环
  while (!glfwWindowShouldClose(window)) {   // 要求被退出时函数返回True
    // 是否触发事件
    glfwPollEvents();

    // Render
    // 清空颜色缓冲
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw first triangles
    // =====激活程序对象绘制第一个triangle======
    glUseProgram(shaderProgram);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);  // 从索引0开始依次绘制3个顶点
    // glBindVertexArray(0);  // Unbind VAO **是放在这里吗???*** **不**

    // =====激活程序对象绘制第二个triangle======
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);  // 从索引0开始依次绘制3个顶点
    glBindVertexArray(0);  // Unbind VAO 是放在这里吗

    // 从索引缓冲渲染
    //  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    // 交换screen buffer
    glfwSwapBuffers(window);
  }
  // Properly de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);

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
