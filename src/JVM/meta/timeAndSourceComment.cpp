#include <iostream>

#include <time.h>
#include <cstring>
#include "timeAndSourceComment.h"

namespace toyc {

  timeAndSourceComment::timeAndSourceComment(std::string s) {
    text = s;
    time_t _tm = time(NULL);
    struct tm *curtime = localtime(&_tm);
    text = asctime(curtime);
  }

  timeAndSourceComment::timeAndSourceComment() {
    text = "";
    time_t _tm = time(NULL);
    struct tm *curtime = localtime(&_tm);
    text = asctime(curtime); // has a newline at end ... grrrr. Remove it!
    text.erase(strcspn(text.c_str(),"\r\n"));
  }
  
  std::string timeAndSourceComment::toString() {
    std::string str = "; " + text;
    return str;
  }
  
}
