#ifndef CONV_COORD_COMMON_HPP_
#define CONV_COORD_COMMON_HPP_

#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace conv_coord {

// -------------------------------------
//   Functions
// -------------------------------------
struct timespec jst2utc(struct timespec);
std::string gen_time_str(struct timespec);

}  // namespace conv_coord

#endif

