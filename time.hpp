#ifndef CONV_COORD_TIME_HPP_
#define CONV_COORD_TIME_HPP_

#include <ctime>
#include <iomanip>
#include <string>

namespace conv_coord {

struct timespec jst2utc(struct timespec);
std::string gen_time_str(struct timespec);

class Time {
  struct timespec ts;  // timespec of UTC
  double jd;           // JD (ユリウス日)
  double t;            // T (ユリウス世紀数)

public:
  Time(struct timespec ts) : ts(ts), jd(0.0), t(0.0) {}  // コンストラクタ
  double calc_jd();               // 計算: JD (ユリウス日)
  double calc_t();                // 計算: T  (ユリウス世紀数)

private:
  double gc2jd(struct timespec);  // GC  -> JD
  double jd2t(double);            // JD  -> T
};

}  // namespace conv_coord

#endif

