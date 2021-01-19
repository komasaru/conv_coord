#ifndef CONV_COORD_MATRIX_HPP_
#define CONV_COORD_MATRIX_HPP_

#include "st_position.hpp"

#include <cmath>
#include <iostream>

namespace conv_coord {

constexpr double kMtxUnit[3][3] = {
  {1.0, 0.0, 0.0},
  {0.0, 1.0, 0.0},
  {0.0, 0.0, 1.0},
};  // 単位行列
bool r_x(double, double(&)[3][3], const double(&)[3][3] = kMtxUnit);  // 回転行列生成（x軸中心）
bool r_y(double, double(&)[3][3], const double(&)[3][3] = kMtxUnit);  // 回転行列生成（y軸中心）
bool r_z(double, double(&)[3][3], const double(&)[3][3] = kMtxUnit);  // 回転行列生成（z軸中心）
StPosition rotate(StPosition, double(&)[3][3]);  // 座標回転

}  // namespace conv_coord

#endif

