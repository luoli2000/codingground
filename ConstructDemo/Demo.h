#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace llcode{

class Demo {
 public:
  Demo() { init(" ", "+"); }

  Demo(const std::string& val) { init(val, "+"); }

  Demo(const Demo& other) { init(other.val_, "*", other.getVer()); }

  Demo(Demo&& other) { moveinit(move(other.val_), "~", other.getVer()); }

  Demo& operator=(const Demo& other) {
    if (this != &other) {
      init(other.val_, "=", other.getVer());
    }
    return *this;
  }
  Demo& operator=(Demo&& other) {
    if (this != &other) {
      moveinit(move(other.val_), "~=", other.getVer());
    }
    return *this;
  }

  ~Demo() { init("<X>", "-"); }
  std::string getVal() const { return val_; };
  int getVer() const { return ver_; };

  void Display(const std::string& tag, int srcVer) {
    std::cout << tag << "(" << val_ << "/" << ver_ << "/" << this << ")";
    if (srcVer != -1) {
      std::cout << " <= " << srcVer;
    }
    std::cout << std::endl;
  }

 private:
  void init(const std::string& val, const std::string& tag, int srcVer = -1) {
    if (tag != "-") {
      val_ = val;
      ver_ = verSeed_++;
    }
    Display(tag, srcVer);
  }

  void moveinit(std::string&& val, const std::string& tag, int srcVer = -1) {
    if (tag != "-") {
      val_ = move(val);
      ver_ = verSeed_++;
    }
    Display(tag, srcVer);
  }

  std::string val_;
  int ver_;

  static int verSeed_;
};
}