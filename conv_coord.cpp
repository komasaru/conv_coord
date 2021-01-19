/***********************************************************
  天体座標変換

    DATE          AUTHOR          VERSION
    2020.11.02    mk-mode.com     1.00 新規作成

  Copyright(C) 2020 mk-mode.com All Rights Reserved.

  ----------------------------------------------------------
  引数 : JST（日本標準時） X Y Z
         書式 * JST: 最大23桁の数字
                （先頭から、西暦年(4), 月(2), 日(2), 時(2), 分(2), 秒(2),
                            1秒未満(9)（小数点以下9桁（ナノ秒）まで））
              * X, Y, Z: 元の赤道直交座標
***********************************************************/
#include "common.hpp"
#include "coord.hpp"
#include "obliquity.hpp"
#include "st_position.hpp"
#include "time.hpp"

#include <cmath>
#include <cstdlib>   // for EXIT_XXXX
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>


int main(int argc, char* argv[]) {
  static constexpr double kPi = atan(1.0) * 4.0;
  namespace ns = conv_coord;
  std::string     tm_str;     // time string
  unsigned int    s_tm;       // size of time string
  int             s_nsec;     // size of nsec string
  ns::StPosition  pos_src;    // 直交座標（元の）
  ns::StPosition  pos_res;    // 座標（計算結果用）
  struct timespec jst;        // JST
  struct timespec utc;        // UTC
  struct          tm t = {};  // for work
  double          jcn;        // Julian Century Number
  double          eps;        // 黄道傾斜角

  try {
    // コマンドライン引数の個数チェック
    if (argc < 5) {
      std::cout << "Usage: ./conv_coord JST X Y Z" << std::endl;
      return EXIT_SUCCESS;
    }

    // JST 取得
    tm_str = argv[1];
    s_tm = tm_str.size();
    if (s_tm > 23) {
      std::cout << "[ERROR] Over 23-digits!" << std::endl;
      return EXIT_FAILURE;
    }
    s_nsec = s_tm - 14;
    std::istringstream is(tm_str);
    is >> std::get_time(&t, "%Y%m%d%H%M%S");
    jst.tv_sec  = mktime(&t);
    jst.tv_nsec = 0;
    if (s_tm > 14) {
      jst.tv_nsec = std::stod(
          tm_str.substr(14, s_nsec) + std::string(9 - s_nsec, '0'));
    }

    // 元の赤道直交座標取得
    pos_src.x = std::stod(argv[2]);
    pos_src.y = std::stod(argv[3]);
    pos_src.z = std::stod(argv[4]);

    // JST -> UTC
    utc = ns::jst2utc(jst);

    // ユリウス世紀数計算
    ns::Time o_tm(utc);
    jcn = o_tm.calc_t();

    // 黄道傾斜角計算
    ns::Obliquity o_ob;
    eps = o_ob.calc_ob(jcn);

    // 事前準備の情報
    std::cout << "JST: "
              << ns::gen_time_str(jst) << std::endl
              << "UTC: "
              << ns::gen_time_str(utc) << std::endl
              << " JD: "
              << std::fixed << std::setprecision(10) << o_tm.calc_jd()
              << " day" << std::endl
              << "  T: "
              << jcn
              << " century (= Julian Century Number)" << std::endl
              << "EPS:  "
              << eps
              << " rad." << std::endl
              << "     "
              << eps * 180.0 / kPi
              << " deg." << std::endl
              << "---" << std::endl;

    // 座標クラスのインスタンス化
    ns::Coord o_cd(eps);

    // 計算＆結果出力
    std::cout << "RECT_EQ = ["
              << pos_src.x << ", " << pos_src.y << ", " << pos_src.z
              << "]" << std::endl;
    pos_res = o_cd.rect_eq2ec(pos_src);
    std::cout << "RECT_EC = ["
              << pos_res.x << ", " << pos_res.y << ", " << pos_res.z
              << "]" << std::endl;
    pos_res = o_cd.rect_ec2eq(pos_res);
    std::cout << "RECT_EQ = ["
              << pos_res.x << ", " << pos_res.y << ", " << pos_res.z
              << "]" << std::endl;
    pos_res = o_cd.rect2pol(pos_res);
    std::cout << " POL_EQ = ["
              << pos_res.x << ", " << pos_res.y
              << "] (R = " << pos_res.z << ")" << std::endl;
    pos_res = o_cd.pol_eq2ec(pos_res);
    std::cout << " POL_EC = ["
              << pos_res.x << ", " << pos_res.y
              << "] (R = " << pos_res.z << ")" << std::endl;
    pos_res = o_cd.pol_ec2eq(pos_res);
    std::cout << " POL_EQ = ["
              << pos_res.x << ", " << pos_res.y
              << "] (R = " << pos_res.z << ")" << std::endl;
    pos_res = o_cd.pol2rect(pos_res);
    std::cout << "RECT_EQ = ["
              << pos_res.x << ", " << pos_res.y << ", " << pos_res.z
              << "]" << std::endl;
  } catch (...) {
      std::cerr << "EXCEPTION!" << std::endl;
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

