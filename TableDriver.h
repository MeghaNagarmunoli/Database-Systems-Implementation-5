#ifndef _TABLE_DRIVER_H_
#define _TABLE_DRIVER_H_

#include <algorithm>

class TableDriver {
public:
  bool createTable();
  bool insertInto();
  bool dropTable();
  void setOutput();
  bool exists(const char* relName);
private:
  

  static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
  }

  // trim from end
  static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
  }

  // trim from both ends
  static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
  }
};


#endif
