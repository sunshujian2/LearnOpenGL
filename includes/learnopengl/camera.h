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
  float pitch;
  float yaw;
  // 相机速度
  float moveSpeed = 0.2f;   // keyboard
  float sightSpeed;         // mouse
  float zoomSpeed;          // scroll
  float fov = 45.0f;        // scroll value

  // 光标坐标
  // bool firstMouse = true;
  // float lastX;
  // float lastY;
  const float sensitivity = 0.2f;

  // 相机观察矩阵
  glm::mat4 View;

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
         glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
         float p = 0.0f, float y = -90.0f) :
      cameraPos(position), cameraFront(front), cameraUp(up),
      pitch(p), yaw(y) {
    updateCameraVectors();
  }

  void setLookAt() {     // 输入位置, 目标, 上向量 lookAt, 改变view,
    View = glm::lookAt(cameraPos,
    cameraPos + cameraFront,      // 保证观察目标正对
    cameraUp);
  }
  glm::mat4 getViewMatrix() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
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

  void mouse_move(double xoffset, double yoffset) {
    // 鼠标移动控制
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch += yoffset;

    // pitch = (pitch > 89.0f) ? 89.0:pitch;
    // pitch = (pitch < -89.0f) ? -89.0f:pitch;
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch =  -89.0f;

    updateCameraVectors();
  }


  void scroll_move(double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 45.0f) fov -= yoffset;
    if (fov <= 1.0f) fov = 1.0f;
    if (fov >= 45.0f) fov = 45.0f;
  }

 private:
  void updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
  }
};





