// Copyright <2017>[Tim Hu]

#ifndef SHADER_H
// 只有SHADER_H没被include的情况下才include和comiple这个头文件
#define SHADER_H

// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class Shader {
 public:
  // 程序ID
  unsinged int ID;

  // 构造器读取并建构着色器
  Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
    // 1, 从文件路径获取顶点/片段着色器
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // 保证ifstream对象能抛出异常
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
      // 打开文件
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);
      std::stringstream vShaderStream, fShaderStream;
      // 读取文件的缓冲内容到数据流中
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();
      // 关闭文件处理器
      vShaderFile.close();
      fShaderFile.close();
      // 转换数据流到string
      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e) {
      std::cout << "ERROR::SHADER::FILE::NOT::SUCCESSFUL::READ"
                << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // =============
    // 2.编译着色器
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // 着色片段也类似
    fragment = glCreateShader();
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // 着色器程序
    ID = glCreateProgram();          // 已声明, 重新定义
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // 删除着色器
    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }
  // 使用/激活程序
  void use() {
    glUseProgram(ID);
  }
  // uniform工具函数
  void setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), int(value));
  }
  void setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value)
  }
  void setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }

 private:
  // Utility function for checking shader compilation/linking errors
  void checkCompileErrors(unsigned int shader, const std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type:"
                  << type << "\n" << infoLog <<
            "\n -- -------------------------- --" << std::endl;
      }
    } else {
      glGetShaderiv(shader, GL_LINK_STATUS, &success);
      if (!success) {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type:"
                  << type << "\n" << infoLog <<
            "\n -- -------------------------- --" << std::endl;
      }
    }
  }
};
#endif
