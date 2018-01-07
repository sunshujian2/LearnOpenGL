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

ex1: 变成一个真正的FPS摄像机（也就是说不能够随意飞行）；你只能够呆在xz平面
ex2: 创建你自己的LookAt函数
*/

// #ifndef CAMERA_H
#define CAMERA_H

// include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};


// 相机初始默认值
const float YAW = -90.0f;
// 旋转欧拉角
const float PITCH = 0.0f;
// 相机速度
const float SPEED = 2.0f;               // keyboard
const float SENSITIVITY = 0.2f;         // mouse
const float SCROLL = 1.5f;              // scroll
const float ZOOM = 45.0f;               // fov



class Camera {
 public:
  // 相机位置
  glm::vec3 cameraPos;
  glm::vec3 cameraFront;
  glm::vec3 cameraUp;
  glm::vec3 cameraRight;

  // 旋转欧拉角
  float pitch;
  float yaw;
  // 相机速度
  const float moveSpeed = SPEED;          // keyboard
  const float mouseSpeed = SENSITIVITY;   // mouse
  const float scrollSpeed = SCROLL;       // scroll
  float fov = ZOOM;                       // scroll value

  // 相机观察矩阵
  glm::mat4 View;

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
         glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
         float p = PITCH, float y = YAW) :
      cameraPos(position), cameraFront(front), cameraUp(up),
      pitch(p), yaw(y) {
    updateCameraVectors();
  }

  Camera(float posX, float posY, float posZ,
         float upX, float upY, float upZ,
         float y = YAW, float p = PITCH):
  cameraPos(glm::vec3(posX, posY, posZ)),
  cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
  cameraUp(glm::vec3(upX, upY, upZ)),
  pitch(p),
  yaw(y) { }

  glm::mat4 getViewMatrix() {
    // return myLookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  }

  void keyboard_move(Camera_Movement direction, float deltaTime) {
    // 键盘控制移动
    float velocity = moveSpeed * deltaTime;
    if (direction == FORWARD)
      cameraPos += velocity * cameraFront;
    if (direction == BACKWARD)
      cameraPos -= velocity * cameraFront;
    if (direction == LEFT)
      cameraPos -= velocity * cameraRight;
    if (direction == RIGHT)
        cameraPos += velocity * cameraRight;

    cameraPos.y = 0.0f;          //保持在地平线上, xz平面

    updateCameraVectors();
  }

  void mouse_move(double xoffset, double yoffset) {
    // 鼠标移动控制
    xoffset *= mouseSpeed;
    yoffset *= mouseSpeed;
    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch =  -89.0f;

    updateCameraVectors();
  }


  void scroll_move(double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 45.0f) fov -= yoffset * scrollSpeed;
    if (fov <= 1.0f) fov = 1.0f;
    if (fov >= 45.0f) fov = 45.0f;

    updateCameraVectors();
  }


  glm::mat4 myLookAt(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
    // glm::mat4 view;
    // 1. Position = known
    // 2. Calculate cameraDiretion
    glm::vec3 zaxis = glm::normalize(position - target);
    // 3. get positive right axis vector
    glm::vec3 xaxis = glm::normalize(glm::cross(
        glm::normalize(cameraUp),
        zaxis));
    // 4. Calculate camera up vector
    glm::vec3 yaxis = glm::cross(zaxis, xaxis);

    // Create translation and rotation matrix
    glm::mat4 translation;
    translation[3][0] = -position.x;
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;

    glm::mat4 rotation;
    rotation[0][0] = xaxis.x;
    rotation[1][0] = xaxis.y;
    rotation[2][0] = xaxis.z;
    rotation[0][1] = yaxis.x;
    rotation[1][1] = yaxis.y;
    rotation[2][1] = yaxis.z;
    rotation[0][2] = zaxis.x;
    rotation[1][2] = zaxis.y;
    rotation[2][2] = zaxis.z;

    return rotation * translation;
  }


 private:
  void updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

    cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
  }
};





