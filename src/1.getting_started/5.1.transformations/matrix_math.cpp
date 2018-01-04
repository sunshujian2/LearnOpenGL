/*
-------------------------------
  Copyright <2018>[Tim Hu]
  file:matrix_math.cpp
  Date:Thu Jan  4 10:06:53 CST 2018
------------------------------ 
*/

#include <math.h>
#include <iostream>

#define PI 3.1415926;

float dot_product(float vec1[], float vec2[]);
float length(float vec1[], float vec2[]);
float angle(float vec[]);
float* cross_product(float vec1[], float vec2[]);

float dot_product(float vec1[], float vec2[]) {
  float product_result = vec1[0] * vec2[0] + vec1[1] * vec2[1];
  return product_result;
}

float length(float vec[]) {
  return sqrt((vec[0] * vec[0] + vec[1] * vec[1]));
}

float angle(float vec1[], float vec2[]) {
  // 反余弦, 计算光照时候特别有用。
  float cosin = dot_product(vec1, vec2)/(length(vec1)*length(vec2));
  float angle = acos(cosin) * 180/PI;
  return angle;
}

void cross_product(float vec1[], float vec2[], float vec_r[]) {
  // (Ax, Ay, Az) x (Bx, By, Bz) = (Ay * Bz - Az * By
  //                                Az * Bx - Ax * Bz
  //                                Ax * By - Ay * Bx)
  vec_r[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
  vec_r[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
  vec_r[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

int main() {
  // ...
  float vec1[] = {0.6, -0.8};
  float vec2[] = {0  ,  1};
  float dot_r = dot_product(vec1, vec2);
  std::cout << "dot_product result = " << dot_r << std::endl;
  float angle_r = angle(vec1, vec2);
  std::cout << "angle result = " << angle_r << std::endl;

  float cross_vec1[] = {1, 2, 3};
  float cross_vec2[] = {4, 5, 6};
  float cross_vec_r[] = {};
  cross_product(cross_vec1, cross_vec2, cross_vec_r);
  std::cout << "cross_product result = " << cross_vec_r[0] << ','
            << cross_vec_r[1] << ','
            << cross_vec_r[2] << std::endl;
  return 0;
}
