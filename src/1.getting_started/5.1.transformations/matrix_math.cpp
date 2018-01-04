/*
-------------------------------
  Copyright <2018>[Tim Hu]
  file:matrix_math.cpp
  Date:Thu Jan  4 10:06:53 CST 2018
------------------------------ 
*/

#include <math.h>
#include <iostream>
// include OpenGL Mathematic
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

#define PI 3.1415926;

float dot_product(float vec1[], float vec2[]);
float length(float vec1[], float vec2[]);
float angle(float vec[]);
float* cross_product(float vec1[], float vec2[]);
void revise_array(int A[]);


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



void translate(float trans[4][4], float vec[4][1]) {
  /*
    [2 0 0 1]  [x]    [2x+1]
    [0 2 0 2]  [y]    [2y+2]
    [0 0 2 3]* [z] =  [2z+3]
    [0 0 0 1]  [1]    [  1 ]
   */
  // 左列与右行数是否相等
  int li_t = 4, col_t = 4;
  std::cout << "-- -------print matrix--------- --" << std::endl;
  for (int i = 0; i < li_t; i++) {
    for (int j = 0; j < col_t; j++) {
      std::cout << trans[i][j] << ',';
    }
    std::cout << '\n';
  }
  int li_v = 4, col_v = 1;
  std::cout << "-- -------print vector--------- --" << std::endl;
  for (int i = 0; i < li_v; i++) {
    for (int j = 0; j < col_v; j++) {
      std::cout << vec[i][j] << ',';
    }
    std::cout << '\n';
  }
  // matrix multiply
  std::cout << "-- -------matrix vector multiply--------- --" << std::endl;
  float vec_mul[4][1] = {};
  for (int i = 0; i < li_t; i++) {
    float line_mass = 0;
    for (int j = 0; j < col_t; j++) {
      std::cout << vec[j][0] << ',';
      line_mass += trans[i][j] * vec[j][0];
    }
    vec_mul[i][0] = line_mass;
    line_mass = 0;
    std::cout << "vec_mul[i][0] = " << vec_mul[i][0] << '\n';
  }
  vec = vec_mul;
}

void revise_array(int A[2][3]) {
  A[0][0] = 5;
  A[0][1] = 2;
  A[0][2] = -1;
  // A[0] = {5, 2, -1};
}

void test_array() {
  int arr[] = {1, -1, 5};
  int i = *(arr+1);
  std::cout << "i = " << i << std::endl;
  int arr_d[2][3] = {{4, -2, 3}, {1, 9, 8}};
  revise_array(arr_d);
  std::cout << "arr[0] = " << arr_d[0][0] << std::endl;
}

int main() {
  // ...
  /*
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
  */

  // -- -------maxtrix----------- --
  float trans[4][4] = {{1, 0, 0, 1},
                       {0, 1, 0, 2},
                       {0, 0, 1, 3},
                       {0, 0, 0, 1}
  };

  float vec4_mat[4][1] = {{1.3},
                          {2.2},
                          {3.1},
                          {1}
  };
  int li_v = 4, col_v = 1;

  translate(trans, vec4_mat);
  std::cout << "-- -------print vector--------- --" << std::endl;
  for (int i = 0; i < li_v; i++) {
    for (int j = 0; j < col_v; j++) {
      std::cout << vec4_mat[i][j] << ',';
    }
    std::cout << '\n';
  }
  std::cout << "-- -------test array--------- --" << std::endl;
  test_array();
  return 0;
}
