/*******************
blu.h
*******************/

#ifndef _BLU_H__
#define _BLU_H__

//导入Arduino核心头文件
#include "Arduino.h"

class BLU {
private:
public:
  BLU();           //构造函数
  ~BLU();          //析构函数
  void initBlu();  //
  void loopBlu();  //
  bool getConnectState();
};

#endif
