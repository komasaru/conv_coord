#ifndef CONV_COORD_COORD_HPP_
#define CONV_COORD_COORD_HPP_

namespace conv_coord {

// 直交座標・極座標兼用
struct Coord {
  double x;  // x, lambda, lambda, alpha
  double y;  // y, phi,    beta,   delta
  double z;  // z, radius
};

}  // namespace conv_coord

#endif

