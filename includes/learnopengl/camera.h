/*
-------------------------------
  Copyright <2018>[Tim Hu]
  file:camera.h
  Date:Sun Jan  7 10:46:54 CST 2018
------------------------------ 
*/

/*
构造摄像机位置和方向
键盘控制移动
鼠标移动控制
滚轮控制缩放
*/

// #ifndef CAMERA_H
#define CAMERA_H

// GLFW
#include <GLFW/glfw3.h>

// include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Camera {
 public:

  // 相机位置
  glm::vec3 cameraPos;
  glm::vec3 cameraFront;
  glm::vec3 cameraUp;

  // 旋转欧拉角
  float pitch = -90.0f;
  float yaw = 0.0f;
  // 相机速度
  float moveSpeed = 0.2f;   // keyboard
  float sightSpeed;         // mouse
  float zoomSpeed;          // scroll
  float fov = 45.0f;        // scroll value

  // 相机观察矩阵
  glm::mat4 View;

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
         glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
         float p = -90.0f, float y = 0.0f) :
      cameraPos(position), cameraFront(front), cameraUp(up),
      pitch(p), yaw(y) { }

  /*
  Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up,
         float pitch, float yaw) :
      postion(glm::vec3(0.0f, 0.0f, 3.0f),
      front(glm::vec3(0.0f, 0.0f, -1.0f)),
      up(glm::vec3(0.0f, 1.0f, 0.0f)),
      pitch(pitch),
      yaw(yaw) {}
  */

  void setLookAt() {     // 输入位置, 目标, 上向量 lookAt, 改变view,
    View = glm::lookAt(cameraPos,
    cameraPos + cameraFront,      // 保证观察目标正对
    cameraUp);
  }

  void keyboard_move(GLFWwindow *window) {
    // 键盘控制移动
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      cameraPos += moveSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      cameraPos -= moveSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= moveSpeed * glm::cross(cameraFront, cameraUp);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += moveSpeed * glm::cross(cameraFront, cameraUp);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      cameraPos += moveSpeed * cameraUp;
  }
  /*
  void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    // 鼠标移动控制
    if (firstMouse) {
      lastX = xpos;
      lastY = ypos;
      firstMoush = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
  }
  */
};





