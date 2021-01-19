#ifndef CONV_COORD_COORD_HPP_
#define CONV_COORD_COORD_HPP_

#include "st_position.hpp"

#include <iostream>

namespace conv_coord {

class Coord {
  double eps;

public:
  Coord(double eps): eps(eps) {}
  StPosition rect_eq2ec(const StPosition);  // 変換: 赤道直交座標 -> 黄道直交座標
  StPosition rect_ec2eq(const StPosition);  // 変換: 黄道直交座標 -> 赤道直交座標
  StPosition rect2pol(  const StPosition);  // 変換: 直交座標     -> 極座標
  StPosition pol_eq2ec( const StPosition);  // 変換: 赤道極座標   -> 黄道極座標
  StPosition pol_ec2eq( const StPosition);  // 変換: 黄道極座標   -> 赤道極座標
  StPosition pol2rect(  const StPosition);  // 変換: 極座標       -> 直交座標
};

}  // namespace conv_coord

#endif

